#include "nivel.h"

Nivel::Nivel(QGraphicsScene* scene) : scene(scene) {
    protagonista = nullptr;
}

void Nivel::crearNivel() {
    // Crear y posicionar al protagonista
    protagonista = new Protagonista(100, 200);  // Posición inicial del protagonista
    scene->addItem(protagonista);

    // Crear y posicionar obstáculos
    Obstaculo* pared1 = new Obstaculo(50, 250, 200, 10);  // Pared horizontal
    scene->addItem(pared1);

    // Crear más obstáculos según sea necesario
    Obstaculo* pared2 = new Obstaculo(300, 300, 150, 10);
    scene->addItem(pared2);

    // Crear enemigos
    enemigo* enemigo1 = new enemigo(500, 200,enemigo::Tipo::Enemigo1);
    enemigo* enemigo2 = new enemigo(550, 200,enemigo::Tipo::Enemigo2);
    scene->addItem(enemigo1);
}
