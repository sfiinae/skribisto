#pragma once
#include "QtSql/qsqlerror.h"
#include "database/entity_table_sql_generator.h"
#include "database/interface_database_context.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QThreadPool>
#include <QUuid>

template <class T, class U> class DummyDatabaseContext : public Contracts::Database::InterfaceDatabaseContext
{
  public:
    DummyDatabaseContext();
    ~DummyDatabaseContext();
    Result<void> init() override;

  private:
    QString m_databaseName;
    QStringList m_entityClassNames;

    // InterfaceDatabaseContext interface
  public:
    QSqlDatabase getConnection() override;
    QStringList entityClassNames() const override;
    void setEntityClassNames(const QStringList &newEntityClassNames) override;
};

template <class T, class U> DummyDatabaseContext<T, U>::DummyDatabaseContext()
{
    const char *t = T::staticMetaObject.className();
    qRegisterMetaType<T>();
    qRegisterMetaType<U>(U::staticMetaObject.className());

    m_databaseName = ":memory:";
}

template <class T, class U> DummyDatabaseContext<T, U>::~DummyDatabaseContext()
{
}

template <class T, class U> Result<void> DummyDatabaseContext<T, U>::init()
{
    auto db = DummyDatabaseContext::getConnection();

    {
        QSqlQuery query(db);

        QStringList sqlList;
        Database::EntityTableSqlGenerator generator(m_entityClassNames);
        sqlList << generator.generateEntitySql<U>();
        sqlList << generator.generateEntitySql<T>();
        sqlList.removeDuplicates();

        for (const QString &queryStr : sqlList)
        {
            qDebug() << queryStr;
            if (!query.prepare(queryStr))
            {
                qCritical() << query.lastError().text() << queryStr;
            }
            if (!query.exec())
            {
                qCritical() << query.lastError().text() << queryStr;
            }
        }
    }

    return Result<void>();
}

template <class T, class U> QSqlDatabase DummyDatabaseContext<T, U>::getConnection()
{
    QString connectionName = QString("connectionName");
    if (!QSqlDatabase::contains(connectionName))
    {
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        database.setDatabaseName(m_databaseName);
        if (!database.open())
        {
            QSqlDatabase::removeDatabase(connectionName);
            qDebug() << Q_FUNC_INFO << "sql_error" << database.lastError().text();
        }
    }
    // qDebug() << QSqlDatabase::connectionNames();

    return QSqlDatabase::database(connectionName);
}

template <class T, class U> QStringList DummyDatabaseContext<T, U>::entityClassNames() const
{
    return m_entityClassNames;
}

template <class T, class U> void DummyDatabaseContext<T, U>::setEntityClassNames(const QStringList &newEntityClassNames)
{
    m_entityClassNames = newEntityClassNames;
}
