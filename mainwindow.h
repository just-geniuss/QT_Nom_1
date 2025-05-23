#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "librarymanager.h"
#include "literaturemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
    LibraryManager manager;
    LiteratureModel *model;

    void updateTable();
};

#endif // MAINWINDOW_H
