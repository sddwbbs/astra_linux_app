#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>
#include <QApplication>
#include <QTreeView>
#include <QTimer>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSortFilterProxyModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void resizeColumn();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void readSettings();
    void writeSettings();
    int col = 0;
    int curIndex = 0;
    int curLen = 0;
    QSortFilterProxyModel *proxyModel;
    QFileSystemModel *model;
    const QString rootPath;
    void resetFilter();
};
#endif // MAINWINDOW_H
