#ifndef STOPZONE_H
#define STOPZONE_H

#include <qopengl.h>
#include <QImage>
#include <GL/glu.h>
#include <QGLWidget>
#include "car.h"
#include "barrel.h"

class StopZone {

private:
    //longueur de la voiture
    float length;

    float *coord = new float[3];
    Barrel barrel;


    // Nombre de parking effectué par la voiture principale
    int parkingUsed;

public:
    StopZone(Car *voiture);

    //fonction d'affichage
    void display(bool barrelPressed1, float timeElapsed);

    //renvoie les coordonnées
    float *getCoord() { return coord; }

    //rPermet d'acceder au barril
    Barrel getBarrel() { return barrel; }

};

#endif // STOPZONE_H
