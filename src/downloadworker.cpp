#include "downloadworker.h"

#include <QMutexLocker>
#include <QFileInfo>

#include "filedownloader.h"
#include "filesaver.h"

struct DownloadWorker::impl_t
{
    QMutex m_lock;
    QString m_fileUrl;
    QString m_path;
};

DownloadWorker::DownloadWorker(const QString& fileUrl, const QString& path)
{
    createImpl();

    impl().m_fileUrl = fileUrl;
    impl().m_path = path;
}

DownloadWorker::~DownloadWorker() {}

void DownloadWorker::run()
{
    auto reply = FileDownloader::instance()->download(impl().m_fileUrl);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        auto data = reply->readAll();
        FileSaver saver;
        QFileInfo info(impl().m_fileUrl);
        auto fileName = info.fileName();
        QUrl url{impl().m_path};
        auto localPath = url.toLocalFile();

        if (!saver.save(data, localPath + "/" + fileName))
        {
            qDebug() << "failed to save file";
        }

        reply->deleteLater();
        qDebug() << "worker finished";
    });
}
