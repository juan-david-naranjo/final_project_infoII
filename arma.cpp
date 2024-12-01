#include "arma.h"
#include "proyectil.h" // Incluir la clase proyectil
#include <QGraphicsScene>
#include <QDebug>

arma::arma(QObject *parent)
    : QObject{parent}, recogida(false) {
    // Configurar la imagen del arma
    setPixmap(QPixmap(":/scenas/sprites/tirachina.png")); // Ruta a la imagen del arma
    if (pixmap().isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen del arma.";
    }
}

void arma::verificarColision(QGraphicsItem* protagonista) {
    if (!recogida && this->collidesWithItem(protagonista)) {
        qDebug() << "¡El protagonista ha recogido el arma!";
        recogida = true; // Marca el arma como recogida
        emit armaRecogida(); // Emite la señal
        hide(); // Oculta el arma de la escena
    }
}

void arma::disparar(int velocidadX, int velocidadY, qreal posX, qreal posY) {
    if (recogida) {
        qDebug() << "¡Disparando proyectil!";

        // Crear un proyectil en la posición del protagonista
        proyectil* nuevoProyectil = new proyectil(scene(), posX, posY, velocidadX, velocidadY);
        nuevoProyectil->iniciarMovimiento();
    } else {
        qDebug() << "¡El arma no ha sido recogida aún!";
    }
}


