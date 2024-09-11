#include "root_repository.h"

using namespace Skribisto::Common::Persistence::Repositories;

RootRepository::RootRepository(std::unique_ptr<DatabaseTableGroup<Root>> dbTableGroup, 
                                std::shared_ptr<InterfaceBookRepository> bookRepository, 
                                QObject* parent)
    : QObject(parent), m_dbTableGroup(std::move(dbTableGroup)), m_bookRepository(std::move(bookRepository)) {}

QList<Root> RootRepository::create(const QList<Root>& roots) {
    auto result = m_dbTableGroup->create(roots);
    emit created(getIds(result));
    return result;
}

QList<Root> RootRepository::get(const QList<int>& rootIds) {
    return m_dbTableGroup->get(rootIds);
}

QList<Root> RootRepository::getWithDetails(const QList<int>& rootIds) {
    return m_dbTableGroup->getWithDetails(rootIds);
}

QList<int> RootRepository::getAllIds() {
    return m_dbTableGroup->getAllIds();
}

QList<Root> RootRepository::update(const QList<Root>& roots) {
    auto result = m_dbTableGroup->update(roots);
    emit updated(getIds(result));
    return result;
}
QList<int> RootRepository::remove(const QList<int>& rootIds) {
    auto roots = m_dbTableGroup->get(rootIds)
    
    // Remove books in cascade
    for (int root : roots) {
        m_bookRepository->remove(QList<int>() << root->getBook());
    }

    m_dbTableGroup->remove(rootIds);
    emit removed(rootIds);
    return rootIds;
}

QList<int> RootRepository::getIds(const QList<Root>& roots) const {
    QList<int> ids;
    for (const auto& root : roots) {
        ids.append(root.id());
    }
    return ids;
}
