#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "serialhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register the C++ type with QML
    qmlRegisterType<SerialHandler>("ScopeX", 1, 0, "SerialHandler");

    QQmlApplicationEngine engine;

    // Add import path for the QML module
    engine.addImportPath("qrc:/");

    // Load the QML file from the resource system
    const QUrl url(u"qrc:/qt/qml/ScopeX/Main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
