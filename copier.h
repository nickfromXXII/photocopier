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

signals:
    void progress(int);
    void ready(const QString&);

};

#endif // COPIER_H
