#ifndef ARMA_H
#define ARMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "proyectil.h"


class arma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit arma(QObject *parent = nullptr);

    // Método para verificar colisión con el protagonista
    void verificarColision(QGraphicsItem* protagonista);

    // Método para disparar proyectiles, tomando como parámetros la dirección y velocidad
    void disparar(int velocidadX, int velocidadY, qreal posX, qreal posY);

    int getVelocidad();

signals:
    void armaRecogida(); // Señal emitida cuando el arma es recogida por el protagonista

private:
    bool recogida; // Indica si el arma ya fue recogida

};

#endif // ARMA_H
