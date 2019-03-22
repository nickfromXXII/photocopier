#ifndef COPIER_H
#define COPIER_H

#include <QThread>

class Copier : public QObject
{
    Q_OBJECT

public:
    void setPath(const QString& src, const  QString dest);

public slots:
    void copy();

private:
    QString src;
    QString dest;

    struct Postfix {
        QString year;
        QString month;
        QString day;

        Postfix(QString y, QString m, QString d) : year(y), month(m), day(d) {}

        QString toString() {
            return "/" + year + "/" + month + "/" + day + "/";
        }
    };

signals:
    void progress(int);
    void ready();

};

#endif // COPIER_H
