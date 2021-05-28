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
    GLfloat colorDiffuse_car[] = {0.7f, 0.7f, 0.7f};
    GLfloat colorSpeculaire_car[] = {0.774597f, 0.774597f, 0.774597f };
    GLfloat colorShininess_car[] = {76.8};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbient_car);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, colorShininess_car);

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    // Back face
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);

    // Top face
    glNormal3f(0.f,1.0f,0.f);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);


    // Bottom face
    glNormal3f(0.f,-1.0f,0.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);

    // Right face (Left with my POV)
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    // Left face (Right with my POV)
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    glVertex3f(-WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,LENGTH/2);
    glVertex3f(-WIDTH/2,HEIGHT+SIZE_WHEEL/2,-LENGTH/2);

    glEnd();


    // Wheels

    //Front right wheel
    glPushMatrix();
    glTranslatef(WIDTH/2,SIZE_WHEEL/2,-LENGTH/2);
    drawWheel();
    glPopMatrix();

    //Back right wheel
    glPushMatrix();
    glTranslatef(WIDTH/2,SIZE_WHEEL/2,LENGTH/2);
    drawWheel();
    glPopMatrix();

    //Front left wheel
    glPushMatrix();
    glTranslatef(-WIDTH/2-SIZE_WHEEL/2,SIZE_WHEEL/2,-LENGTH/2);
    drawWheel();
    glPopMatrix();

    //Back left wheel
    glPushMatrix();
    glTranslatef(-WIDTH/2-SIZE_WHEEL/2,SIZE_WHEEL/2,LENGTH/2);
    drawWheel();
    glPopMatrix();

    //Flashing Lights
    drawFlashingLights(timeElapsed);
    glPopMatrix();


}

void Car::drawWheel()
{

    glPushMatrix();
    glRotatef(90,0,1,0);

    //Cylindre
   // glColor3f(.5f,.5f,.5f);
    gluCylinder(wheelQuadric_,SIZE_WHEEL/2,SIZE_WHEEL/2,SIZE_WHEEL/2,12,1);


    //Premier disque
   // glColor3f(.25f,.25f,.25f);
    gluDisk(wheelQuadric_,0.,SIZE_WHEEL/2,12,1);

    //Deuxième disque
  //  glColor3f(.5f,.5f,.5f);
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
    GLfloat light1_diffuse[]={1.0f,0.0f,0.0f};
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
