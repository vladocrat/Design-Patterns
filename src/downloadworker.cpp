#include "downloadworker.h"

#include <QMutexLocker>
#include <QFileInfo>

#include "filedownloader.h"
#include "filesaver.h"

DownloadWorker::DownloadWorker(const QString& fileUrl, const QString& path)
    : m_fileUrl{fileUrl}, m_path{path} {}

DownloadWorker::~DownloadWorker() {}

void DownloadWorker::run()
{
    auto reply = FileDownloader::instance()->download(m_fileUrl);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        auto data = reply->readAll();
        FileSaver saver;
        QFileInfo info(m_fileUrl);
        auto fileName = info.fileName();
        QUrl url{m_path};
        auto localPath = url.toLocalFile();

        if (!saver.save(data, localPath + "/" + fileName))
        {
            qDebug() << "failed to save file";
        }

        reply->deleteLater();
        qDebug() << "worker finished";
    });
}
