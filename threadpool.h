#pragma once

#include <QThread>
#include <QObject>
#include <QVector>
#include <QMutex>

#include <memory>

#include "pimpl.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance() noexcept;

    [[nodiscard]] std::shared_ptr<QThread> get() noexcept;
    void release(std::shared_ptr<QThread>& thread) noexcept;

private:
    ThreadPool() = default;
    ~ThreadPool() = default;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    DECLARE_PIMPL
};

