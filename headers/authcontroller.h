#pragma once

#include <QObject>

#include "user.h"

class AuthController final : public QObject
{
    Q_OBJECT
public:
    static AuthController* instance() noexcept;

    Q_INVOKABLE void login(const QString& username, const QString& password) noexcept;
    Q_INVOKABLE void logout() noexcept;

    static void registerType();

signals:
    void loggedIn(const User&);
    void loggedOut();
    void dataChanged(const QString&, const QString&);

private:
    AuthController();
    ~AuthController() = default;
    AuthController(const AuthController&) = delete;
    AuthController(AuthController&&) = delete;
    AuthController& operator=(const AuthController&) = delete;
    AuthController& operator=(AuthController&&) = delete;
};

