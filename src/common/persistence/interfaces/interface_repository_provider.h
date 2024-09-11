#include "interface_repository.h"
#include "common_export.h"
#include <QSharedPointer>

#pragma once
namespace Skribisto::Common::Persistence::Interfaces
{
class QLEANY_EXPORT InterfaceRepositoryProvider
{
  public:
    virtual ~InterfaceRepositoryProvider()
    {
    }

    virtual void registerRepository(const char *name, InterfaceRepository *repository) = 0;
    virtual InterfaceRepository *repository(const char *name) = 0;
};
} // namespace Qleany::Contracts::Repository
