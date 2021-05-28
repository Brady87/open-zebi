#ifndef CAR_H
#define CAR_H
#include <GL/glu.h>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QObject>
#include <cmath>

// Classe dediee pour la gestion de la voiture
class Car
{

private:
    //Propriétés extrinsèques de la voiture
    float coord[3];

    //Propriétés intrinsèques de la voiture
    const float SPEED_CAR=1.5;
    const float HEIGHT=0.8;
    const float WIDTH=1.0;
    const float LENGTH=2.0;
    const float SIZE_WHEEL=0.5;
    float timeElapsed;
    bool isOpponent;
    int parkingUsed=0;
    float zShift=0.0;

    GLUquadric* wheelQuadric_ = nullptr;



protected :
    void drawCar() ;
    void drawWheel() ;
    void drawFlashingLights(float timeElapsed) ;



private slots:
    void changeColorFlashingLights();

public:

    // Constructeur avec parametres
    Car(bool opponent,float xShift, float zShift);

    // Destructeur
    ~Car();

    // Methode d'affichage
    void display(float timeElapsed);

    //Tourner à droite et à gauche
    void turn(float angle);
    float getLength(){return LENGTH;}
    float* getCoord(){return coord;}
    int getParkingUsed(){return parkingUsed;}

    //Se garer
    void parked(){parkingUsed++;}

};

#endif // CAR_H

