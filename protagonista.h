#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
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
    void hacerGesto(); // Duración del gesto (por defecto 1 segundo)
    void morir();

    // Variables de movimiento y animación
    int x, y;
    int speed_x, speed_y;
    int vidas;
    bool isDead;

    Direction direction; // Dirección actual del protagonista
    bool animacionActiva; // Si la animación está activa
    int frame; // Cuadro actual de la animación

    // Recursos gráficos
    QPixmap spriteSheet;     // Sprite completo
    QPixmap framesReposo;    // Cuadro de reposo
    QPixmap framesCaminarDerecha[8]; // Cuadros para caminar a la derecha
    QPixmap framesSaltar[6]; // Cuadros para saltar
    // Timers
    QTimer* timerAnimacion;
    QTimer* timerGesto;
    QTimer* timer;

public slots:

};

#endif // PROTAGONISTA_H
