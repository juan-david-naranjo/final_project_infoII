#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPen>

class Obstaculo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Obstaculo(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
};

#endif // OBSTACULO_H
