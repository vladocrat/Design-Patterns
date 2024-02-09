#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "threadpool.h"
#include "filedownloader.h"
#include "filesaver.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // auto pool = ThreadPool::instance();
    // pool->initialize(4);
    // auto thread = pool->get();
    // auto thread1 = pool->get();
    // auto thread2 = pool->get();

    // auto downloader = FileDownloader::instance();
    // downloader->setUser({"user", "password"});
    // auto reply = downloader->download(QUrl{"ftp://localhost:8082/test.txt"});

    // QObject::connect(reply, &QNetworkReply::finished, [reply]()
    // {
    //     auto data = reply->readAll();

    //     FileSaver saver;

    //     if (!saver.save(data, "test.txt"))
    //     {
    //         qDebug() << "failed to save file";
    //     }

    //     qDebug() << "saved successfully";
    // });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
