#include "filesaver.h"

#include <QFile>
#include <QDebug>

FileSaver::FileSaver()
{

}

bool FileSaver::save(const QByteArray& data, const QString& path) const noexcept
{
    qDebug() << path; //! TODO remove
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(data);
    file.close();
    return true;
}
