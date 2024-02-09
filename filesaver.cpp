#include "filesaver.h"

#include <QFile>

FileSaver::FileSaver()
{

}

bool FileSaver::save(const QByteArray& data, const QString& path) const noexcept
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(data);
    file.close();
    return true;
}
