#pragma once

#include <QObject>

class FileSaver final : public QObject
{
    Q_OBJECT
public:
    FileSaver();

    [[nodiscard]] bool save(const QByteArray& data, const QString& path) const noexcept;
};

