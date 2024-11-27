#include "protagonista.h"

#include "protagonista.h"

Protagonista::Protagonista(int startX, int startY, QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent),
    x(startX), y(startY),
    speed_x(0), speed_y(0),
    vidas(3), isDead(false),
    frame(0), direction(Direction::Right), animacionActiva(false),
    timerAnimacion(nullptr), timerGesto(nullptr)
{
    setPos(x, y);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Cargar el sprite sheet
    spriteSheet = QPixmap(":/personaje/sprites/sprites_bart.png");
    if (spriteSheet.isNull()) {
        qDebug() << "Error: No se pudo cargar el sprite sheet.";
    }

    // Tamaño de cada cuadro
    int frameWidth = 69;
    int frameHeight = 55;

    // Dividir los cuadros de animación
    framesReposo = spriteSheet.copy(0, 0, frameWidth, frameHeight); // Reposo (fila 1, columna 1)

    // Caminar a la derecha (fila 2, columnas 1 a 8)
    for (int i = 0; i < 8; ++i) {
        framesCaminarDerecha[i] = spriteSheet.copy(i * frameWidth, frameHeight, frameWidth, frameHeight);
    }

    // Saltar (fila 3, columnas 1 a 6)
    for (int i = 0; i < 6; ++i) {
        framesSaltar[i] = spriteSheet.copy(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight);
    }

    // Establecer el cuadro inicial
    setPixmap(framesReposo);
}

Protagonista::~Protagonista() {
    // Liberar recursos de los punteros
    if (timerAnimacion) {
        delete timerAnimacion;
    }
    if (timerGesto) {
        delete timerGesto;
    }
}

void Protagonista::keyPressEvent(QKeyEvent* event) {
    if (isDead) return;

    switch (event->key()) {
    case Qt::Key_A: // Mover a la izquierda
        speed_x = -5;
        direction = Direction::Left;
        break;
    case Qt::Key_D: // Mover a la derecha
        speed_x = 5;
        direction = Direction::Right;
        break;
    case Qt::Key_Space: // Saltar
        if (speed_y == 0) { // Solo saltar si no estás en el aire
            speed_y = -15; // Velocidad inicial del salto
        }
        break;
    default:
        break;
    }
}

void Protagonista::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
        speed_x = 0;
        break;
    default:
        break;
    }
}

void Protagonista::update() {
    // Aplicar gravedad
    if (y + speed_y > 300) { // Si va a caer más allá del suelo
        y = 300; // Colocarlo en el suelo
        speed_y = 0;
    } else {
        y += speed_y;
    }
    mover(speed_x, speed_y);
    actualizarAnimacion();
}

void Protagonista::mover(int dx, int dy) {
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    setPos(nuevaPos);

    x += dx;
    y += dy;
}

void Protagonista::actualizarAnimacion() {
    if (speed_x != 0 && speed_y == 0) { // Movimiento lateral
        animacionActiva = true;

        // Cambiar el cuadro de caminar
        frame = (frame + 1) % 8; // Hay 8 cuadros para caminar
        if (direction == Direction::Right) {
            setPixmap(framesCaminarDerecha[frame]);
        } else if (direction == Direction::Left) {
            setPixmap(framesCaminarDerecha[frame].transformed(QTransform().scale(-1, 1))); // Espejo
        }

    } else if (speed_y != 0) { // Saltando
        animacionActiva = true;

        // Cambiar el cuadro de saltar
        frame = (frame + 1) % 6; // Hay 6 cuadros para saltar
        setPixmap(framesSaltar[frame]);

    } else {
        animacionActiva = false;

        // Cuadro de reposo
        if (direction == Direction::Right) {
            setPixmap(framesReposo);
        } else if (direction == Direction::Left) {
            setPixmap(framesReposo.transformed(QTransform().scale(-1, 1)));
        }
    }
}


void Protagonista::IniciarAnimacion(bool caminar) {
    if (caminar) {
        // Si se activa la animación de caminar, se inicia el temporizador
        if (!timerAnimacion) {
            timerAnimacion = new QTimer(this);
            connect(timerAnimacion, &QTimer::timeout, this, &Protagonista::actualizarAnimacion);
        }
        timerAnimacion->start(100); // Cambia el cuadro cada 100 ms (puedes ajustar el tiempo)

    } else {
        // Si la animación no está activa, detenemos el temporizador
        if (timerAnimacion && timerAnimacion->isActive()) {
            timerAnimacion->stop();
            frame = 0; // Reinicia el cuadro de la animación
            setPixmap(framesReposo); // Muestra la imagen de reposo
        }
    }
}


void Protagonista::hacerGesto() {
    /*
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
*/
}

void Protagonista::morir() {
    isDead = true;
    setPixmap(QPixmap("C:\\ruta\\imagen_de_muerte.png")); // Imagen de muerte
    // Aquí puedes agregar cualquier otro código necesario cuando el protagonista muere
}
