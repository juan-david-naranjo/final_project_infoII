#include "personaje.h"

Personaje::Personaje(QObject *parent)
    : QObject{parent},
    posX(0), posY(0), velocidad(0), vidas(0) {} // Inicialización de atributos

// Métodos getter
double Personaje::getPosX() const {
    return posX;
}

double Personaje::getPosY() const {
    return posY;
}

QString Personaje::getNombre() const {
    return nombre;
}

double Personaje::getVelocidad() const {
    return velocidad;
}

int Personaje::getVida() const {
    return vidas;
}

// Métodos setter
void Personaje::setPosX(double x) {
    posX = x;
}

void Personaje::setPosY(double y) {
    posY = y;
}

void Personaje::setNombre(const QString &n) {
    nombre = n;
}

void Personaje::setVelocidad(double v) {
    velocidad = v;
}

void Personaje::setVida(int v) {
    vidas = v;
}
