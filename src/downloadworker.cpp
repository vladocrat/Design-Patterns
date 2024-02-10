#include "downloadworker.h"


struct DownloadWorker::impl_t
{
    std::function<void()> m_task;
};

DownloadWorker::DownloadWorker(std::function<void()> f)
{
    createImpl();

    impl().m_task = f;
}

DownloadWorker::~DownloadWorker()
{

}

void DownloadWorker::run()
{
    impl().m_task();
    emit finished();
}
