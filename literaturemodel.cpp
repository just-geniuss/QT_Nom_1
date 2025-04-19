#include "literaturemodel.h"
#include "qregularexpression.h"

// Реализация конструктора модели
// Просто вызывает конструктор базового класса с переданным родителем
LiteratureModel::LiteratureModel(QObject *parent) : QAbstractTableModel(parent) {}

// Реализация метода установки данных в модель
void LiteratureModel::setData(const QLinkedList<Literature> &data) {
    // beginResetModel сообщает представлениям (таблицам), что модель будет полностью обновлена
    beginResetModel();   
    // Копируем новые данные
    library = data;      
    // endResetModel сообщает, что обновление завершено и представления должны перерисоваться
    endResetModel();     
}

// Реализация метода для получения количества строк в модели
int LiteratureModel::rowCount(const QModelIndex &parent) const {
    // Q_UNUSED игнорирует неиспользуемый параметр (подавляет предупреждение компилятора)
    Q_UNUSED(parent);
    // Количество строк равно размеру нашего списка
    return library.size();
}

// Реализация метода для получения количества столбцов в модели
int LiteratureModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    // У нас 3 столбца: UID, Название и Автор
    return 3; 
}

// Реализация метода добавления нового произведения в модель
void LiteratureModel::addLiterature(const Literature &lit) {
    // Индекс новой строки будет равен текущему размеру списка
    int row = library.size(); 
    // Сообщаем представлениям о начале вставки новой строки
    beginInsertRows(QModelIndex(), row, row); 
    // Добавляем произведение в список
    library.append(lit);                     
    // Сообщаем представлениям о завершении вставки
    endInsertRows();                          
}

// Реализация метода удаления произведения из модели
bool LiteratureModel::removeLiterature(const QString &uid) {
    // Ищем произведение по UID
    int i = 0;
    for (auto it = library.begin(); it != library.end(); ++it, ++i) {
        if (it->uid == uid) {
            // Сообщаем представлениям о начале удаления строки
            beginRemoveRows(QModelIndex(), i, i);
            // Удаляем элемент из списка
            library.erase(it);
            // Сообщаем представлениям о завершении удаления
            endRemoveRows();
            return true;
        }
    }
    return false; // Произведение не найдено
}

// Реализация метода обновления произведения в модели
bool LiteratureModel::updateLiterature(const QString &uid, const Literature &newLit) {
    // Ищем произведение по UID
    int i = 0;
    for (auto it = library.begin(); it != library.end(); ++it, ++i) {
        if (it->uid == uid) {
            // Обновляем элемент
            *it = newLit;
            // Создаем индексы для левого верхнего и правого нижнего углов обновляемой области
            QModelIndex topLeft = index(i, 0);
            QModelIndex bottomRight = index(i, columnCount() - 1);
            // Сигнализируем представлениям, что данные изменились
            emit dataChanged(topLeft, bottomRight);
            return true;
        }
    }
    return false; // Произведение не найдено
}

// Реализация метода получения данных для ячейки таблицы
QVariant LiteratureModel::data(const QModelIndex &index, int role) const {
    // Qt::DisplayRole - это роль для отображения текста в ячейке
    if (role == Qt::DisplayRole) {
        // Получаем произведение по индексу строки
        int i = 0;
        auto it = library.begin();
        while (i < index.row() && it != library.end()) {
            ++it;
            ++i;
        }
        
        if (it != library.end()) {
            const Literature &lit = *it;
            // В зависимости от столбца возвращаем разные поля
            switch (index.column()) {
            case 0: return lit.uid;     // UID
            case 1: return lit.title;   // Название
            case 2: return lit.author;  // Автор
            }
        }
    }
    // Если роль не поддерживается или индекс некорректен, возвращаем пустой QVariant
    return QVariant();  
}

// Реализация метода для получения заголовков столбцов/строк
QVariant LiteratureModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Обрабатываем только горизонтальные заголовки (столбцы) для роли отображения
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        // В зависимости от номера столбца возвращаем разные заголовки
        switch (section) {
        case 0: return "UID";
        case 1: return "Название";
        case 2: return "Автор";
        }
    }
    return QVariant();
}

// Реализация метода для получения произведения по индексу модели
Literature LiteratureModel::getLiterature(const QModelIndex &index) const {
    // Получаем произведение по индексу строки
    int i = 0;
    auto it = library.begin();
    while (i < index.row() && it != library.end()) {
        ++it;
        ++i;
    }
    
    if (it != library.end()) {
        return *it;
    }
    
    return Literature(); // Возвращаем пустое произведение, если индекс некорректен
}

