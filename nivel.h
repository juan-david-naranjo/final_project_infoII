#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include "protagonista.h"
#include "obstaculo.h"
#include "enemigo.h"  // Si tienes clase enemigo

class Nivel {
public:
    Nivel(QGraphicsScene* scene);
    void crearNivel();

private:
    QGraphicsScene* scene;
    Protagonista* protagonista;
};

#endif // NIVEL_H
