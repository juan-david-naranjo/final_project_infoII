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

    // Métodos para configurar obstáculos específicos
    static Obstaculo* crearParedHorizontal(qreal x, qreal y, qreal width, QObject *parent = nullptr);
    static Obstaculo* crearParedVertical(qreal x, qreal y, qreal height, QObject *parent = nullptr);
    static Obstaculo* crearCuadrado(qreal x, qreal y, qreal size, QObject *parent = nullptr);
};

#endif // OBSTACULO_H
