#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protagonista.h"

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

    // Crear una vista para la escena
    view = new QGraphicsView(scene, this); // Crear la vista
    setCentralWidget(view); // Establecer la vista como el widget central de la ventana

    // Hacer al protagonista enfocable
    protagonista->setFlag(QGraphicsItem::ItemIsFocusable);
    protagonista->setFocus(); // Establecer el foco al protagonista para recibir eventos del teclado

    // Establecer el tamaño fijo de la ventana
    setFixedSize(sceneWidth, sceneHeight); // Establecer el tamaño de la ventana
}

MainWindow::~MainWindow()
{
    delete ui;
    delete protagonista; // Eliminar el protagonista cuando la ventana se cierre
}
