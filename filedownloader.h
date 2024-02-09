#pragma once

#include <QObject>
#include <QVector>
#include <QFile>
#include <QNetworkReply>

#include "pimpl.h"

class FileDownloader final : public QObject
{
    Q_OBJECT
public:
    FileDownloader();

    QNetworkReply* download(const QUrl& url) noexcept;

private:
    DECLARE_PIMPL
};

