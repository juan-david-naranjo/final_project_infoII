#include "suelo.h"
#include <QBrush>

Suelo::Suelo(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent)
    : QObject(), QGraphicsRectItem(parent)
{
    // Establece la geometría del rectángulo
    setRect(x, y, width, height);

    // Opcional: Establecer un color o patrón para el suelo
    setBrush(QBrush(Qt::green)); // Ejemplo: Suelo verde
}
