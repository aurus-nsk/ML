#include "mywindow.h"
#include "mymodel.h"
#include "predict.h"
#include "plot.h"
#include "ui_mywindow.h"
#include <QtGui>
#include <QAbstractTableModel>
#include <QDockWidget>
#include <QTableView>
#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>

myWindow::myWindow(QWidget *parent) : QMainWindow(parent){
    setupUi(this);
    setupActions();
    setWindowTitle("Linear Regression");
    //Read the file
    QString filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        source = QString::fromUtf8(file.readAll());
    }
        //setup model
        tableModel=new MyModel(source,this);

        //setup view
        QSplitter *splitter = new QSplitter;

        graph = new Plot;
        tableView = new QTableView;

        splitter->addWidget(tableView);
        splitter->addWidget(graph);
        splitter->setStretchFactor(0, 0);
        splitter->setStretchFactor(1, 1);

        tableView->setModel(tableModel);
        graph->setModel(tableModel);

        setCentralWidget(splitter);
}

void myWindow::about()
{
    QMessageBox::about(this, tr("Linear regression"),
    tr("Linear regression is a part of machine learning\nIt's a Qt application example.\n"
    "(c) 2012 Sergey Chepurnov"));
}
void myWindow::linearR()
{
    QWidget *lr = new QWidget;
    lr->setWindowTitle("math");
    QPixmap pix;
    pix.load(":/images/algorithm.png");
    QLabel *label = new QLabel;
    label->setPixmap(pix);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    lr->setLayout(layout);
    //lr->setGeometry(50,100,100,400);
    lr->show();
}
void myWindow::setupActions()
{
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(actionLinear_regression, SIGNAL(triggered()), this, SLOT(linearR()));
    connect(action_Exit, SIGNAL(triggered(bool)),qApp, SLOT(quit()));
}
