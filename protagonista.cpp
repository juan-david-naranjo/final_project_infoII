#include "protagonista.h"
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QDebug>

Protagonista::Protagonista(int startX, int startY, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent), x(startX), y(startY), speed_x(0), speed_y(0),
    health(100), lives(3), isDead(false), currentFrame(0),
    timerAnimacion(nullptr), timerGesto(nullptr), healthBar(nullptr)
{
    setPos(x, y); // Establece la posición inicial
    setFlag(QGraphicsItem::ItemIsFocusable); // Hacer que el objeto sea "focusable"
    setFocus(); // Otorgar el foco al protagonista para recibir eventos de teclado

    // Cargar la imagen predeterminada del protagonista desde la hoja de sprites
    spriteSheet = QPixmap("C:\\Users\\Lenovo\\Pictures\\GRADO ALEJO 11A\\bart simpson animation 2.jpg");

    // La imagen de Bart está en la fila 1, columna 1 de la hoja de sprites
    normalImage = spriteSheet.copy(0, 0, 39, 87);  // Ajusta el tamaño si es necesario
    setPixmap(normalImage); // Establece la imagen predeterminada de Bart

    // Intentar cargar la imagen para los gestos
    QPixmap gestureSheet("C:\\Users\\Lenovo\\Pictures\\bart baile 2.png");

    // Verificar si la imagen se carga correctamente
    if (gestureSheet.isNull()) {
        qDebug() << "Error al cargar la imagen de gesto.";
        return;
    }

    // Inicializar las imágenes para el gesto
    for (int i = 0; i < 7; ++i) {
        // Asegúrate de que los cuadros estén bien alineados en la imagen
        gestureFrames.append(gestureSheet.copy(i * 39, 0, 39, 87)); // Suponiendo que cada cuadro es de 39x87
    }

    // Crear la barra de salud
    healthBar = new QGraphicsRectItem(this);
    healthBar->setRect(0, -10, health, 5);
    healthBar->setBrush(Qt::green);

    // Inicializar las animaciones
    iniciarAnimaciones(false);
}

Protagonista::~Protagonista() {
    // Liberar recursos de los punteros
    delete timerAnimacion;
    delete timerGesto;
    delete healthBar;
}

int Protagonista::getX() const {
    return x;
}

int Protagonista::getY() const {
    return y;
}

void Protagonista::keyPressEvent(QKeyEvent* event) {
    if (isDead) return;

    switch (event->key()) {
    case Qt::Key_W:
        speed_y = -5;
        break;
    case Qt::Key_A:
        speed_x = -5;
        iniciarAnimaciones(true); // Iniciar animación de caminar a la izquierda
        break;
    case Qt::Key_S:
        speed_y = 5;
        break;
    case Qt::Key_D:
        speed_x = 5;
        iniciarAnimaciones(true); // Iniciar animación de caminar a la derecha
        break;
    case Qt::Key_Space:
        hacerGesto(5000); // Llamar con una duración específica de 2000 ms (2 segundos)
        break;
    default:
        break;
    }
}


void Protagonista::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
        speed_y = 0;
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        speed_x = 0;
        if (timerAnimacion && timerAnimacion->isActive()) {
            timerAnimacion->stop(); // Detener la animación de caminar
        }
        setPixmap(normalImage); // Restaurar la imagen normal
        break;
    default:
        break;
    }
}

void Protagonista::iniciarAnimaciones(bool haciaDerecha) {
    // Cargar los cuadros para caminar hacia la derecha solo una vez al inicio
    if (framesCaminarDerecha.isEmpty()) {
        for (int i = 0; i < 13; ++i) {
            framesCaminarDerecha.append(spriteSheet.copy(i * 39, 1 * 87, 39, 87)); // Los cuadros de caminar son 39x87
        }
    }

    // Voltear los cuadros si se camina a la izquierda
    if (!haciaDerecha) {
        for (int i = 0; i < framesCaminarDerecha.size(); ++i) {
            framesCaminarIzquierda.append(framesCaminarDerecha[i].transformed(QTransform().scale(-1, 1)));
        }
    }

    // Inicializar el temporizador de la animación si no está ya creado
    if (!timerAnimacion) {
        timerAnimacion = new QTimer(this);
        connect(timerAnimacion, &QTimer::timeout, this, &Protagonista::actualizarCaminar);
    }

    // Reiniciar la animación al cambiar de dirección
    timerAnimacion->start(100);
}
void Protagonista::update() {
    if (!isDead) {
        mover(speed_x, speed_y);
    }
}

void Protagonista::mover(int dx, int dy) {
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    this->setPos(nuevaPos);

    x += dx;
    y += dy;

}

void Protagonista::actualizarCaminar() {
    currentFrame = (currentFrame + 1) % framesCaminarDerecha.size();
    setPixmap((speed_x >= 0) ? framesCaminarDerecha[currentFrame] : framesCaminarIzquierda[currentFrame]);
}

void Protagonista::setCaminarDerecha() {
    setPixmap(framesCaminarDerecha[currentFrame]);
}

void Protagonista::hacerGesto(int duration) {
    currentGestoFrame = 0;
    if (!timerGesto) {  // Asegurarse de que no haya una instancia previa de timerGesto
        timerGesto = new QTimer(this);
        connect(timerGesto, &QTimer::timeout, this, &Protagonista::actualizarGesto);
    }
    timerGesto->start(100); // Cambiar la imagen cada 100 ms

    // Establecer un temporizador para detener el gesto después de la duración especificada
    QTimer::singleShot(duration, [this]() {
        timerGesto->stop();
        setPixmap(normalImage); // Volver a la imagen normal
    });
}


void Protagonista::actualizarGesto() {
    setPixmap(gestureFrames[currentGestoFrame]);
    currentGestoFrame = (currentGestoFrame + 1) % gestureFrames.size();

    // Hacer que el gesto dure más tiempo (por ejemplo, 3 ciclos completos)
    static int ciclosCompletados = 0;
    if (currentGestoFrame == 0) {
        ciclosCompletados++;
        if (ciclosCompletados >= 3) { // Después de 3 ciclos completos
            timerGesto->stop();
            setPixmap(normalImage); // Regresar a la imagen normal
            ciclosCompletados = 0; // Reiniciar el contador
        }
    }
}

void Protagonista::recibirDano(int dano) {
    health -= dano;
    if (health <= 0) {
        health = 0;
        morir();
    }
    healthBar->setRect(0, -10, health, 5); // Actualiza el tamaño de la barra de salud
}

void Protagonista::morir() {
    isDead = true;
    setPixmap(QPixmap("C:\\ruta\\imagen_de_muerte.png")); // Imagen de muerte
    // Aquí puedes agregar cualquier otro código necesario cuando el protagonista muere
}
