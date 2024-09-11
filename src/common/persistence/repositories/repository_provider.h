#pragma once

#include "common_export.h"
#include <QDebug>
#include <QHash>
#include <QMutex>
#include <QObject>
#include "persistence/interfaces/interface_repository.h"
#include "persistence/interfaces/interface_repository_provider.h"
#include <type_traits>

using namespace Skribisto::Common::Persistence::Repositories::Interfaces;

namespace Skribisto::Common::Persistence::Repositories
{
class COMMON_EXPORT RepositoryProvider : public QObject,
                                         public InterfaceRepositoryProvider
{
    Q_OBJECT

  public:
    static RepositoryProvider *instance();

    // InterfaceRepositoryProvider interface

  public:
    void registerRepository(const char *name, InterfaceRepository *repository) override;

    InterfaceRepository *repository(const char *name) override;

  private:
    RepositoryProvider() = default;
    RepositoryProvider(const RepositoryProvider &) = delete;
    RepositoryProvider &operator=(const RepositoryProvider &) = delete;

    QHash<QString, InterfaceRepository *> m_repositories;
    QMutex m_mutex;
    static QScopedPointer<RepositoryProvider> s_instance;
};
} // namespace Qleany::Repository
