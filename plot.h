#ifndef PLOT_H
#define PLOT_H
#include "ui_mywindow.h"
#include "mywindow.h"
#include <QAbstractItemView>
#include <QObject>
#include <QVector>
#include <QPointF>

class Plot : public QAbstractItemView
{
    Q_OBJECT

public:
    Plot(QWidget *parent = 0);
    QList<float> mmval(const QVector<QPointF> &mfp);
    QList<QPointF> sort(const QVector<QPointF>& unsort);
    QPointF proportion(const QPointF &value, const float& maxvalx, const float& maxvaly, const int& pxs);
    QRect visualRect(const QModelIndex &index) const;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
    QModelIndex indexAt(const QPoint &point) const;
protected:
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,Qt::KeyboardModifiers modifiers);
    int horizontalOffset() const;
    int verticalOffset() const;
    bool isIndexHidden(const QModelIndex &index) const;
    void setSelection(const QRect&, QItemSelectionModel::SelectionFlags command);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;
    void paintEvent(QPaintEvent *event);
protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
private:
    int rows(const QModelIndex &index = QModelIndex()) const;
    int pxs;
};

#endif // PLOT_H


