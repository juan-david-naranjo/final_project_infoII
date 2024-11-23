#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QList>
#include "personaje.h"  // Incluir la clase Personaje

class Protagonista : public Personaje, public QGraphicsPixmapItem {  // Hereda de Personaje
    Q_OBJECT

public:
    // Constructor que también inicializa la clase base Personaje
    Protagonista(int startX, int startY, QGraphicsPixmapItem* parent = nullptr);
    ~Protagonista();

    // Métodos getter para obtener las posiciones
    int getX() const;
    int getY() const;

    // Sobrescribir eventos de teclado
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void update();
    void recibirDano(int dano);

    // Implementar el método abstracto de Personaje
    void IniciarAnimacion(bool caminar) override;

private:
    // Métodos internos para mover, animar y gestionar gestos
    void mover(int dx, int dy);
    void iniciarAnimaciones(bool caminar);
    void setCaminarDerecha();
    void setCaminarIzquierda();  // Nueva función para caminar a la izquierda
    void hacerGesto(int duration); // Agrega un parámetro opcional para duración del gesto
    void morir();

    int speed_x, speed_y;
    int vidas;
    bool isDead;
    int currentFrame;
    int currentGestoFrame;

    QPixmap spriteSheet;
    QPixmap normalImage;
    QList<QPixmap> framesCaminarDerecha;
    QList<QPixmap> framesCaminarIzquierda; // Nueva lista para cuadros de caminar a la izquierda
    QList<QPixmap> gestureFrames;

    QTimer* timerAnimacion;
    QTimer* timerGesto;

public slots:
    void actualizarCaminar();
    void actualizarGesto();
};

#endif // PROTAGONISTA_H
