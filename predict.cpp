#include "predict.h"
#include <QtGui>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <QPointF>
#include <QVector>
Predict::Predict(const QVector<QPointF>&dataset, const float &al, const int &num,QObject *parent)
    : QObject(parent), data(dataset), alpha(al), num_iters(num)
{
    th<<0<<0;
    m = data.size();
    J=0;
    dJ<<0<<0;
    S1=0;
    S2=0;
}
float Predict::Costfunction(){

    float S=0;
    float sum;
    float degree = 2.0;
    for (int i=0; i<data.size(); ++i){
        sum=(th.at(0)+th.at(1)*data[i].x()) - data[i].y();
        S=S+powf(sum,degree);
    }
    J=(1/(2*m))*S;
    return J;
}

QList<float> Predict::GradDesc(){

    float si1=0,si2=0;
    for(int it=0; it<num_iters;++it){
        S1=0;
        S2=0;
       for (int i=0; i<data.size(); ++i){
         si1=th[0]+th[1]*data[i].x() - data[i].y();
         S1=S1+si1;
         si2=th[0]+th[1]*data[i].x() - data[i].y();
         S2=S2+(si2*data[i].x());
       }
       dJ[0]= S1;
       dJ[1]= S2;
       th[0]=th[0]-alpha/m*dJ[0];
       th[1]=th[1]-alpha/m*dJ[1];
    }
    return th;
}
QVector<QPointF> Predict::Hypothesis(){
    QVector<QPointF> hx;
    QPointF fp;
    for (int r=0; r< data.size();++r){
        fp.setX(th.at(0)+th.at(1)*data[r].x());
        fp.setY(data[r].x());
        hx.append(fp);
    }
    return hx;
}
