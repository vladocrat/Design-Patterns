#pragma once

#include <QThread>
#include <QObject>

#include <memory>

#include "pimpl.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance() noexcept;

    void initialize(size_t poolSize) noexcept;
    [[nodiscard]] std::shared_ptr<QThread> get() noexcept;

private:
    void release(const std::shared_ptr<QThread>& thread) noexcept;

    ThreadPool();
    ~ThreadPool() = default;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    DECLARE_PIMPL
};

