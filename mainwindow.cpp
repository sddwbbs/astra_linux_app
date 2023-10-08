#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , proxyModel(new QSortFilterProxyModel(this))
    , model(new QFileSystemModel(this))
    , rootPath(QDir::homePath())
{
    ui->setupUi(this);
    resize(600, 600);

    model->setRootPath(rootPath);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    col = model->columnCount();

    proxyModel->setSourceModel(model);
    ui->treeView->setModel(proxyModel);

    const QModelIndex rootIndex = proxyModel->mapFromSource(model->index(QDir::cleanPath(rootPath)));

    if (rootIndex.isValid()) {
        ui->treeView->setRootIndex(rootIndex);
    }

    ui->treeView->setIndentation(30);
    ui->treeView->setSortingEnabled(true);

    QTimer::singleShot(0, this, SLOT(resizeColumn()));
    connect(ui->treeView, &QTreeView::expanded, this, &MainWindow::resizeColumn);
    connect(ui->treeView, &QTreeView::collapsed, this, &MainWindow::resizeColumn);

    setWindowTitle(tr("Дерево файлов"));
    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete ui;
}

void MainWindow::readSettings()
{
    QSettings settings("MySoft", "MyProgram");

    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("position", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings("MySoft", "MyProgram");

    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();
}

void MainWindow::resizeColumn()
{
    for (int i = 0; i < col; ++i) {
        ui->treeView->resizeColumnToContents(i);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    if (curLen > text.length()) {
        resetFilter();
    } else {
        curLen = text.length();
    }

    if (!text.isEmpty()) {
        ui->lineEdit->setClearButtonEnabled(true);
        QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::Wildcard);
        proxyModel->setRecursiveFilteringEnabled(true);
        proxyModel->setFilterKeyColumn(curIndex);
        proxyModel->setFilterRegExp(regExp);
    } else {
        curLen = 0;
        resetFilter();
    }
}

void MainWindow::resetFilter() {
    proxyModel->setFilterRegExp(QRegExp());
    const QModelIndex rootIndex = proxyModel->mapFromSource(model->index(QDir::cleanPath(rootPath)));

    if (rootIndex.isValid()) {
        ui->treeView->setRootIndex(rootIndex);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int newIndex)
{
    curIndex = newIndex;
}

