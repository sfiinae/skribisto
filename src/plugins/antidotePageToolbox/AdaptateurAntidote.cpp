/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c AdaptateurAntidote -a AdaptateurAntidote
 *API_DBus.xml
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "AdaptateurAntidote.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class AdaptateurAntidote
 */

AdaptateurAntidote::AdaptateurAntidote(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

AdaptateurAntidote::~AdaptateurAntidote()
{
    // destructor
}

void AdaptateurAntidote::ActiveDocument()
{
    // handle method call com.druide.antidote.dbus.api.ActiveDocument
    QMetaObject::invokeMethod(parent(), "activeDocument");
}

void AdaptateurAntidote::CorrigeDansTexteur(int leDebut, int laFin, const QString& laChaine, bool automatique)
{
    // handle method call com.druide.antidote.dbus.api.CorrigeDansTexteur
    QMetaObject::invokeMethod(parent(), "corrigeDansTexteur", Q_ARG(int, leDebut), Q_ARG(int, laFin),
                              Q_ARG(QString, laChaine), Q_ARG(bool, automatique));
}

QString AdaptateurAntidote::DonneBloc(int leDebut, int laFin)
{
    // handle method call com.druide.antidote.dbus.api.DonneBloc
    QString _ret;

    QMetaObject::invokeMethod(parent(), "donneBloc", Q_RETURN_ARG(QString, _ret), Q_ARG(int, leDebut),
                              Q_ARG(int, laFin));
    return _ret;
}

int AdaptateurAntidote::DonneDebutSelection()
{
    // handle method call com.druide.antidote.dbus.api.DonneDebutSelection
    int _ret;

    QMetaObject::invokeMethod(parent(), "donneDebutSelection", Q_RETURN_ARG(int, _ret));
    return _ret;
}

int AdaptateurAntidote::DonneFinDocument()
{
    // handle method call com.druide.antidote.dbus.api.DonneFinDocument
    int _ret;

    QMetaObject::invokeMethod(parent(), "donneFinDocument", Q_RETURN_ARG(int, _ret));
    return _ret;
}

int AdaptateurAntidote::DonneFinSelection()
{
    // handle method call com.druide.antidote.dbus.api.DonneFinSelection
    int _ret;

    QMetaObject::invokeMethod(parent(), "donneFinSelection", Q_RETURN_ARG(int, _ret));
    return _ret;
}

int AdaptateurAntidote::DonnePositionFinBoite(int unePos)
{
    // handle method call com.druide.antidote.dbus.api.DonnePositionFinBoite
    int _ret;

    QMetaObject::invokeMethod(parent(), "donnePositionFinBoite", Q_RETURN_ARG(int, _ret), Q_ARG(int, unePos));
    return _ret;
}

QString AdaptateurAntidote::DonneRetourDeCharriot()
{
    // handle method call com.druide.antidote.dbus.api.DonneRetourDeCharriot
    QString _ret;

    QMetaObject::invokeMethod(parent(), "donneRetourDeCharriot", Q_RETURN_ARG(QString, _ret));
    return _ret;
}

QString AdaptateurAntidote::DonneTitreDocument()
{
    // handle method call com.druide.antidote.dbus.api.DonneTitreDocument
    QString _ret;

    QMetaObject::invokeMethod(parent(), "donneTitreDocument", Q_RETURN_ARG(QString, _ret));
    return _ret;
}

bool AdaptateurAntidote::PermetsRetourDeCharriot()
{
    // handle method call com.druide.antidote.dbus.api.PermetsRetourDeCharriot
    bool _ret;

    QMetaObject::invokeMethod(parent(), "permetsRetourDeCharriot", Q_RETURN_ARG(bool, _ret));
    return _ret;
}

void AdaptateurAntidote::RetourneAuTexteur()
{
    // handle method call com.druide.antidote.dbus.api.RetourneAuTexteur
    QMetaObject::invokeMethod(parent(), "retourneAuTexteur");
}

void AdaptateurAntidote::RompsLienCorrecteur()
{
    // handle method call com.druide.antidote.dbus.api.RompsLienCorrecteur
    QMetaObject::invokeMethod(parent(), "rompsLienCorrecteur");
}

void AdaptateurAntidote::RompsLienTexteur()
{
    // handle method call com.druide.antidote.dbus.api.RompsLienTexteur
    QMetaObject::invokeMethod(parent(), "rompsLienTexteur");
}

void AdaptateurAntidote::SelectionneIntervalle(int leDebut, int laFin)
{
    // handle method call com.druide.antidote.dbus.api.SelectionneIntervalle
    QMetaObject::invokeMethod(parent(), "selectionneIntervalle", Q_ARG(int, leDebut), Q_ARG(int, laFin));
}
