#include "filedownloader.h"

#include <QNetworkAccessManager>
#include <QAuthenticator>

struct FileDownloader::impl_t
{
    QNetworkAccessManager qnam;
    User user;
};

FileDownloader* FileDownloader::instance() noexcept
{
    static FileDownloader fd;
    return &fd;
}

FileDownloader::FileDownloader()
{
    createImpl();

    QObject::connect(&impl().qnam, &QNetworkAccessManager::authenticationRequired, this, [this](QNetworkReply* reply, QAuthenticator* authenticator)
    {
        authenticator->setUser(impl().user.username);
        authenticator->setPassword(impl().user.password);
    });
}

FileDownloader::~FileDownloader()
{

}

QNetworkReply* FileDownloader::download(const QUrl& url) noexcept
{
    return impl().qnam.get(QNetworkRequest{url});
}

void FileDownloader::setUser(const User& user) noexcept
{
    impl().user = user;
}


