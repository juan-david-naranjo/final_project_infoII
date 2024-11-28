#include "protagonista.h"

Protagonista::Protagonista(int startX, int startY, QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent),
    x(startX), y(startY),
    speed_x(0), speed_y(0),
    vidas(3), isDead(false),
    direction(Direction::Right), alternarFrame(false)
{
    setPos(x, y);
    setFlag(QGraphicsItem::ItemIsFocusable);  // Permite que el protagonista reciba eventos del teclado
    setFocus();

    // Cargar imágenes separadas
    spriteReposo = QPixmap(":/scenas/sprites/sprites_bartreposo.png");
    spriteCaminar1 = QPixmap(":/scenas/sprites/sprites_bartcaminar1.png");
    spriteCaminar2 = QPixmap(":/scenas/sprites/sprites_bartcaminar2.png");
    spriteSalto = QPixmap(":/scenas/sprites/sprites_bartsalto.png");

    if (spriteReposo.isNull() || spriteCaminar1.isNull() || spriteCaminar2.isNull() || spriteSalto.isNull()) {
        qDebug() << "Error: No se pudieron cargar todas las imágenes.";
    }

    // Establecer la imagen inicial
    setPixmap(spriteReposo);

    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, &Protagonista::alternarFrameAnimacion);
    animTimer->start(100); // Cambiar cada 500 ms (medio segundo)
}

Protagonista::~Protagonista() {

    delete animTimer;
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
            speed_y = -20; // Velocidad inicial del salto
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
    // Aplicar gravedad y lógica de salto
    if (speed_y < 0) { // Si está subiendo
        if (y + speed_y <= 300 - 3 * saltoAltura) {  // Verificar si ha alcanzado la altura máxima
            y = 300 - 3 * saltoAltura;  // Limitar la altura máxima del salto
            speed_y = 0;  // Detener el ascenso
        } else {
            y += speed_y;  // Continuar subiendo
            speed_y += gravedad;  // Aumentar la velocidad negativa (gravedad) mientras sube
        }
    } else {  // Si está cayendo
        if (y + speed_y >= 300) {  // Si cae al suelo
            y = 300;  // Colocarlo en el suelo
            speed_y = 0;  // Detener el movimiento vertical
        } else {
            y += speed_y;  // Continuar cayendo
            speed_y += gravedad;  // Aumentar la velocidad de caída
        }
    }

    mover(speed_x, speed_y);  // Mover al protagonista
    actualizarAnimacion();  // Actualizar la animación
}

void Protagonista::mover(int dx, int dy) {
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    setPos(nuevaPos);

    x += dx;
    y += dy;
}

void Protagonista::actualizarAnimacion() {
    if (speed_y != 0) { // Saltando
        setPixmap(direction == Direction::Right ? spriteSalto : spriteSalto.transformed(QTransform().scale(-1, 1)));
    } else if (speed_x == 0) { // Quieto
        setPixmap(direction == Direction::Right ? spriteReposo : spriteReposo.transformed(QTransform().scale(-1, 1)));
    }
}

void Protagonista::alternarFrameAnimacion() {
    if (speed_x != 0) { // Si el personaje se está moviendo
        alternarFrame = !alternarFrame;
        QPixmap currentSprite = alternarFrame ? spriteCaminar1 : spriteCaminar2;

        if (direction == Direction::Right) {
            setPixmap(currentSprite); // Imagen normal
        } else if (direction == Direction::Left) {
            setPixmap(currentSprite.transformed(QTransform().scale(-1, 1))); // Imagen invertida
        }
    }
}


void Protagonista::IniciarAnimacion(bool caminar) {
    // Ya no es necesario este método dado el nuevo sistema de animaciones.
}

void Protagonista::morir() {
    isDead = true;
    setPixmap(QPixmap("C:\\ruta\\imagen_de_muerte.png")); // Imagen de muerte
    // Aquí puedes agregar cualquier otro código necesario cuando el protagonista muere
}
