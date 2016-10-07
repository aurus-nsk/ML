#include "mywindow.h"
#include "mymodel.h"
#include "predict.h"
#include "plot.h"
#include "ui_mywindow.h"
#include <QtGui>
#include <QPointF>
#include <QVector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <QAbstractItemView>
#include <QDebug>
Plot::Plot(QWidget *parent) : QAbstractItemView(parent)
{
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
    pxs=500;
}
void Plot::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(viewport());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::blue);
    //draw our data from model
    QPointF fp;
    QVector<QPointF> xy;
    for (int row = 0; row < model()->rowCount(rootIndex()); ++row){
        QModelIndex xindex = model()->index(row, 0, rootIndex());
        QModelIndex yindex = model()->index(row, 1, rootIndex());
        fp.setX(model()->data(xindex).toFloat());
        fp.setY(model()->data(yindex).toFloat());
        xy.append(fp);
    }
    QList<float> mxy(mmval(xy));
    for (int row = 0; row < model()->rowCount(rootIndex()); ++row){
        QModelIndex xindex = model()->index(row, 0, rootIndex());
        QModelIndex yindex = model()->index(row, 1, rootIndex());
        fp.setX(model()->data(xindex).toFloat());
        fp.setY(model()->data(yindex).toFloat());
        //draw points in the new coordinate system
        p.drawEllipse(proportion(fp,mxy.at(0),mxy.at(1),pxs),2,2);
    }
            //initialize parameters of linear regression
            Predict predict(xy,0.01,1500);
            //find the optimum values for theta
            predict.GradDesc();
            //compute the CostFunction with opt.theta
            predict.Costfunction();
            //compute the Hypothesis
            QVector<QPointF> hx(predict.Hypothesis());
            QList<float> mhx(mmval(hx));
            QVector<QPointF> Nhx;
            foreach (QPointF temp, hx){
                Nhx.append(proportion(temp,mhx.at(0),mhx.at(1),pxs));
            }
            //draw hypothesis points
            /*p.setPen(Qt::red);
            for(int m=0; m< Nhx.size(); ++m){
                p.drawEllipse(Nhx.at(m),2,2);
            }
            */
            //draw only hypothesis line
            QList<QPointF> hxline(sort(Nhx));
            p.setPen(Qt::red);
            p.drawLine(hxline.at(0),hxline.at(1));
            //draw axes of our new coordinate system
            p.setPen(Qt::black);
            //(num*500/100) == pxs*num%
            p.drawLine( QPoint( (10*pxs/100), pxs ), QPoint( pxs+(10*500/100), pxs ) ); //x
            p.drawLine( QPoint( (10*pxs/100), pxs ), QPoint( (10*pxs/100), 0 ) ); //y
            //name of axes and their max value
            QPoint point;
            point.setX(pxs/2+(10*pxs/100)/2);
            point.setY(pxs+(5*pxs/100));
            p.drawText(point,"X(population)");
            point.setX(pxs/100);
            point.setY(pxs/2+(5*pxs/100));
            p.drawText(point,"Y(profit)");
            //set the zero
            point.setX((8*pxs/100));
            point.setY(pxs);
            p.drawText(point,"0");
            //max val of x
            point.setX(pxs+(5*pxs/100));
            point.setY(pxs+(5*pxs/100));
            p.drawText(point,QString("%1").arg(mxy.at(0)));
            //max val of y
            point.setX((1*pxs/100));
            point.setY((3*pxs/100));
            p.drawText(point,QString("%1").arg(mxy.at(1)));
            //text sign
            p.setPen(Qt::red);
            point.setX(90*pxs/100);
            point.setY(88*pxs/100);
            p.drawText(point,"linear regression");
            //text sign
            p.setPen(Qt::blue);
            point.setX(90*pxs/100);
            point.setY(92*pxs/100);
            p.drawText(point,"training data");

    p.end();
}
// create a line from many points
QList<QPointF> Plot::sort(const QVector<QPointF>& unsort){

    QList<QPointF> line;
    QPointF tp;
    int num;
    QList<float> x,y;
    for (int i = 0; i<unsort.size();++i){
        x.append(unsort[i].x());
        y.append(unsort[i].y());
    }
    QList<float>::const_iterator it;
    it = std::max_element(x.begin(), x.end());
    tp.setX(*it);
    num = x.indexOf(*it);
    tp.setY(y.at(num));
    line.append(tp);
    it = std::min_element(x.begin(), x.end());
    tp.setX(*it);
    num = x.indexOf(*it);
    tp.setY(y.at(num));
    line.append(tp);
    return line;
}
//find max and min values
QList<float> Plot::mmval(const QVector<QPointF> &mfp){

    QVector<float> x,y;
    QList<float> mval;
    for(int i=0; i< mfp.size();++i){
        x.append(mfp[i].x());
        y.append(mfp[i].y());
    }
    QVector<float>::const_iterator it;
    it = std::max_element(x.begin(), x.end());
    mval.append(*it);
    it = std::max_element(y.begin(), y.end());
    mval.append(*it);
    it = std::min_element(x.begin(), x.end());
    mval.append(*it);
    it = std::min_element(y.begin(), y.end());
    mval.append(*it);
    return mval; //mval[0]==max(x); mval[1]==max(y);mval[2]==min(x); mval[3]==min(y);
}
//compute point on the widget in the new coordinate system
QPointF Plot::proportion(const QPointF &value, const float& maxvalx, const float& maxvaly, const int& pxs)
{
    QPointF revalue;
    float xpx,ypx;
    //compute x
    xpx=(value.x()*pxs)/maxvalx+(10*pxs/100);
    //compute y
    ypx=(value.y()*pxs)/maxvaly;
    ypx=pxs-ypx;
    //form the QPoint(x,y)
    revalue.setX(xpx);
    revalue.setY(ypx);
    return revalue;
}
//This slot is called when items are changed in the model.
void Plot::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);
    viewport()->update();
}
//Returns the model index of the item at the viewport coordinates point.
QModelIndex Plot::indexAt(const QPoint &point) const
{
    return QModelIndex();
}
//Returns true if the item at index is a hidden
bool Plot::isIndexHidden(const QModelIndex & /*index*/) const
{
    return false;
}
//Returns the view’s horizontal offset
int Plot::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}
//count rows in model
int Plot::rows(const QModelIndex &index) const
{
    return model()->rowCount(model()->parent(index));
}
//Returns a QModelIndex object pointing to the next object in the view,
//based on the given cursorAction and keyboard modifiers specified by modifiers.
QModelIndex Plot::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers /*modifiers*/)
{
    QModelIndex current = currentIndex();

    switch (cursorAction) {
        case MoveLeft:
        case MoveUp:
            if (current.row() > 0)
                current = model()->index(current.row() - 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(0, current.column(), rootIndex());
            break;
        case MoveRight:
        case MoveDown:
            if (current.row() < rows(current) - 1)
                current = model()->index(current.row() + 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(rows(current) - 1, current.column(),
                                         rootIndex());
            break;
        default:
            break;
    }
    viewport()->update();
    return current;
}
//Scrolls the view if necessary to ensure that the item at index is visible.
void Plot::scrollTo(const QModelIndex &index, ScrollHint)
{
    QRect area = viewport()->rect();
    QRect rect = visualRect(index);

    if (rect.left() < area.left())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + rect.left() - area.left());
    else if (rect.right() > area.right())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + qMin(
                rect.right() - area.right(), rect.left() - area.left()));

    if (rect.top() < area.top())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + rect.top() - area.top());
    else if (rect.bottom() > area.bottom())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + qMin(
                rect.bottom() - area.bottom(), rect.top() - area.top()));
    update();
}
//Applies the selection flags to the items in or touched by the rectangle, rect.
void Plot::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    update();
}
//Returns the vertical offset of the view.
int Plot::verticalOffset() const
{
    return verticalScrollBar()->value();
}
//Returns the rectangle occupied by the item at the given model index
QRect Plot::visualRect(const QModelIndex &index) const
{
    QRect rect;
    if (rect.isValid())
        return QRect(rect.left() - horizontalScrollBar()->value(),
                     rect.top() - verticalScrollBar()->value(),
                     rect.width(), rect.height());
    else
        return rect;
}
//Returns the viewport region for the items in the selection
QRegion Plot::visualRegionForSelection(const QItemSelection &selection) const
{
    int ranges = selection.count();

    if (ranges == 0)
        return QRect();

    QRegion region;
    for (int i = 0; i < ranges; ++i) {
        QItemSelectionRange range = selection.at(i);
        for (int row = range.top(); row <= range.bottom(); ++row) {
            for (int col = range.left(); col <= range.right(); ++col) {
                QModelIndex index = model()->index(row, col, rootIndex());
                region += visualRect(index);
            }
        }
    }
    return region;
}

