#include "ground.h"

Ground::Ground()
{


    QImage qim_TextureGrass_=QGLWidget::convertToGLFormat(QImage(":/grass.jpg"));
    QImage qim_TextureRoad_=QGLWidget::convertToGLFormat(QImage(":/road.jpg"));
    QImage qim_TextureSky_=QGLWidget::convertToGLFormat(QImage(":/sky.jpg"));

    //


    glGenTextures(3,m_TextureID_);

    //Sky

    glBindTexture(GL_TEXTURE_2D,m_TextureID_[2]);
    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureSky_.width(),qim_TextureSky_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureSky_.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Grass
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[0]);

    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureGrass_.width(),qim_TextureGrass_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureGrass_.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Road

    glBindTexture(GL_TEXTURE_2D,m_TextureID_[1]);

    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureRoad_.width(),qim_TextureRoad_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureRoad_.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

}

Ground::~Ground()
{
}

void Ground::display(uint64_t timeElapsed)
{

    //Color

    float grassShift = timeElapsed / 5.0;


    // Grass
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[0]);

    glBegin(GL_QUADS);

    glNormal3f(0.f,1.f,0.f);
    glTexCoord2f(0.f,100.f+grassShift); glVertex3f(-1000.f,-0.01f,100.f);
    glTexCoord2f(0.f,.0f+grassShift); glVertex3f(-1000.f,-0.01f,-100.f);
    glTexCoord2f(200.f,0.f+grassShift); glVertex3f(1000.f,-0.01f,-100.f);
    glTexCoord2f(200.f,100.f+grassShift); glVertex3f(1000.f,-0.01f,100.f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Road

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[1]);

    glBegin(GL_QUADS);

    glNormal3f(0.f,1.f,0.f);
    glTexCoord2f(0.f,256.f+grassShift); glVertex3f(-5.f,0.f,110.f);
    glTexCoord2f(0.f,0.f+grassShift); glVertex3f(-5.f,0.f,-100.f);
    glTexCoord2f(1.f,0.f+grassShift); glVertex3f(5.f,0.f,-100.f);
    glTexCoord2f(1.f,256.f+grassShift); glVertex3f(5.f,0.f,110.f);

    glEnd();

    glDisable(GL_TEXTURE_2D);


    // Sky
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,m_TextureID_[2]);

    glBegin(GL_QUADS);

    glTexCoord2f(0.f,0.f); glVertex3f(-90.f,-10.f,90.f);
    glTexCoord2f(1.f,0.f); glVertex3f(90.f,-10.f,90.f);
    glTexCoord2f(1.f,5.f); glVertex3f(90.f,180.f,90.f);
    glTexCoord2f(0.f,5.f); glVertex3f(-90.f,180.f,90.f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

}
