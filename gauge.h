#ifndef GAUGE_H
#define GAUGE_H

#include <qopengl.h>
#include <QImage>
#include <GL/glu.h>
#include <QGLWidget>
#include <QMessageBox>
#include <QTimer>

// Classe dediée à l'affichage de la jauge
class Gauge {
private:
    // Taux remplissage , 1: plein / 0: vide
    float rate = 1;
public:
    Gauge();

    void display();

    void addFuel();

    void decrease();

    float getRate() { return rate; }
};

#endif // GAUGE_H
