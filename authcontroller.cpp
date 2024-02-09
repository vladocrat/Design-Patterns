#include "authcontroller.h"

AuthController* AuthController::instance() noexcept
{
    static AuthController ac;
    return &ac;
}

void AuthController::login(const QString& username, const QString& password) noexcept
{
    emit loggedIn({username, password});
}

AuthController::AuthController()
{

}
