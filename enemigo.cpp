#include "enemigo.h"
#include <QDebug>
#include <QTimer>

enemigo::enemigo(int startX, int startY, Tipo tipo, QObject *parent)
    : Personaje(parent), x(startX), y(startY), speed_x(0), speed_y(0), tipoEnemigo(tipo), vidas(1), alternarFrame(false) {

    // Inicializar el temporizador de animación
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, [this]() {
        IniciarAnimacion(true);
    });

    // Cargar imágenes individuales según el tipo de enemigo
    switch (tipoEnemigo) {
    case Tipo::Enemigo1:
        imagen1 = QPixmap(":/scenas/sprites/sprites_raton1.png");
        imagen2 = QPixmap(":/scenas/sprites/sprites_raton2.png");
        break;
    case Tipo::Enemigo2:
        imagen1 = QPixmap(":/scenas/sprites/sprites_arana1.png");
        imagen2 = QPixmap(":/scenas/sprites/sprites_arana2.png");
        break;
    case Tipo::Enemigo3:
        imagen1 = QPixmap(":/scenas/sprites/sprites_aran1.png");
        imagen2 = QPixmap(":/scenas/sprites/sprites_arana2.png");
        break;
    }

    if (imagen1.isNull() || imagen2.isNull()) {
        qDebug() << "Error al cargar imágenes para el enemigo de tipo" << static_cast<int>(tipoEnemigo);
    }

    // Configurar el primer sprite y velocidad según el tipo
    setPixmap(imagen1);

    if (tipoEnemigo == Tipo::Enemigo1 || tipoEnemigo == Tipo::Enemigo2) {
        speed_x = 2; // Movimiento horizontal
        speed_y = 0;
    } else if (tipoEnemigo == Tipo::Enemigo3) {
        speed_x = 0; // Movimiento vertical
        speed_y = 2;
    }

    timerAnimacion->start(200); // Alternar cada medio segundo
}

void enemigo::mover() {
    // Movimiento según el tipo de enemigo
    if (tipoEnemigo == Tipo::Enemigo1 || tipoEnemigo == Tipo::Enemigo2) {
        x += speed_x;
        if (x >= 800 || x <= 0) { // Asumiendo un ancho de pantalla de 800
            speed_x = -speed_x; // Cambiar dirección
            setTransform(QTransform::fromScale((speed_x > 0) ? 1 : -1, 1)); // Reflejar horizontalmente
        }
    } else if (tipoEnemigo == Tipo::Enemigo3) {
        y += speed_y;
        if (y >= 600 || y <= 0) { // Borde vertical
            speed_y = -speed_y;
        }
    }

    setPos(x, y);
}

void enemigo::IniciarAnimacion(bool caminar) {
    if (caminar) {
        alternarFrame = !alternarFrame; // Alternar entre true y false
        setPixmap(alternarFrame ? imagen2 : imagen1);
    } else {
        setPixmap(imagen1); // Mostrar la imagen 1 cuando no camina
    }
}
