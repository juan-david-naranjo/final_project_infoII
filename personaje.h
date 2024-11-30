#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QString>

class Personaje : public QObject
{
    Q_OBJECT
public:
    explicit Personaje(QObject *parent = nullptr);

    virtual ~Personaje() = default;

    // Métodos getter
    double getPosX() const;
    double getPosY() const;
    QString getNombre() const;
    double getVelocidad() const;
    int getVida() const;

    // Métodos setter
    void setPosX(double x);
    void setPosY(double y);
    void setNombre(const QString &n);
    void setVelocidad(double v);
    void setVida(int v);

    // Método puro (abstracto)
    virtual void IniciarAnimacion(bool caminar) = 0;
    void habilitarArma();

protected:
    double posX;       // Posición en X
    double posY;       // Posición en Y
    QString nombre;    // Nombre del personaje
    double velocidad;  // Velocidad del personaje
    unsigned short int vidas;  // Vida del personaje

signals:
};

#endif // PERSONAJE_H
