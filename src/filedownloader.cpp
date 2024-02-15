#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QAuthenticator>

#include "usercontroller.h"

struct FileDownloader::impl_t
{
    QNetworkAccessManager qnam;
    int count { 0 };
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

    QObject::connect(&impl().qnam, &QNetworkAccessManager::finished, [this] () {
        static int count;
        ++count;
        qDebug() << "QNAM FINISHED " << count << " " << impl().count;
    });
}

FileDownloader::~FileDownloader()
{

}

QNetworkReply* FileDownloader::download(const QUrl& url) noexcept
{
    ++impl().count;
    return impl().qnam.get(QNetworkRequest{url});
}


