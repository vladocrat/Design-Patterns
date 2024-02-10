#include "downloadcontroller.h"

#include <QQmlEngine>

DownloadController* DownloadController::instance() noexcept
{
    static DownloadController dc;
    return &dc;
}

void DownloadController::download(QVariantList list) noexcept
{

}

void DownloadController::registerType() noexcept
{
    qmlRegisterSingletonInstance("DownloadController", 1, 0, "DownloadController", DownloadController::instance());
}
