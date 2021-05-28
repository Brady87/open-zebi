#ifndef STOPZONE_H
#define STOPZONE_H

#include <qopengl.h>
#include <QImage>
#include <GL/glu.h>
#include <QGLWidget>
#include "car.h"
#include "barrel.h"

class StopZone
{
public:
    StopZone(Car *voiture,float timeElapsed);
    void display(bool barrelPressed1);
    float* getCoord(){return coord;}
    Barrel *baril1;
    bool m_barrelPressed=false;
private:
    float length;
    float* coord=new float[3];

};

#endif // STOPZONE_H
