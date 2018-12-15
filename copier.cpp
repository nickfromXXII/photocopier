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
    int filesToCopy = QDir(src).count();
    int copied = 0;
    while (photosDir.hasNext()) {
        QFileInfo photo(photosDir.next());
        QDate shotDate = photo.birthTime().date();
        if (shotDate != lastPhotoShotDay) {
            destDir.mkdir(shotDate.toString("d.M.yyyy"));
        }
        qDebug() << photo.filePath() << " " << destDir.path() + "/" + shotDate.toString("d.M.yyyy") + "/"
                    + photo.fileName();
        QFile::copy(
                    photo.filePath(),
                    destDir.path() + "/" + shotDate.toString("d.M.yyyy") + "/" + photo.fileName()
                    );
        copied++;
        qDebug() << copied << "/" << filesToCopy << " " << int(double(copied)/double(filesToCopy)*100.0);
        emit progress(int(double(copied)/double(filesToCopy)*100.0));
    }

    emit ready("Successfully copied");
}

void Copier::setPath(const QString &src, const QString dest)
{
    this->src = src;
    this->dest = dest;
}
