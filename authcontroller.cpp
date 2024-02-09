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
    emit dataChanged(username, password);
}

void AuthController::logout() noexcept
{
    emit loggedOut();
}

void AuthController::registerType()
{
    qmlRegisterSingletonInstance("AuthController", 1, 0, "AuthController", AuthController::instance());
}

AuthController::AuthController()
{

}
