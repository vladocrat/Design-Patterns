#pragma once

#include <QObject>
#include <QVector>
#include <QFile>
#include <QNetworkReply>

#include "pimpl.h"
#include "user.h"

class FileDownloader final : public QObject
{
    Q_OBJECT
public:
    static FileDownloader* instance() noexcept;

    [[nodiscard]] QNetworkReply* download(const QUrl& url) noexcept;
    void setUser(const User&) noexcept;

private:
    FileDownloader();
    ~FileDownloader();
    FileDownloader(const FileDownloader&) = delete;
    FileDownloader(FileDownloader&&) = delete;
    FileDownloader& operator=(const FileDownloader&) = delete;
    FileDownloader& operator=(FileDownloader&&) = delete;

    DECLARE_PIMPL
};

