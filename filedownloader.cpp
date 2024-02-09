#include "filedownloader.h"

#include <QNetworkAccessManager>

struct FileDownloader::impl_t
{
    QNetworkAccessManager qnam;
};

FileDownloader::FileDownloader()
{

}

QNetworkReply* FileDownloader::download(const QUrl& url) noexcept
{
    return impl().qnam.get(QNetworkRequest{url});
}


