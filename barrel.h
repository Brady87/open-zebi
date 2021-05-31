#ifndef BARREL_H
#define BARREL_H

#include <GL/glu.h>
#include <qopengl.h>
#include <QImage>
#include <QGLWidget>


class Barrel {
private:
    // A été cliqué
    bool prevClicked = false;

    // Coordonnées du baril
    float *coord = new float(3);

    // Texture
    GLuint *textureID_ = new GLuint[1];

public:
    Barrel();

    ~Barrel();

    void display(float offsetZ, bool barrelPressed);

    void draw(float offsetZ, GLUquadric *quadrique);
};

#endif // BARREL_H
