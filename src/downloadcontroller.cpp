#include "downloadcontroller.h"

#include <QQmlEngine>
#include <QFileInfo>

#include "threadpool.h"

DownloadController* DownloadController::instance() noexcept
{
    static DownloadController dc;
    return &dc;
}

void DownloadController::download(QVariantList list, const QString& path) const noexcept
{
    auto pool = ThreadPool::instance();
    pool->initialize(1);

    for (const auto& file : list)
    {
        auto strFile = file.value<QString>();
        pool->enqueue(new DownloadWorker(strFile, path));
    }

    pool->start();
}

void DownloadController::registerType() noexcept
{
    qmlRegisterSingletonInstance("DownloadController", 1, 0, "DownloadController", DownloadController::instance());
}
