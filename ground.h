#ifndef GROUND_H
#define GROUND_H

#include <qopengl.h>
#include <QImage>
#include <GL/glu.h>
#include <QGLWidget>
#include "barrel.h"

// Classe dediée à l'affichage du sol & du ciel
class Ground {
private:
    // Images textures
    QImage qim_TextureGrass_;
    QImage qim_TextureRoad_;
    QImage qim_TextureSky_;
    GLuint *m_TextureID_ = new GLuint[3];
public:

    // Constructeur avec parametres
    Ground();

    // Destructeur
    ~Ground();

    // Methode d'affichage
    void display(float timeElapsed);
};

#endif // GROUND_H
