#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "personaje.h"

class enemigo : public Personaje, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum class Tipo { Enemigo1, Enemigo2, Enemigo3 };

    explicit enemigo(int startX, int startY, Tipo tipo, QObject *parent = nullptr);

    void mover();
    void update();
    void recibirDano(int dano);
    void morir();
    void IniciarAnimacion(bool caminar) override;

private:
    int x, y;
    int speed_x, speed_y;
    Tipo tipoEnemigo;
    unsigned short int vidas;

    QTimer* timerAnimacion;
    bool animacionActiva;

    QPixmap imagen1; // Primera imagen de animación
    QPixmap imagen2; // Segunda imagen de animación
    bool alternarFrame; // Controla cuál imagen mostrar

signals:
         // Señales, si necesitas alguna
};

#endif // ENEMIGO_H
