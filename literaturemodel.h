#ifndef LITERATUREMODEL_H
#define LITERATUREMODEL_H

#include <QAbstractTableModel>
#include "literature.h"
#include <QList>

class LiteratureModel : public QAbstractTableModel {
    Q_OBJECT
public:
    LiteratureModel(QObject *parent = nullptr);
    void setData(const QList<Literature> &data);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void addLiterature(const Literature &lit);
    bool removeLiterature(const QString &uid);
    bool updateLiterature(const QString &uid, const Literature &newLit);

    Literature getLiterature(const QModelIndex &index) const;

private:
    QList<Literature> library;
};

#endif // LITERATUREMODEL_H
