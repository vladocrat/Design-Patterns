#pragma once

#include <QThread>

#include "pimpl.h"

class DownloadWorker final : public QThread
{
    Q_OBJECT
public:
    DownloadWorker(std::function<void()>);
    ~DownloadWorker();

signals:
    void finished();

protected:
    void run() override;

private:
    DECLARE_PIMPL
};

