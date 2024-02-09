#include "usercontroller.h"

#include "user.h"

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

}

QString UserController::password() const noexcept
{

}

UserController::UserController()
{
    createImpl();
}

UserController::~UserController()
{

}
