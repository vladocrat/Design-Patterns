#pragma once

#include <QRunnable>
#include <QMutex>
#include <QUrl>

#include "pimpl.h"

class DownloadWorker final : public QRunnable
{
public:
    DownloadWorker(const QString& fileUrl, const QString& path);
    ~DownloadWorker();

protected:
    void run() override;

private:
    DECLARE_PIMPL
};

