#include "obstaculo.h"
#include <QBrush>

Obstaculo::Obstaculo(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QObject(parent), QGraphicsRectItem()
{
    // Establece la geometría del obstáculo
    setRect(x, y, width, height);

    // Estilo visual (opcional)
    setBrush(QBrush(Qt::gray)); // Obstáculo gris
    setPen(QPen(Qt::NoPen));          // Sin borde
}

// Crear una pared horizontal
Obstaculo* Obstaculo::crearParedHorizontal(qreal x, qreal y, qreal width, QObject *parent)
{
    return new Obstaculo(x, y, width, 10, parent); // Altura fija de 10 píxeles
}

// Crear una pared vertical
Obstaculo* Obstaculo::crearParedVertical(qreal x, qreal y, qreal height, QObject *parent)
{
    return new Obstaculo(x, y, 10, height, parent); // Ancho fijo de 10 píxeles
}

// Crear un cuadrado
Obstaculo* Obstaculo::crearCuadrado(qreal x, qreal y, qreal size, QObject *parent)
{
    return new Obstaculo(x, y, size, size, parent); // Ancho y alto iguales
}
