#include "obstaculo.h"
#include <QBrush>

Obstaculo::Obstaculo(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QObject(parent), QGraphicsRectItem()
{
    // Establece la geometría del obstáculo
    setRect(x, y, width, height);

    // Estilo visual (opcional)
    setBrush(QBrush(Qt::gray)); // Obstáculo gris
    setPen(QPen(Qt::NoPen));    // Sin borde
}
