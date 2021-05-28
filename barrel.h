#ifndef BARREL_H
#define BARREL_H

#include <GL/glu.h>
#include <qopengl.h>
#include <QImage>
#include <QGLWidget>


class Barrel
{
private:
    bool prevClicked=false;
    float *coord = new float(3);

public:
    Barrel();
    ~Barrel();
    void display(float offsetZ, bool leftRight,bool barrelPressed);
    void drawBarrel(bool leftRight,uint64_t offsetZ,GLUquadric * quadrique);
private:
    GLuint* textureID_=new GLuint[1];
};

#endif // BARREL_H