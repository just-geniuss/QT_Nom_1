#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QUuid>

// Конструктор главного окна приложения
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new LiteratureModel(this)) // создаём модель и передаём ей this как родителя
{
    ui->setupUi(this);                      // инициализируем UI
    ui->tableView->setModel(model);         // устанавливаем модель в таблицу
    ui->tableView->setColumnHidden(0,true); // Скрываем колонку с uid
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // колонки на всю ширину tableView
    updateTable();                          // обновляем отображение данных
}

// Деструктор окна, освобождает ресурсы UI
MainWindow::~MainWindow() {
    delete ui;
}

// Обновляет данные в таблице из менеджера
void MainWindow::updateTable() {
    model->setData(manager.library);  // передаём QList из менеджера в модель
}

// Слот обработки нажатия на кнопку "Добавить"
void MainWindow::on_addButton_clicked() {
    QString uid = QUuid::createUuid().toString();  // Генерируем уникальный идентификатор
    QString title = ui->titleLineEdit->text();     // Получаем название из поля ввода
    QString author = ui->authorLineEdit->text();   // Получаем автора из поля ввода
    if (!title.isEmpty() && !author.isEmpty()) {
        Literature lit = {uid, title, author};     // Создаём объект литературы
        manager.addLiterature(lit);                // Добавляем в менеджер
        model->addLiterature(lit);                 // Обновляем таблицу
    }
}

// Слот обработки нажатия на кнопку "Удалить"
void MainWindow::on_deleteButton_clicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();  // Получаем текущую выбранную строку
    if (currentIndex.isValid()) {
        QString uid = model->getLiterature(currentIndex).uid;  // Получаем UID из модели
        manager.removeLiterature(uid);                         // Удаляем литературу по UID
        model->removeLiterature(uid);                          // Обновляем таблицу
    }
}

// Слот обработки нажатия на кнопку "Сохранить"
void MainWindow::on_saveButton_clicked() {
    QFileDialog dialog(this);                         // Создаём диалог выбора файла
    dialog.setAcceptMode(QFileDialog::AcceptSave);    // Режим — сохранить
    dialog.setNameFilter("JSON Files (*.json)");      // Фильтр — только JSON
    dialog.setDefaultSuffix("json");                  // Расширение по умолчанию — .json

    if (dialog.exec() == QDialog::Accepted) {         // Если файл выбран
        QString filePath = dialog.selectedFiles().first();  // Получаем путь
        manager.saveToJSON(filePath);                 // Сохраняем данные
    }
}

// Слот обработки нажатия на кнопку "Загрузить"
void MainWindow::on_loadButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON", "", "JSON Files (*.json)");
    if (!filePath.isEmpty()) {
        manager.loadFromJSON(filePath);  // Загружаем данные
        updateTable();                   // Обновляем таблицу
    }
}

// Слот обработки нажатия на кнопку "Изменить"
void MainWindow::on_editButton_clicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();  // Получаем выбранную строку
    if (currentIndex.isValid()) {
        QString uid = model->getLiterature(currentIndex).uid;  // UID текущей записи
        QString title = ui->titleLineEdit->text();
        QString author = ui->authorLineEdit->text();
        if (!title.isEmpty() && !author.isEmpty()) {
            Literature newLit = {uid, title, author};  // Обновлённая запись
            manager.updateLiterature(uid, newLit);     // Обновляем в менеджере
            model->updateLiterature(uid, newLit);      // Обновляем таблицу
        }
    }
}


