#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "authcontroller.h"
#include "downloadcontroller.h"
#include "usercontroller.h"

void registerTypes()
{
    AuthController::registerType();
    DownloadController::registerType();
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    app.setOrganizationName("designpatterns");
    app.setOrganizationDomain("designpatterns.com");

    UserController::instance();
    registerTypes();

    QQmlApplicationEngine engine;

    const QUrl url{QStringLiteral("qrc:/main.qml")};

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
