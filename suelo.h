#ifndef SUELO_H
#define SUELO_H

#include <QGraphicsRectItem>
#include <QObject>

class Suelo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // Constructor que permite definir el tamaño y posición del suelo
    Suelo(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);
};

#endif // SUELO_H
