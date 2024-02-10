#include "downloadcontroller.h"

#include <QQmlEngine>
#include <QFileInfo>

#include "threadpool.h"
#include "filedownloader.h"
#include "filesaver.h"

namespace Internal
{

void download(const QVariant& file, const QString& path)
{
    auto filePath = file.value<QString>();
    auto reply = FileDownloader::instance()->download(QUrl{filePath});

    QObject::connect(reply, &QNetworkReply::finished, [reply, path, filePath]()
    {
        auto data = reply->readAll();
        FileSaver saver;
        QFileInfo info(filePath);
        auto fileName = info.fileName();
        QUrl url{path};
        auto localPath = url.toLocalFile();

        if (!saver.save(data, localPath + "/" + fileName))
        {
            qDebug() << "failed to save file";
        }

        reply->deleteLater();
    });
}

} //! Internal

DownloadController* DownloadController::instance() noexcept
{
    static DownloadController dc;
    return &dc;
}

void DownloadController::download(QVariantList list, const QString& path) const noexcept
{
    auto pool = ThreadPool::instance();
    pool->initialize(4);

    for (const auto& file : list)
    {
        auto result = pool->start(Internal::download, file, path);
    }

    // for (const auto& file : list)
    // {
    //     auto thread = pool->get();

    //     if (thread == nullptr)
    //     {
    //         auto connection = std::make_unique<QMetaObject::Connection>();
    //         *connection = QObject::connect(pool, &ThreadPool::threadFreed, this, [thread, file, path, &connection](){
    //             QObject::disconnect(*connection);
    //             Internal::download(thread.get(), file, path);
    //         });

    //         continue;
    //     }

    //     Internal::download(thread.get(), file, path);
    // }
}

void DownloadController::registerType() noexcept
{
    qmlRegisterSingletonInstance("DownloadController", 1, 0, "DownloadController", DownloadController::instance());
}
