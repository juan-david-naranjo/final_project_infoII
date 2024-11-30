#include "arma.h"
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

void arma::disparar() {
    if (recogida) {
        qDebug() << "¡Disparando proyectil!";
        // Aquí implementarás la lógica de disparo, como crear un nuevo objeto de proyectil y agregarlo a la escena.
    } else {
        qDebug() << "¡El arma no ha sido recogida aún!";
    }
}
