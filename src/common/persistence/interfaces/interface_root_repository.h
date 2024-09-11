#pragma once

#include "entities/root.h"
#include "interface_repository.h"

#include <QList>

namespace Skribisto::Common::Persistence::Interfaces {

class InterfaceRootRepository : public virtual InterfaceRepository {
public:
    virtual ~InterfaceRootRepository() = default;

    virtual QList<Root> create(const QList<Root>& roots) = 0;
    virtual QList<Root> get(const QList<int>& rootIds) = 0;
    virtual QList<Root> getWithDetails(const QList<int>& rootIds) = 0;
    virtual QList<int> getAllIds() = 0;
    virtual QList<Root> update(const QList<Root>& roots) = 0;
    virtual QList<int> remove(const QList<int>& rootIds) = 0;
};

}
