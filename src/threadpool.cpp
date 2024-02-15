#include "threadpool.h"

#include <QMutexLocker>
#include <QDebug>
#include <QVector>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>
#include <QThread>
#include <QFileInfo>

#include "saver.h"

struct ThreadPool::impl_t
{
    size_t busy {0};
    size_t size {0};
    QString savePath;
    QQueue<QPair<QString, QByteArray>> requests;
};

ThreadPool* ThreadPool::instance() noexcept
{
    static ThreadPool pl;
    return &pl;
}

ThreadPool::ThreadPool()
{
    createImpl();
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::initialize(size_t poolSize) noexcept
{
    impl().size = poolSize;
}

size_t ThreadPool::size() const noexcept
{
    return impl().size;
}

void ThreadPool::setSavePath(const QString& path) noexcept
{
    impl().savePath = path;
}

void ThreadPool::addTask(const QString& fileName, const QByteArray& data)
{
    if (impl().busy >= impl().size)
    {
        impl().requests.push_back({fileName, data});
        return;
    }

    Saver* saver = new Saver;
    saver->setData(impl().savePath + "/" + fileName, data);

    QThread* thread = new QThread;
    thread->start();

    QObject::connect(saver, &Saver::error, this, [this, saver, thread](const QString& error)
    {
        --impl().busy;

        emit taskCompleted(saver->taskName());

        saver->deleteLater(); //! TODO(check if removed from another thread)
        thread->quit();

        if (impl().busy < impl().size && !impl().requests.empty())
        {
            auto [name, data_] = impl().requests.takeFirst();
            addTask(name, data_);
            return;
        }
    }, Qt::QueuedConnection);

    QObject::connect(saver, &Saver::saved, this, [this, saver, thread] ()
    {
        --impl().busy;

        emit taskCompleted(saver->taskName());

        saver->deleteLater(); //! TODO(check if removed from another thread)
        thread->quit();

        if (impl().busy < impl().size && !impl().requests.empty())
        {
            auto [name, data_] = impl().requests.takeFirst();
            addTask(name, data_);
            return;
        }
    }, Qt::QueuedConnection);

    saver->moveToThread(thread);
    ++impl().busy;

    QMetaObject::invokeMethod(saver, &Saver::save, Qt::QueuedConnection);
}
