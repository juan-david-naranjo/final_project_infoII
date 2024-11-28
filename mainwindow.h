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

    // Miembros para los elementos de la escena
    QGraphicsPixmapItem *bart; // El item que representa a Bart en la escena
    Protagonista *protagonista;  // El protagonista del juego
    enemigo *enemigo1;           // Puntero para el enemigo 1
    enemigo *enemigo2;           // Puntero para el enemigo 2
    enemigo *enemigo3;           // Puntero para el enemigo 3
    QTimer *timer;               // Temporizador para las actualizaciones

    // Dimensiones de la escena
    int sceneWidth = 800;      // Ancho de la escena
    int sceneHeight = 600;     // Alto de la escena
    int tileSize = 50;         // Tamaño de los tiles, si es necesario para el jugador

    // Método para actualizar enemigos
    void actualizarEnemigos();
};

#endif // MAINWINDOW_H
