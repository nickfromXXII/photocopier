#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>
#include <QProgressBar>
#include <QSettings>

#include "copier.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout* mainLay;

    QHBoxLayout* srcCatalogLay;
    QLineEdit* srcCatalogPath;
    QPushButton* srcCatalogSelect;

    QHBoxLayout* destCatalogLay;
    QLineEdit* destCatalogPath;
    QPushButton* destCatalogSelect;

    QPushButton* copyBtn;
    QProgressBar* copyProgress;

    void setupUI();

private slots:
    void srcCatalogSelectClicked();
    void destCatalogSelectClicked();
    void copyBtnClicked();

};

#endif // MAINWINDOW_H
