#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include "literature.h"
#include <QList>
#include <QString>

class LibraryManager {
public:
    QList<Literature> library;

    void addLiterature(const Literature &lit);
    void removeLiterature(const QString &uid);
    void updateLiterature(const QString &uid, const Literature &newLit);
    void loadFromJSON(const QString &filePath);
    void saveToJSON(const QString &filePath);
};

#endif // LIBRARYMANAGER_H
