#pragma once

#include <QObject>

#include "user.h"

class AuthController final : public QObject
{
    Q_OBJECT
public:
    static AuthController* instance() noexcept;

    Q_INVOKABLE void login(const QString& username, const QString& password) noexcept;

signals:
    void loggedIn(const User&);

private:
    AuthController();
    ~AuthController() = default;

};

