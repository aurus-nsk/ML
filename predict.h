#ifndef PREDICT_H
#define PREDICT_H

#include <QObject>
#include <QPointF>
#include <QVector>

class Predict : public QObject
{
    Q_OBJECT
public:
    Predict(const QVector<QPointF>& dataset,const float &al, const int &num, QObject *parent = 0);
    float Costfunction();
    QList<float> GradDesc();
    QVector<QPointF> Hypothesis();
private:
    QVector<QPointF> data;
    float alpha;
    int num_iters;
    QList<float> th;
    float m;
    float J;
    QList<float> dJ;
    float S1;
    float S2;
};

#endif // PREDICT_H
