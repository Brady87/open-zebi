#ifndef CAR_H
#define CAR_H

#include <GL/glu.h>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QObject>
#include <cmath>

// Classe dediee pour la gestion de la voiture
class Car {

private:
    //Propriétés extrinsèques de la voiture
    // Coordonnées
    float coord[3];

    //Propriétés intrinsèques de la voiture
    const float SPEED_CAR = 1.5;
    const float HEIGHT = 0.8;
    const float WIDTH = 1.0;
    const float LENGTH = 2.0;
    const float SIZE_WHEEL = 0.5;

    // Temps écoulée
    float timeElapsed;

    // Voiture opposante ?
    bool isOpponent;

    // Nombre de parking antérieur
    int parkingUsed = 0;

    // Décalage sur la profondeur
    float zShift = 0.0;

    // Quadrique
    GLUquadric *wheelQuadric_ = nullptr;


public:

    // Constructeur avec parametres
    Car(bool opponent, float xShift, float zShift);

    // Destructeur
    ~Car();

    // Methode d'affichage
    void display(float timeElapsed);

    void drawCar();

    void drawWheel();

    void drawFlashingLights(float timeElapsed);


    //Tourner à droite et à gauche
    void turn(float angle);

    // Getters et Setters
    float getLength() { return LENGTH; }

    float *getCoord() { return coord; }

    int getParkingUsed() { return parkingUsed; }

    //Se garer
    void park() { parkingUsed++; }


};

#endif // CAR_H

