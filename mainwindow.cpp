#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QString rootPath = QDir::homePath();
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(rootPath);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    ui->treeView->setModel(model);
    if (!rootPath.isEmpty()) {
        const QModelIndex rootIndex = model->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            ui->treeView->setRootIndex(rootIndex);
    }

    ui->treeView->setAnimated(false);
    ui->treeView->setIndentation(20);
    ui->treeView->setSortingEnabled(true);

    setWindowTitle(QObject::tr("Dir View"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    ui->treeView->resizeColumnToContents(0);
}

