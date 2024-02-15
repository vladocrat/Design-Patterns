#pragma once

#include <QObject>

#include "pimpl.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance() noexcept;

    void initialize(size_t poolSize) noexcept;
    size_t size() const noexcept;

    void setSavePath(const QString& path) noexcept;

    void addTask(const QString& fileName, const QByteArray& data);

signals:
    void taskCompleted(QString fileName);

private:
    ThreadPool();
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    DECLARE_PIMPL
};

