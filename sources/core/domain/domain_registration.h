#pragma once

#include "domain_global.h"
#include "entity.h"
#include "scene.h"
#include "chapter.h"
#include "book.h"
#include "atelier.h"
#include "author.h"
#include "entity_base.h"

#include <QObject>

namespace Domain {

class SKR_DOMAIN_EXPORT DomainRegistration : public QObject
{
    Q_OBJECT
  public:
    explicit DomainRegistration(QObject *parent)
    {
        
        qRegisterMetaType<Domain::Entity>();
        qRegisterMetaType<Domain::Scene>();
        qRegisterMetaType<Domain::Chapter>();
        qRegisterMetaType<Domain::Book>();
        qRegisterMetaType<Domain::Atelier>();
        qRegisterMetaType<Domain::Author>();
        qRegisterMetaType<Domain::SceneParagraph>();
        qRegisterMetaType<Domain::EntityBase>();

    }
};

} // namespace Domain
