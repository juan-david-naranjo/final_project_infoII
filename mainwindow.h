#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "protagonista.h"
#include "enemigo.h"  // Asegúrate de incluir la clase enemigo

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Miembros para la escena y la vista
    QGraphicsScene *scene;    // La escena donde se colocan los elementos
    QGraphicsView *view;      // La vista para mostrar la escena

    arma* miArma;
    proyectil* Min;
    int angulo;

    // Miembros para los elementos de la escena
    QGraphicsPixmapItem *bart; // El item que representa a Bart en la escena
    Protagonista *protagonista;  // El protagonista del juego
    enemigo *enemigo1 = nullptr;
    enemigo *enemigo2 = nullptr;
    enemigo *enemigo3 = nullptr;
    enemigo *enemigo4 = nullptr;
    enemigo *enemigo5 = nullptr;
    enemigo *enemigo6 = nullptr;
    enemigo *enemigo7 = nullptr;
    enemigo *enemigo8 = nullptr;
    enemigo *enemigo9 = nullptr;
    enemigo *enemigo10 = nullptr;
    enemigo *enemigo11 = nullptr;
    QTimer *timer;

    // Dimensiones de la escena
    int sceneWidth = 800;      // Ancho de la escena
    int sceneHeight = 600;     // Alto de la escena
    int tileSize = 50;         // Tamaño de los tiles, si es necesario para el jugador

    // Método para actualizar enemigos
    void actualizarEnemigos();

public slots:
    void dispararProyectil();
};

#endif // MAINWINDOW_H
