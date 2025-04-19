#include "literaturemodel.h"
#include "qregularexpression.h"

// Конструктор модели, инициализирует базовый QAbstractTableModel с указанным родителем.
LiteratureModel::LiteratureModel(QObject *parent) : QAbstractTableModel(parent) {}

// Метод устанавливает новые данные (QList с литературой) и сообщает модели, что данные обновились.
void LiteratureModel::setData(const QList<Literature> &data) {
    beginResetModel();   // сигнализируем начало сброса модели
    library = data;      // сохраняем новые данные
    endResetModel();     // сигнализируем завершение сброса модели
}

// Возвращает количество строк в таблице, равное количеству записей в библиотеке.
int LiteratureModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return library.size();
}

// Возвращает количество колонок — UID, Название и Автор.
int LiteratureModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3; // UID, Title, Author
}

void LiteratureModel::addLiterature(const Literature &lit) {
    int row = library.size(); // индекс новой строки
    beginInsertRows(QModelIndex(), row, row); // сообщаем о вставке новой строки
    library.append(lit);                     // вставляем новую запись в QList
    endInsertRows();                          // завершаем вставку строки
}

bool LiteratureModel::removeLiterature(const QString &uid) {
    for (int i = 0; i < library.size(); ++i) {
        if (library.at(i).uid == uid) {
            beginRemoveRows(QModelIndex(), i, i);
            library.removeAt(i);
            endRemoveRows();
            return true;
        }
    }
    return false;
}

bool LiteratureModel::updateLiterature(const QString &uid, const Literature &newLit) {
    for (int i = 0; i < library.size(); ++i) {
        if (library.at(i).uid == uid) {
            library[i] = newLit;
            QModelIndex topLeft = index(i, 0);
            QModelIndex bottomRight = index(i, columnCount() - 1);
            emit dataChanged(topLeft, bottomRight);
            return true;
        }
    }
    return false;
}

// Возвращает данные для отображения в ячейках таблицы.
// Используется только роль DisplayRole (т.е. для вывода текста).
QVariant LiteratureModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        const Literature &lit = library.at(index.row()); // получаем литературу по индексу строки
        switch (index.column()) {
        case 0: return lit.uid;     // UID
        case 1: return lit.title;   // Название
        case 2: return lit.author;  // Автор
        }
    }
    return QVariant();  // если роль не поддерживается или индекс некорректен
}

// Устанавливает заголовки колонок таблицы.
// Отображаются только горизонтальные заголовки и только при DisplayRole.
QVariant LiteratureModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "UID";
        case 1: return "Название";
        case 2: return "Автор";
        }
    }
    return QVariant();
}

// Возвращает объект Literature по индексу строки — удобно для обработки событий (например, выбора записи).
Literature LiteratureModel::getLiterature(const QModelIndex &index) const {
    return library.at(index.row());
}

