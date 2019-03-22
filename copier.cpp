#include "copier.h"

#include <QDirIterator>
#include <QDate>
#include <QDebug>
#include <QDir>

void Copier::copy()
{
    QDirIterator photosDir(src, QDirIterator::NoIteratorFlags);
    QDate lastPhotoShotDay;
    QDir destDir(dest);
    uint filesToCopy = QDir(src).count();
    int copied = 0;
    while (photosDir.hasNext()) {
        QFileInfo photo(photosDir.next());
        QDate shotDate = photo.birthTime().date();
        Postfix postfix(
                    shotDate.toString("yyyy"),
                    shotDate.toString("MM.yyyy"),
                    shotDate.toString("dd.MM")
                        );
        if (shotDate != lastPhotoShotDay) {
            destDir.mkpath(postfix.toString());
        }
        QFile::copy(
                    photo.filePath(),
                    destDir.path() + postfix.toString() + photo.fileName()
                    );
        copied++;
        emit progress(int(double(copied)/double(filesToCopy)*100.0));
    }

    emit ready();
}

void Copier::setPath(const QString &src, const QString dest)
{
    this->src = src;
    this->dest = dest;
}
