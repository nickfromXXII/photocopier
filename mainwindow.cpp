#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QCoreApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QCoreApplication::setOrganizationName("Nikita Mironov");
    QCoreApplication::setApplicationName("Photocopier");
    setupUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget;
    mainLay = new QVBoxLayout(centralWidget);

    QSettings settings("Nikita Mironov", "Photocopier");
    srcCatalogLay = new QHBoxLayout;
    srcCatalogPath = new QLineEdit(settings.value("path/lastSrc").toString());
    srcCatalogSelect = new QPushButton("Select source...");
    srcCatalogLay->addWidget(srcCatalogPath);
    srcCatalogLay->addWidget(srcCatalogSelect);

    destCatalogLay = new QHBoxLayout;
    destCatalogPath = new QLineEdit(settings.value("path/lastDest").toString());
    destCatalogSelect = new QPushButton("Select destination...");
    destCatalogLay->addWidget(destCatalogPath);
    destCatalogLay->addWidget(destCatalogSelect);

    copyBtn = new QPushButton("Copy");

    copyProgress = new QProgressBar;
    copyProgress->setAlignment(Qt::AlignCenter);

    mainLay->addStretch();
    mainLay->addLayout(srcCatalogLay);
    mainLay->addLayout(destCatalogLay);
    mainLay->addWidget(copyBtn);
    mainLay->addWidget(copyProgress);
    mainLay->addStretch();

    setCentralWidget(centralWidget);

    connect(srcCatalogSelect, SIGNAL(clicked()), this, SLOT(srcCatalogSelectClicked()));
    connect(destCatalogSelect, SIGNAL(clicked()), this, SLOT(destCatalogSelectClicked()));
    connect(copyBtn, SIGNAL(clicked()), this, SLOT(copyBtnClicked()));
}

void MainWindow::srcCatalogSelectClicked()
{
    srcCatalogPath->setText(QFileDialog::getExistingDirectory(this, "Get source directory"));
    QSettings settings("Nikita Mironov", "Photocopier");
    settings.setValue("path/lastSrc", srcCatalogPath->text());
}

void MainWindow::destCatalogSelectClicked()
{
    destCatalogPath->setText(QFileDialog::getExistingDirectory(this, "Get destination directory"));
    QSettings settings("Nikita Mironov", "Photocopier");
    settings.setValue("path/lastDest", destCatalogPath->text());
}

void MainWindow::copyBtnClicked()
{
    copyProgress->reset();

    QThread* copyThread = new QThread(this);
    Copier* copier = new Copier;
    copier->setPath(srcCatalogPath->text(), destCatalogPath->text());
    copier->moveToThread(copyThread);

    connect(copyThread, SIGNAL(finished()), copier, SLOT(deleteLater()));
    connect(copyThread, SIGNAL(started()), copier, SLOT(copy()));
    connect(copier, SIGNAL(progress(int)), copyProgress, SLOT(setValue(int)));

    copyThread->start();
}
