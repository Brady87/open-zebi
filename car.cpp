#include "car.h"
#include<iostream>
Car::Car(bool _isOpponent,float _xShift, float _zShift)
{
    wheelQuadric_=gluNewQuadric();
    gluQuadricDrawStyle(wheelQuadric_, GLU_FILL);
    coord[0]=_xShift;
    coord[1]=0.0;
    coord[2]=10.0;
    isOpponent=_isOpponent;
    zShift=_zShift;

}

Car::~Car()
{
}

void Car::display(float timeElapsed)
{
    //Si Voiture opposante, elle se déplace selon z décroissant
    if (isOpponent){
        coord[2]=100.0-float(SPEED_CAR*fmod(timeElapsed+zShift,120));
    }

    glPushMatrix();

    glTranslated(-coord[0] ,0., coord[2]);

    // Couleur chrome
    GLfloat colorAmbient_car[] = {0.25f, 0.25f, 0.25f };
    GLfloat colorDiffuse_car[] = {0.7f, 0.7f, 0.2f};
    GLfloat colorSpecular_car[] = {0.774597f, 0.774597f, 0.774597f };
    GLfloat colorShininess_car[] = {76.8};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpecular_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbient_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, colorShininess_car);

    glBegin(GL_QUADS);

    // Face avant
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    // Face arrière
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);

    // Face haut
    glNormal3f(0.f,1.0f,0.f);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);


    // Face bas
    glNormal3f(0.f,-1.0f,0.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);

    // Face gauche
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    // Face droite
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    glEnd();


    // Roues

    // Roue avant droite
    glPushMatrix();
    glTranslatef(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    drawWheel();
    glPopMatrix();

    // Roue arrière droite
    glPushMatrix();
    glTranslatef(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    drawWheel();
    glPopMatrix();

    //Roue avant droite
    glPushMatrix();
    glTranslatef(-WIDTH/2-SIZE_WHEEL/2,SIZE_WHEEL/2,-LENGTH/2);
    drawWheel();
    glPopMatrix();

    // Roue arrière gauche
    glPushMatrix();
    glTranslatef(-WIDTH/2-SIZE_WHEEL/2,SIZE_WHEEL/2,LENGTH/2);
    drawWheel();
    glPopMatrix();

    // Gyrophare
    drawFlashingLights(timeElapsed);
    glPopMatrix();


}

void Car::drawWheel()
{
    // Construction des roues

    glPushMatrix();
    glRotatef(90,0,1,0);

    //Cylindre
    gluCylinder(wheelQuadric_,SIZE_WHEEL/2,SIZE_WHEEL/2,SIZE_WHEEL/2,12,1);


    //Premier disque
    gluDisk(wheelQuadric_,0.,SIZE_WHEEL/2,12,1);

    //Deuxième disque
    glTranslatef(0.f,0.f,SIZE_WHEEL/2);
    gluDisk(wheelQuadric_,0.,SIZE_WHEEL/2,12,1);
    glPopMatrix();
}


void Car::drawFlashingLights(float timeElapsed)
{
    // Gyrophare
    glPushMatrix();

    // Matériau gyrophare
    GLfloat colorDiffuse_gyro_red []={0.75,0.0,0.0};
    GLfloat colorDiffuse_gyro_blue []={0.0,0.0,0.75};

    // Couleur des lampes du gyrophare
    GLfloat light1_red[]={1.0,0.0,0.0};
    GLfloat light1_blue[]={0.0,0.0,1.0};


    //Position et couleur de la lampe1
    GLfloat light1_pos[]={0.f,1.5f,0.0f,1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    if (fmod(timeElapsed,20)<10)
    {
         glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_red);
         glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuse_gyro_red);

    }
    else{

        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_blue);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,colorDiffuse_gyro_blue);
    }



    glTranslatef(0.f,1.0f,0.0f);
    // Sphère du gyrophare
    gluSphere(wheelQuadric_,0.25,24,24);

    glPopMatrix();

    GLfloat colorAmbiante_[]={0.9f,0.9f,0.9f,1.f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorAmbiante_);

}

void Car::turn(float angle){
    coord[0]+=angle;
    if (coord[0]<=-4){
        coord[0]=-4;
    }
    else if (coord[0]>=4){
        coord[0]=4;
    }
}
