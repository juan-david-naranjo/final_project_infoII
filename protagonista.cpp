#include "protagonista.h"

Protagonista::Protagonista(int startX, int startY, QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent),
    x(startX), y(startY),
    speed_x(0), speed_y(0),
    vidas(3), isDead(false),
    direction(Direction::Right), alternarFrame(false),
    ejecutarArma(false), alternarFrameArma(false), angulo(0), objArma(nullptr)
{
    setPos(x, y);
    setFlag(QGraphicsItem::ItemIsFocusable);  // Permite que el protagonista reciba eventos del teclado
    setFocus();

    // Cargar imágenes separadas
    spriteReposo = QPixmap(":/scenas/sprites/sprites_bartreposo.png");
    spriteCaminar1 = QPixmap(":/scenas/sprites/sprites_bartcaminar1.png");
    spriteCaminar2 = QPixmap(":/scenas/sprites/sprites_bartcaminar2.png");
    spriteSalto = QPixmap(":/scenas/sprites/sprites_bartsalto.png");

    spriteArma1 = QPixmap(":/scenas/sprites/sprites_bartArma1.png");
    spriteArma2 = QPixmap(":/scenas/sprites/sprites_bartArma2.png");

    if (spriteArma1.isNull() || spriteArma2.isNull()) {
        qDebug() << "Error: No se pudieron cargar las imágenes del arma.";
    }

    if (spriteReposo.isNull() || spriteCaminar1.isNull() || spriteCaminar2.isNull() || spriteSalto.isNull()) {
        qDebug() << "Error: No se pudieron cargar todas las imágenes.";
    }

    // Establecer la imagen inicial
    setPixmap(spriteReposo);

    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, &Protagonista::alternarFrameAnimacion);
    animTimer->start(100); // Cambiar cada 100 ms (medio segundo)

    animTimerArma = new QTimer(this);
    connect(animTimerArma, &QTimer::timeout, this, &Protagonista::alternarFrameArmaAnimacion);
    animTimerArma->start(100);

    timer.start();
}

Protagonista::~Protagonista() {

    delete animTimer;
}

void Protagonista::keyPressEvent(QKeyEvent* event) {
    if (isDead) return;

    switch (event->key()) {
    case Qt::Key_A: // Mover a la izquierda
        speed_x = -3;
        direction = Direction::Left;
        break;
    case Qt::Key_D: // Mover a la derecha
        speed_x = 3;
        direction = Direction::Right;
        break;
    case Qt::Key_Space: // Saltar
        if (speed_y == 0) {
            speed_y = -10;
        }
        break;
    case Qt::Key_S: // Usar el arma
        if (ejecutarArma) {
            // Verificar si ha pasado suficiente tiempo desde el último disparo
            if (timer.elapsed() - lastShotTime >= shotInterval) {
                qDebug() << "Alternando frame de arma al presionar S.";
                alternarFrameArmaAnimacion(); // Alternar la animación del arma
                if (!animTimerArma->isActive()) {
                    animTimerArma->start(500);
                }
                dispararConArma();
                lastShotTime = timer.elapsed();  // Actualizar el tiempo del último disparo
            }
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
    case Qt::Key_S: // Al soltar "S", mostrar la segunda animación
        usarArma(false);
        animTimerArma->stop();
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

    QList<QGraphicsItem*> itemsColisionados = collidingItems();
    for (QGraphicsItem* item : itemsColisionados) {
        arma* armaColisionada = dynamic_cast<arma*>(item); // Verifica si el objeto es un arma
        if (armaColisionada) {
            armaColisionada->verificarColision(this); // Comprueba la colisión con el arma
            setArma(armaColisionada); // Asigna la referencia del arma al protagonista
            habilitarArma(); // Activa el uso del arma
            qDebug() << "El protagonista ha recogido un arma.";
        }
    }
    for (QGraphicsItem* item : itemsColisionados) {
        enemigo* enemigoColisionado = dynamic_cast<enemigo*>(item); // Verifica si es un enemigo
        if (enemigoColisionado) {
            // El protagonista ha colisionado con un enemigo, reducir vida
            perderVida();
            break; // Salir del bucle después de la primera colisión
        }
    }
}

void Protagonista::perderVida() {
    if (vidas > 0) {
        vidas--;  // Reducir vida
        qDebug() << "Vida restante: " << vidas;
        if (vidas == 0) {
            isDead = true;
            morir();  // Si no hay vidas, el protagonista muere
        }
    }
}

void Protagonista::mover(int dx, int dy) {
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    setPos(nuevaPos);

    x += dx;
    y += dy;

    setPos(x, y);
}

void Protagonista::actualizarAnimacion() {
    if (ejecutarArma) {
        return; // No hacer nada y evitar mostrar la animación de reposo
    }
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

void Protagonista::alternarFrameArmaAnimacion() {
    if (!ejecutarArma) return; // Si no tiene el arma, no hacer nada
    alternarFrameArma = !alternarFrameArma;  // Alternar la animación
    usarArma(alternarFrameArma); // Alternar entre las animaciones de arma
}


void Protagonista::habilitarArma() {
    ejecutarArma = true; // Habilita el uso del arma
    objArma = ejecutarArma ? objArma : nullptr;  // Asegúrate de que objArma esté apuntando al arma correcta
}

void Protagonista::setArma(arma* nuevaArma) {
    objArma = nuevaArma; // Asignar el puntero del arma
    qDebug() << "El protagonista ahora tiene un arma.";
}

void Protagonista::usarArma(bool primeraAnimacion) {
    if (!ejecutarArma) return; // Si no tiene el arma, no hace nada
    QPixmap currentSprite = primeraAnimacion ? spriteArma1 : spriteArma2;

    if (direction == Direction::Right) {
        setPixmap(currentSprite); // Imagen normal
    } else if (direction == Direction::Left) {
        setPixmap(currentSprite.transformed(QTransform().scale(-1, 1))); // Imagen invertida
    }
}

// Método corregido para obtener la dirección como valor entero (en grados)
int Protagonista::obtenerDireccionDelProtagonista() {
    if (direction == Direction::Right) {
        return 0;   // Dirección de 0 grados (derecha)
    } else if (direction == Direction::Left) {
        return 180; // Dirección de 180 grados (izquierda)
    } else if (direction == Direction::Up) {
        return 90;  // Dirección de 90 grados (arriba)
    } else if (direction == Direction::Down) {
        return 270; // Dirección de 270 grados (abajo)
    }
    return 0; // Valor por defecto (derecha)
}

void Protagonista::dispararConArma() {
    if (ejecutarArma) {
        qDebug() << "Disparo de arma iniciado.";

        // Notificar a MainWindow para crear y disparar el proyectil
        emit dispararProyectil();  // Emite una señal para disparar
    }
}


void Protagonista::morir() {
    isDead = true;
    setPixmap(QPixmap("C:\\ruta\\imagen_de_muerte.png")); // Imagen de muerte
    // Aquí puedes agregar cualquier otro código necesario cuando el protagonista muere
}
