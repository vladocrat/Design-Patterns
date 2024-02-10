#include "usercontroller.h"

#include <QDebug>

#include "user.h"
#include "authcontroller.h"

struct UserController::impl_t
{
    User user;
};

UserController* UserController::instance() noexcept
{
    static UserController uc;
    return &uc;
}

QString UserController::username() const noexcept
{
    return impl().user.username;
}

QString UserController::password() const noexcept
{
    return impl().user.password;
}

UserController::UserController()
{
    createImpl();

    QObject::connect(AuthController::instance(), &AuthController::loggedIn, this, [this](const User& user)
    {
        impl().user = user;
    });

    QObject::connect(AuthController::instance(), &AuthController::loggedOut, this, [this]()
    {
        impl().user.username = "";
        impl().user.password = "";
    });
}

UserController::~UserController()
{

}
