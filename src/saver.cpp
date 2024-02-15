#include "saver.h"

#include <QFileInfo>
#include <QByteArray>
#include <QDebug>

struct Saver::impl_t
{
    QString path;
    QByteArray data;
};

Saver::Saver()
{
    createImpl();
}

Saver::~Saver()
{
}

void Saver::setData(QString fileName, QByteArray data)
{
    impl().path = fileName;
    impl().data = data;
}

QString Saver::taskName() const
{
    QFileInfo info(impl().path);
    return info.fileName();
}

void Saver::save() noexcept
{
    QFile file(impl().path.remove("file:///"));

    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Failed to open file: " << impl().path;
        emit error(file.errorString());
        return;
    }

    file.write(impl().data);
    file.close();

    emit saved(impl().path);
}

