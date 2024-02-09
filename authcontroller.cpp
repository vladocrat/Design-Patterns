#include "authcontroller.h"

#include <QQmlEngine>

AuthController* AuthController::instance() noexcept
{
    static AuthController ac;
    return &ac;
}

void AuthController::login(const QString& username, const QString& password) noexcept
{
    emit loggedIn({username, password});
}

void AuthController::registerType()
{

}

AuthController::AuthController()
{

}
