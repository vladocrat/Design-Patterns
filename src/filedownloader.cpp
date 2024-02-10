#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QAuthenticator>

#include "usercontroller.h"

struct FileDownloader::impl_t
{
    QNetworkAccessManager qnam;
};

FileDownloader* FileDownloader::instance() noexcept
{
    static FileDownloader fd;
    return &fd;
}

FileDownloader::FileDownloader()
{
    createImpl();

    QObject::connect(&impl().qnam, &QNetworkAccessManager::authenticationRequired, this, [](QNetworkReply* reply, QAuthenticator* authenticator)
    {
        authenticator->setUser(UserController::instance()->username());
        authenticator->setPassword(UserController::instance()->password());
    });
}

FileDownloader::~FileDownloader()
{

}

QNetworkReply* FileDownloader::download(const QUrl& url) noexcept
{
    return impl().qnam.get(QNetworkRequest{url});
}


