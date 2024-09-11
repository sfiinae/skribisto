#pragma once

#include <QObject>
#include <QList>

#include "interface_book_repository.h"
#include <memory>
#include "persistence/interfaces/interface_root_repository.h"
#include "database_table_group.h"

using namespace Skribisto::Common::Persistence::Interfaces;

namespace Skribisto::Common::Persistence::Repositories {

class RootRepository : public QObject, public InterfaceRepository, public InterfaceRootRepository {
    Q_OBJECT

    public:
        explicit RootRepository(std::unique_ptr<DatabaseTableGroup<Root>> dbTableGroup, 
                                std::shared_ptr<InterfaceBookRepository> bookRepository, 
                                QObject* parent = nullptr);

    QList<Root> create(const QList<Root>& roots) override;
    QList<Root> get(const QList<int>& rootIds) override;
    QList<Root> getWithDetails(const QList<int>& rootIds) override;
    QList<int> getAllIds() override;
    QList<Root> update(const QList<Root>& roots) override;
    QList<int> remove(const QList<int>& rootIds) override;

signals:
    void created(const QList<int>& ids);
    void updated(const QList<int>& ids);
    void removed(const QList<int>& ids);

private:
    std::unique_ptr<DatabaseTableGroup<Root>> m_dbTableGroup;
    
    std::shared_ptr<InterfaceBookRepository> m_bookRepository;    

    QList<int> getIds(const QList<Root>& roots) const;
};

} // namespace Skribisto::Common::Persistence::Repositories