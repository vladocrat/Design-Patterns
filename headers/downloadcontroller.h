#pragma once

#include <QObject>

#include "pimpl.h"

class DownloadController final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float progress READ progress NOTIFY progressChanged FINAL)
public:
    static DownloadController* instance() noexcept;

    Q_INVOKABLE void download(const QStringList& files, const QString& path, const QString& threadNum) noexcept;
    Q_INVOKABLE float progress();

    static void registerType() noexcept;

signals:
    void progressChanged();
    void fileSaved(const QString& fileName);

private:
    void downloadFiles();

    DownloadController();
    ~DownloadController();
    DownloadController(const DownloadController&) = delete;
    DownloadController(DownloadController&&) = delete;
    DownloadController& operator=(const DownloadController&) = delete;
    DownloadController& operator=(DownloadController&&) = delete;

    DECLARE_PIMPL
};
