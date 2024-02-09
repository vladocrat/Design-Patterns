#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QAuthenticator>

struct FileDownloader::impl_t
{
    QNetworkAccessManager qnam;
};

FileDownloader::FileDownloader()
{
    createImpl();

    QObject::connect(&impl().qnam, &QNetworkAccessManager::authenticationRequired, this, [](QNetworkReply* reply, QAuthenticator* authenticator)
    {
        authenticator->setUser("user");
        authenticator->setPassword("password");
    });
}

FileDownloader::~FileDownloader()
{

}

QNetworkReply* FileDownloader::download(const QUrl& url) noexcept
{
    return impl().qnam.get(QNetworkRequest{url});
}


