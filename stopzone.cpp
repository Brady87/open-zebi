#include "stopzone.h"

StopZone::StopZone(Car *voiture,float timeElapsed)
{
    int parkingUsed=voiture->getParkingUsed();
    int tz=100;
    coord[0]=4.0;
    coord[1]=0.001;
    coord[2]=tz-fmod(timeElapsed+parkingUsed*25,tz+10);
    length=voiture->getLength();
    baril1=new Barrel();
}


void StopZone::display(bool barrelPressed1){


    glBegin(GL_QUADS);

    //Couleur

    GLfloat colorAmbient_stopZone[] = {0.0f, 0.1f, 0.9f };
    GLfloat colorDiffuse_stopZone[] = {0.4f, 0.4f, 0.4f };
    //GLfloat colorSpeculaire_car[] = {0.774597f, 0.774597f, 0.774597f };
    //GLfloat colorShininess_car[] = {76.8};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse_stopZone);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbient_stopZone);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, colorShininess_car);


    // Affichage de la zone d'arrêt
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(coord[0]+1.0,coord[1],coord[2]-length-0.5);
    glVertex3f(coord[0]+1.0,coord[1],length+coord[2]);
    glVertex3f(coord[0]-1.0,coord[1],length+coord[2]);
    glVertex3f(coord[0]-1.0,coord[1],coord[2]-length-0.5);
    glEnd();

    baril1->display(coord[2]+2.0,true,barrelPressed1);
}
