#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QGraphicsScene>
#include <enemigo.h>

class proyectil : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit proyectil(QGraphicsScene* scene, int startX, int startY, int velocidadX, int velocidadY, QObject *parent = nullptr);

    void actualizarPosicion(); // Actualizar la posición del proyectil
    void iniciarMovimiento(); // Iniciar el movimiento
    int getposX();
    int getposY();

private:
    int x, y;               // Posición inicial
    int speedX, speedY;      // Velocidad en los ejes X y Y
    int angulo;
    const int gravedad = 1;  // Gravedad que afecta el movimiento
    QTimer* timerMovimiento; // Timer para actualizar la posición

signals:
    void destruido(); // Señal cuando el proyectil ha dejado de moverse (fuera de la escena, por ejemplo)
};

#endif // PROYECTIL_H
