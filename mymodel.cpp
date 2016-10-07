#include "mymodel.h"
#include <QPointF>
#include <QMainWindow>
#include <QDebug>

MyModel::MyModel(const QString &source,QObject *parent) : QAbstractTableModel(parent)
{
        QStringList list = source.split('\n');
        //to get our values of x,y
        foreach(QString mystr, list)
            plist.append(splitter(mystr));
}
QPointF MyModel::splitter(const QString& str){
    QPointF ptemp;
    item=str.split(',');
    for (int i = 0; i < item.size(); ++i){
        switch(i){
        case 0: ptemp.setX(item.at(i).toFloat()); break;
        case 1: ptemp.setY(item.at(i).toFloat()); break;
        }
    }
    return ptemp;
}
int MyModel::rowCount(const QModelIndex &parent ) const
{
   Q_UNUSED(parent);
   return plist.count();
}
int MyModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return item.count();
}
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
        if (role == Qt::DisplayRole){
                if (col == 0)
                    return plist[row].x();
                if (col == 1)
                    return plist[row].y();
        }
    return QVariant();
}
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section){
            case 0:
                return QString("X(in 10,000)");
            case 1:
                return QString("Y(in 10,000)");
            }
        }
        if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}
bool MyModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
        if (index.isValid() && (role == Qt::EditRole || role == Qt::DisplayRole)) {

                switch(index.column()){
                    case 0: plist[index.row()].setX(value.toFloat()); break;
                    case 1: plist[index.row()].setY(value.toFloat()); break;
                }
        emit dataChanged( index, index );
        return true;
        }
    return false;
}
Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
if (!index.isValid())
    return 0;
return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
QList<QPointF> MyModel::getValues()
{
    return plist;
}
