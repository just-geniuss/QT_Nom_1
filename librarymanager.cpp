#include "librarymanager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QLinkedList>

// Добавляет новую литературу в коллекцию.
void LibraryManager::addLiterature(const Literature &lit) {
    library.append(lit);
}

// Удаляет литературу из коллекции по UID.
void LibraryManager::removeLiterature(const QString &uid) {
    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->uid == uid) {
            library.erase(it);
            break;
        }
    }
}

// Обновляет запись литературы, если UID уже существует в коллекции.
void LibraryManager::updateLiterature(const QString &uid, const Literature &newLit) {
    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->uid == uid) {
            *it = newLit;
            break;
        }
    }
}

// Загружает данные из JSON-файла.
// Очищает текущую коллекцию и добавляет записи из JSON-документа.
void LibraryManager::loadFromJSON(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        
        if (doc.isArray()) {
            QJsonArray litArray = doc.array();
            
            library.clear();  // очищаем текущие данные
            
            for (const QJsonValue &value : litArray) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    Literature lit = Literature::fromJson(obj);
                    library.append(lit);
                }
            }
        }
    }
    file.close();
}

// Сохраняет текущую коллекцию литературы в JSON-файл.
// Каждая запись преобразуется в JSON-объект и добавляется в массив.
void LibraryManager::saveToJSON(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonArray litArray;
        
        for (const Literature &lit : library) {
            litArray.append(lit.toJson());
        }
        
        QJsonDocument doc(litArray);
        file.write(doc.toJson());
    }
    file.close();
}
