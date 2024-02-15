#include "downloadcontroller.h"

#include <QQmlEngine>
#include <QFileInfo>

#include "saver.h"
#include "filedownloader.h"
#include "threadpool.h"

struct DownloadController::impl_t
{
    float progress{0};
    int workers {0};
    int workersFinished{0};
    QStringList urls;
};

DownloadController* DownloadController::instance() noexcept
{
    static DownloadController dc;
    return &dc;
}

DownloadController::DownloadController()
{
    createImpl();

    QObject::connect(ThreadPool::instance(), &ThreadPool::taskCompleted, this, [this] (const QString& fileName)
    {
        qDebug() << "Task completed: " << fileName;
        qDebug() << "workers encr: " << impl().workers << " " << fileName;
        ++impl().workers;
        emit fileSaved(fileName);

        if (impl().urls.empty())
        {
            return;
        }

        while (impl().workers > 0 && !impl().urls.empty())
        {
            downloadFiles();
        }
    });
}

DownloadController::~DownloadController()
{

}

void DownloadController::download(const QStringList& files, const QString& path, const QString& threadNum) noexcept
{
    auto pool = ThreadPool::instance();
    pool->setSavePath(path);

    bool ok {true};
    auto threadNumber = threadNum.toInt(&ok);

    if (!ok || threadNumber <= 0)
    {
        qDebug() << "Incorrect thread number";
        return;
    }

    impl().workers = threadNumber;
    auto count = static_cast<float>(impl().urls.count());
    pool->initialize(threadNumber);

    for (const auto& item: files)
    {
        QUrl requestedUrl{item};

        if (!requestedUrl.isValid())
        {
            qDebug() << item << " Is invalid requested url, skipping";
            continue;
        }

        impl().urls.push_back(item);
    }

    QObject::connect(pool, &ThreadPool::taskCompleted, this, [this, count]()
    {
        impl().workersFinished++;
        impl().progress = static_cast<float>(impl().workersFinished / count);
        emit progressChanged();
    });

    downloadFiles();
}

float DownloadController::progress()
{
    return impl().progress;
}

void DownloadController::registerType() noexcept
{
    qmlRegisterSingletonInstance("DownloadController", 1, 0, "DownloadController", DownloadController::instance());
}

void DownloadController::downloadFiles()
{
    if (impl().workers == 0)
    {
        return;
    }

    if (impl().urls.empty())
    {
        return;
    }

    auto currentUrl = impl().urls.takeFirst();
    auto reply = FileDownloader::instance()->download(currentUrl);


    qDebug() << "Request " << impl().workers << " " <<  currentUrl;
    --impl().workers;

    QObject::connect(reply, &QNetworkReply::redirected, [] (QUrl redirected)
    {
        qDebug() << "Redirected to: " << redirected;
    });

    QObject::connect(reply, &QNetworkReply::errorOccurred, [reply] (QNetworkReply::NetworkError err)
    {
        qDebug() << "download error";
        qDebug() << reply->errorString();
        qDebug() << err;
    });

    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply, currentUrl] ()
    {
        qDebug() << "reply finished " << reply->bytesAvailable() << " " << currentUrl;

        qDebug() << impl().urls;

        if (reply->error() != QNetworkReply::NoError)
        {
            ++impl().workers;
            downloadFiles();
            return;
        }

        auto buffer = reply->readAll();
        reply->deleteLater();

        ThreadPool::instance()->addTask(QUrl{currentUrl}.fileName(), buffer);
    });
}
