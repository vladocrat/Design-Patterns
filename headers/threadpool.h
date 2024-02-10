#pragma once

#include <QThread>
#include <QObject>
#include <QFuture>

#include <memory>
#include <functional>

#include "pimpl.h"
#include "downloadworker.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance() noexcept;

    void initialize(size_t poolSize) noexcept;

    template<typename Functor, typename... Args>
    auto start(Functor&& f, Args&&... args)
    {
        //! Bind arguments to the functor
        std::function<decltype(f(args...))()> func = std::bind(std::forward<Functor>(f), std::forward<Args>(args)...);

        //! Package the function to use in async env
        std::packaged_task<typename std::result_of<Functor(Args...)>::type()> task(std::bind(std::forward<Functor>(f), std::forward<Args>(args)...));

        //! Get future to refer to later for the result
        std::future<typename std::result_of<Functor(Args...)>::type> future = task.get_future();

        auto worker = new DownloadWorker(task);
        auto thread = get();
        worker->moveToThread(thread.get());

        QObject::connect(thread.get(), &QThread::finished, this, &ThreadPool::release);
        QObject::connect(worker, &DownloadWorker::finished, this, &DownloadWorker::deleteLater);

        worker->start();

        return future;
    }

    [[nodiscard]] std::shared_ptr<QThread> get() noexcept;

signals:
    void threadFreed();

private slots:
    void release(const std::shared_ptr<QThread>& thread) noexcept;

private:
    ThreadPool();
    ~ThreadPool() = default;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    DECLARE_PIMPL
};

