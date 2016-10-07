#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QPointF>
#include <QStringList>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(const QString &source, QObject *parent = 0);
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    // edit the data
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;
    // split the data
    QPointF splitter(const QString& str);
    // return the data
    QList<QPointF> getValues();
private:
    QList<float> x;
    QList<float> y;
    QStringList item;
    QList<QPointF> plist;
};

#endif // MYMODEL_H
