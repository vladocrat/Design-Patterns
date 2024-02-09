#pragma once

#include <QObject>

#include "pimpl.h"

class UserController final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QString password READ password NOTIFY passwordChanged FINAL)
public:
    static UserController* instance() noexcept;

    Q_INVOKABLE QString username() const noexcept;
    Q_INVOKABLE QString password() const noexcept;

signals:
    void usernameChanged();
    void passwordChanged();

private:
    UserController();
    ~UserController();
    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController& operator=(const UserController&) = delete;
    UserController& operator=(UserController&&) = delete;

    DECLARE_PIMPL
};

