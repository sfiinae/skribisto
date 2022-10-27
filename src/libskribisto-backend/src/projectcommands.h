#ifndef PROJECTCOMMANDS_H
#define PROJECTCOMMANDS_H

#include <QObject>
#include <QUndoCommand>
#include "skribisto_backend_global.h"
#include "interfaces/invokablecommandgroupinterface.h"
#include "skrresult.h"

#define projectCommands ProjectCommands::instance()

class SKRBACKENDEXPORT ProjectCommands : public QObject, public InvokableCommandGroupInterface
{
    Q_OBJECT
public:
    explicit ProjectCommands(QObject *parent, QUndoStack *undoStack);

    static ProjectCommands* instance()
    {
        return m_instance;
    }
    int createNewEmptyProject();

    SKRResult save(int projectId);
    SKRResult backupAProject(int projectId, const QString &type, const QUrl &folderPath);
    SKRResult saveAProjectCopy(int projectId, const QString &extension, const QUrl &path);
    void closeProject(int projectId);
    SKRResult saveAs(int projectId, const QUrl &url, const QString &extension);
    QString getSaveFilter() const;

    void setProjectName(int projectId, const QString &name);
    void setAuthor(int projectId, const QString &author);
    void setLanguageCode(int projectId, const QString &newLanguage);
    void setActiveProject(int projectId);

    void loadProject(const QUrl &url);
signals:

private:
    static ProjectCommands *m_instance;
    QUndoStack *m_undoStack;

    // InvokableCommandGroupInterface interface
public:
    QString address() const override
    {
        return "project";
    }

    // InvokableCommandGroupInterface interface
public:
    Command *getCommand(const QString &action, const QVariantMap &parameters) override;
};

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

class SetProjectNameCommand : public Command
{
public:
    SetProjectNameCommand(int projectId, const QString &name);
    void undo();
    void redo();
private:
    QString m_newName, m_oldName;
    int m_projectId;
};

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

class SetAuthorCommand : public Command
{
public:
    SetAuthorCommand(int projectId, const QString &author);
    void undo();
    void redo();
private:
    QString m_newName, m_oldName;
    int m_projectId;
};

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

class SetLanguageCodeCommand : public Command
{
public:
    SetLanguageCodeCommand(int projectId, const QString &newLanguage);
    void undo();
    void redo();
private:
    QString m_oldLanguageCode, m_newLanguageCode;
    int m_projectId;
};

#endif // PROJECTCOMMANDS_H
