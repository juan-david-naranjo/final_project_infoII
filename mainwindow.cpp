#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), protagonista(new Protagonista(0, 0)), timer(new QTimer(this)) {

    connect(timer, &QTimer::timeout, protagonista, &Protagonista::update);
    timer->start(16);

    ui->setupUi(this);

    // Configuración de la escena
    scene = new QGraphicsScene(this); // Crear la escena
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight); // Establecer el rectángulo de la escena

    // Establecer el fondo de la escena con una imagen
    QPixmap base(":/scenas/sprites/fondo.jpg"); // Imagen para el fondo
    scene->setBackgroundBrush(base.scaled(sceneWidth, sceneHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // Crear el protagonista (Bart)
    protagonista = new Protagonista(100, 500, nullptr);
    scene->addItem(protagonista); // Agregar el protagonista a la escena

    // Crear los enemigos
    enemigo1 = new enemigo(200, 100, enemigo::Tipo::Enemigo1);
    enemigo2 = new enemigo(400, 100, enemigo::Tipo::Enemigo2);
    enemigo3 = new enemigo(600, 100, enemigo::Tipo::Enemigo3);

    // Agregar los enemigos a la escena
    scene->addItem(enemigo1);
    scene->addItem(enemigo2);
    scene->addItem(enemigo3);

    // Crear una vista para la escena
    view = new QGraphicsView(scene, this); // Crear la vista
    setCentralWidget(view); // Establecer el widget central

    // Hacer al protagonista enfocable
    protagonista->setFlag(QGraphicsItem::ItemIsFocusable);
    protagonista->setFocus(); // Establecer el foco al protagonista para recibir eventos del teclado

    // Establecer el tamaño fijo de la ventana
    setFixedSize(sceneWidth, sceneHeight); // Establecer el tamaño de la ventana

    arma* miArma = new arma();
    miArma->setPos(400, 300); // Posición inicial del arma
    scene->addItem(miArma);


    // Iniciar un temporizador para actualizar el movimiento de los enemigos
    connect(timer, &QTimer::timeout, protagonista, &Protagonista::update);
    timer->start(16);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEnemigos);
    timer->start(16);
}

void MainWindow::actualizarEnemigos() {
    // Actualizar el movimiento de cada enemigo
    enemigo1->mover();
    enemigo2->mover();
    enemigo3->mover();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete protagonista; // Eliminar el protagonista
    delete enemigo1;     // Eliminar el enemigo1
    delete enemigo2;     // Eliminar el enemigo2
    delete enemigo3;     // Eliminar el enemigo3
}
