#include "stopzone.h"

StopZone::StopZone(Car *voiture) {
    parkingUsed = voiture->getParkingUsed();
    coord[0] = 4.0;
    coord[1] = 0.001;
    coord[2] = 20.0;
    length = voiture->getLength();
    barrel = Barrel();
}


void StopZone::display(bool barrelClicked, float timeElapsed) {

    int tz = 100;
    coord[2] = tz - fmod(timeElapsed + parkingUsed * 25, tz + 10);
    glBegin(GL_QUADS);

    //Couleur

    GLfloat colorAmbient_stopZone[] = {0.0f, 0.1f, 0.9f};
    GLfloat colorDiffuse_stopZone[] = {0.4f, 0.4f, 0.4f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse_stopZone);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbient_stopZone);


    // Affichage de la zone d'arrêt
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(coord[0] + 1.0, coord[1], coord[2] - length - 0.5);
    glVertex3f(coord[0] + 1.0, coord[1], length + coord[2]);
    glVertex3f(coord[0] - 1.0, coord[1], length + coord[2]);
    glVertex3f(coord[0] - 1.0, coord[1], coord[2] - length - 0.5);
    glEnd();


    barrel.display(coord[2] + 2.0, barrelClicked);
}
