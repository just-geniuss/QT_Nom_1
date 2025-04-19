#ifndef LITERATURE_H
#define LITERATURE_H

#include <QString>
#include <QStringList>
#include <QJsonObject>

// Структура для хранения информации о произведении
struct Literature {
    QString uid;    // Уникальный идентификатор
    QString title;  // Название произведения
    QString author; // Автор произведения

    // Конструктор с параметрами для инициализации всех полей
    Literature(const QString& id, const QString& t, const QString& a)
        : uid(id), title(t), author(a) {}

    // Конструктор по умолчанию, инициализирует поля пустыми строками
    Literature() : uid(""), title(""), author("") {}

    // Метод для конвертации объекта в JSON объект
    QJsonObject toJson() const {
        QJsonObject json;
        json["uid"] = uid;
        json["title"] = title;
        json["author"] = author;
        return json;
    }

    // Статический метод для создания объекта Literature из JSON объекта
    static Literature fromJson(const QJsonObject& json) {
        return Literature(
            json["uid"].toString(),
            json["title"].toString(),
            json["author"].toString()
        );
    }
};

#endif // LITERATURE_H
