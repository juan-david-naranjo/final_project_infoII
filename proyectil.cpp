#include "proyectil.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

proyectil::proyectil(QGraphicsScene* scene, int startX, int startY, int velocidadX, int velocidadY, QObject* parent)
    : QObject(parent), QGraphicsEllipseItem(0, 0, 10, 10) // Círculo pequeño (10x10 px)
{
    this->x = startX;
    this->y = startY;
    this->speedX = velocidadX;
    this->speedY = velocidadY;

    // Configurar la apariencia del proyectil (círculo rojo)
    setBrush(Qt::red); // Color del proyectil

    // Agregar el proyectil a la escena
    scene->addItem(this);

    // Crear un temporizador para actualizar la posición del proyectil
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &proyectil::actualizarPosicion);
}

int proyectil::getposX(){
    return x;
}

int proyectil::getposY(){
    return y;
}

void proyectil::iniciarMovimiento() {
    timerMovimiento->start(20); // Cada 20 ms actualizamos la posición

}

void proyectil::actualizarPosicion() {
    // Actualizar las posiciones X y Y
    x += speedX;
    y += speedY;

    // Aplicar la gravedad
    speedY += gravedad;

    // Mover el proyectil
    setPos(x, y);

    // Verificar colisión con enemigos
    QList<QGraphicsItem*> itemsColisionados = collidingItems();
    for (QGraphicsItem* item : itemsColisionados) {
        enemigo* enemigoColisionado = dynamic_cast<enemigo*>(item); // Verifica si es un enemigo
        if (enemigoColisionado) {
            // El proyectil ha colisionado con un enemigo, eliminarlo
            scene()->removeItem(enemigoColisionado);  // Eliminar el enemigo de la escena
            delete enemigoColisionado;  // Eliminar el enemigo de la memoria
            emit destruido();  // El proyectil también se destruye
            delete this;  // El proyectil se elimina de la escena
            return;  // Salir después de la primera colisión
        }
    }

    // Verificar si el proyectil ha salido de la pantalla
    if (y > 500 || x < 0 || x > scene()->width()) {
        emit destruido();
        delete this;  // El proyectil se elimina cuando sale de la escena
    }
}


