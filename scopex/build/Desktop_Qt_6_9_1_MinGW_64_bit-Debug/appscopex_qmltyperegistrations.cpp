/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<serialhandler.h>)
#  include <serialhandler.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_ScopeX()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<SerialHandler>("ScopeX", 1);
    QMetaType::fromType<SerialHandler::WaveformType>().id();
    QT_WARNING_POP
    qmlRegisterModule("ScopeX", 1, 0);
}

static const QQmlModuleRegistration scopeXRegistration("ScopeX", qml_register_types_ScopeX);
