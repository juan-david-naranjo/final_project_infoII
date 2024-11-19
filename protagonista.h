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

class Protagonista : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Protagonista(int startX, int startY, QGraphicsPixmapItem* parent = nullptr);
    ~Protagonista();

    int getX() const;
    int getY() const;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void update();
    void recibirDano(int dano);

private:
    void mover(int dx, int dy);
    void iniciarAnimaciones(bool caminar);
    void setCaminarDerecha();
    void setCaminarIzquierda();  // Nueva función para caminar a la izquierda
    void hacerGesto(int duration); // Agrega un parámetro opcional para duración del gesto
    void morir();

    int x;
    int y;
    int speed_x, speed_y;
    int health;
    int lives;
    bool isDead;
    int currentFrame;
    int currentGestoFrame;

    QPixmap spriteSheet;
    QPixmap normalImage;
    QList<QPixmap> framesCaminarDerecha;
    QList<QPixmap> framesCaminarIzquierda; // Nueva lista para cuadros de caminar a la izquierda
    QList<QPixmap> gestureFrames;

    QGraphicsRectItem* healthBar;

    QTimer* timerAnimacion;
    QTimer* timerGesto;

public slots:
    void actualizarCaminar();
    void actualizarGesto();
};

#endif // PROTAGONISTA_H
