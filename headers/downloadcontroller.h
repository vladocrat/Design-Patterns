#pragma once

#include <QObject>

class DownloadController final : public QObject
{
    Q_OBJECT
public:
    static DownloadController* instance() noexcept;

    Q_INVOKABLE void download(QVariantList, const QString& path) const noexcept;

    static void registerType() noexcept;

private:
    DownloadController() = default;
    ~DownloadController() = default;
    DownloadController(const DownloadController&) = delete;
    DownloadController(DownloadController&&) = delete;
    DownloadController& operator=(const DownloadController&) = delete;
    DownloadController& operator=(DownloadController&&) = delete;
};
