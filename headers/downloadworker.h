#pragma once

#include <QRunnable>
#include <QMutex>
#include <QUrl>

class DownloadWorker final : public QRunnable
{
public:
    DownloadWorker(const QString& fileUrl, const QString& path);
    ~DownloadWorker();

protected:
    void run() override;

private:
    QMutex m_lock;
    QString m_fileUrl;
    QString m_path;
};

