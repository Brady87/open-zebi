#include "barrel.h"

Barrel::Barrel() {
    //Image texture
    QImage fuelImage = QGLWidget::convertToGLFormat(
            QImage("C:/Users/thoma/Documents/Cours/FISE2/Semestre 8/Info/Bibliotheque de developpement multimedia/ProjetBDM/res/fuel.jpg"));
    glGenTextures(1, textureID_);

    glBindTexture(GL_TEXTURE_2D, textureID_[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, fuelImage.width(), fuelImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 fuelImage.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    GLUquadric *barrelQuadric_ = gluNewQuadric();
    gluQuadricDrawStyle(barrelQuadric_, GLU_FILL);

}


Barrel::~Barrel() {
}

void Barrel::display(float offsetZ, bool barrelPressed) {

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // Quadrique
    GLUquadric *barrelQuadric_ = gluNewQuadric();
    gluQuadricDrawStyle(barrelQuadric_, GLU_FILL);

    // bind texture
    glBindTexture(GL_TEXTURE_2D, textureID_[0]);

    /* Change barrels color upon click */
    if (barrelPressed || prevClicked) {
        glColor3f(100.f, 0.f, 0.f);
        prevClicked = true;
    } else {
        glColor3f(100.f, 100.f, 100.f);
    }

    draw(offsetZ, barrelQuadric_);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);


}

void Barrel::draw(float offsetZ, GLUquadric *quadrique) {

    glPushMatrix();
    glTranslated(-5.0, 0.0, offsetZ);


    glRotated(-90, 1, 0, 0);

    gluQuadricTexture(quadrique, GL_TRUE);
    gluCylinder(quadrique, 0.6, 0.6, 1.5, 40, 40);
//    glTranslated(2.0,0.2,0.0);
//    gluDisk(quadrique,0.6,0.6,12,1);
    gluQuadricTexture(quadrique, GL_FALSE);

    glPopMatrix();

}
