#ifndef MYWINDOW_H
#define MYWINDOW_H
#include "ui_mywindow.h"
#include "mymodel.h"
#include <QMainWindow>
#include <QList>
#include <QString>
#include <QTableView>
#include <QAbstractItemView>
class myWindow : public QMainWindow, public Ui::myWindow
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);
protected:
    void setupActions();
private slots:
    void linearR();
    void about();
private:
    QString source;
    QList<QString> dataList;
    QAbstractItemView *graph;
    QTableView *tableView;
    MyModel *tableModel;
};

#endif // MYWINDOW_H
