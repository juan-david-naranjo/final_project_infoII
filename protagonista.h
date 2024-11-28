#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include "personaje.h"  // Hereda de Personaje

class Protagonista : public Personaje, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right }; // Direcciones del protagonista

    // Constructor y destructor
    Protagonista(int startX, int startY, QGraphicsPixmapItem* parent = nullptr);
    ~Protagonista();

    // Métodos getter para las posiciones
    int getX() const { return x; }
    int getY() const { return y; }

    // Sobrescribir eventos de teclado
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    // Actualización de movimiento y animación
    void update();
    void recibirDano(int dano);

    // Implementación de método abstracto de Personaje
    void IniciarAnimacion(bool caminar) override;

private:
    // Métodos internos para mover y animar
    void mover(int dx, int dy);
    void actualizarAnimacion();
    void morir();

    // Variables de movimiento y animación
    int x, y;
    int speed_x, speed_y;
    int vidas;
    bool isDead;

    Direction direction; // Dirección actual del protagonista

    // Recursos gráficos
    QPixmap spriteReposo;          // Imagen de reposo
    QPixmap spriteCaminar1;        // Imagen de caminar (cuadro 1)
    QPixmap spriteCaminar2;        // Imagen de caminar (cuadro 2)
    QPixmap spriteSalto;           // Imagen de salto

    double gravedad = 1;           // Fuerza de gravedad (ajustable)
    double saltoAltura = 100;      // Altura máxima del salto

    bool alternarFrame; // Alternar entre los cuadros de caminar
    QTimer* animTimer;

public slots:
    void alternarFrameAnimacion();
};

#endif // PROTAGONISTA_H
