#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>

// Declarations des constantes
const unsigned int WIN = 900;

// Constructeur
MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

    // Reglage de la taille/position
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    //Gestion du temps
    animationTimer.setInterval(15);
    animationTimer.start();


    connect(&animationTimer, &QTimer::timeout, [&] {
        timeElapsed += increment;
        update();
    });


}

// Fonction d'initialisation
void MyGLWidget::initializeGL() {
    //Couleur du fond
    glClearColor(0.f, 0.f, 0.f, .0f);

    //Activer le mode profondeur
    glEnable(GL_DEPTH_TEST);

    // Light activation
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // ambiant lignt
    GLfloat light_color_tab[] = {1.f, 1.f, 1.f, 0.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_tab);

    GLfloat light_tab[] = {0.f, 2.f, 0.f, 1.f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);

    barils = new Barrel();
    environment = new Ground();

    // Nettoyer les buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH);

    // Matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-5, 5, -5, 5, 3, 2000);
    float width = 4;
    float height = 3;
    gluPerspective(70.f, width / height, 0.1f, 100.f);

    // Position de la caméra
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Placer la caméra
    //X latéral
    //Y hauteur
    //Z déplacement sens voiture
    gluLookAt(0, 5, 0,
              0, 0, 10,
              0, 1, 0);


}

// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height) {
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

// Fonction d'affichage
void MyGLWidget::paintGL() {

    // Récupération de l'image webcam
    webcam.capturingFrame();

    // Récupération des valeurs de distance et d'angle entre les poings
    angle = webcam.getAngle();
    distance = webcam.getDistance();

    //Vérifie si zone d'arrêt
    insideStopZone();

    //Zone d'arrêt
    if (isStopZone && countdown >= 0) {
        // Si on est dans une zone d'arrêt on s'arrête
        increment = 0.0f;
        countdown -= 1;
        angle = 0;
    } else if (countdown < 0) {
        //On quitte la zone d'arrêt si le compte à rebours dans la zone d'arrêt est fini
        increment = 1.0f;
        countdown = 50;
        myCar->park();
        barrelClicked = false;
    } else if (distance < 300 && distance != 0) {
        // On s'arrête si les poings sont proches mais que la distance n'est pas nulle
        increment = 0.0f;
        angle = 0;
    } else {
        increment = 1.0f;
        gauge->decrease();
    }


    //Sol
    environment->display(timeElapsed);
    gauge->display();

    // Zone d'arrêt
    // Si on ne recrée par une zone d'arrêt les barils ne sont pas texturés
    stopZone = new StopZone(myCar);
    stopZone->display(barrelClicked, timeElapsed);
    if (stopZone->getCoord()[2] <= -3) {
        // Si les barils sont passés en négatifs on les reremplis
        barrelClicked = false;
    }


    // Voiture principale tourne
    myCar->turn(0.4 / 45.0 * angle);

    // Rafraichissement des voitures
    opponentCar1->display(timeElapsed);
    opponentCar2->display(timeElapsed);
    opponentCar3->display(timeElapsed);
    opponentCar4->display(timeElapsed);
    myCar->display(timeElapsed);

    //Gestion des collisions
    hitManager();

    // Vérifie s'il reste de l'essence
    fuelManager();


}

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Q: {
            // On arrête le raffraichissement du jeu
            animationTimer.stop();
            int reponse = QMessageBox::question(this, "Fermer",
                                                "Voulez-vous vraiment quitter la partie ? \n Score actuel : " +
                                                QString::fromStdString(std::to_string(int(timeElapsed))),
                                                QMessageBox::Yes | QMessageBox::No);

            if (reponse == QMessageBox::Yes) {
                exit(0);
            } else {
                // On reprend le raffraichissement du jeu
                animationTimer.start();
            }
            break;
        }


            // Cas par defaut
        default: {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'événement et màj de la scène
    event->accept();
    update();
    increment += 0.05;
}

//Vérifie si la voiture est dans une zone d'arrêt
void MyGLWidget::insideStopZone() {
    if (abs(myCar->getCoord()[0] + stopZone->getCoord()[0]) < 0.5 &&
        abs(myCar->getCoord()[2] - stopZone->getCoord()[2]) < 2) {
        isStopZone = true;
    } else {
        isStopZone = false;
    }

}

// Vérifie qu'il reste encore de l'essence
void MyGLWidget::fuelManager() {
    if (gauge->getRate() <= 0) {
        animationTimer.stop();
        QMessageBox::information(this, "Perdu", "Vous êtes à sec. Votre score est de : " +
                                                QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
}

// Gestion des collisions entre ma voiture myCar et les 4 voitures adverses opponentCar
void MyGLWidget::hitManager() {
    if (abs(myCar->getCoord()[0] - opponentCar1->getCoord()[0]) < 0.8 &&
        abs(myCar->getCoord()[2] - opponentCar1->getCoord()[2]) < 0.8) {
        animationTimer.stop();
        QMessageBox::about(this, "Perdu", "Aïe, collision. Votre score est de : " +
                                          QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    } else if (abs(myCar->getCoord()[0] - opponentCar2->getCoord()[0]) < 0.8 &&
               abs(myCar->getCoord()[2] - opponentCar2->getCoord()[2]) < 0.8) {
        animationTimer.stop();
        QMessageBox::about(this, "Perdu", "Ouille, collision. Votre score est de : " +
                                          QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    } else if (abs(myCar->getCoord()[0] - opponentCar3->getCoord()[0]) < 0.8 &&
               abs(myCar->getCoord()[2] - opponentCar3->getCoord()[2]) < 0.8) {
        animationTimer.stop();
        QMessageBox::about(this, "Perdu", "Aïe, collision. Votre score est de : " +
                                          QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    } else if (abs(myCar->getCoord()[0] - opponentCar4->getCoord()[0]) < 0.8 &&
               abs(myCar->getCoord()[2] - opponentCar4->getCoord()[2]) < 0.8) {
        animationTimer.stop();
        QMessageBox::about(this, "Perdu", "Ouille, collision. Votre score est de : " +
                                          QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
    // Gestion des clics sur les barils
    if (event->button() == Qt::LeftButton) {
        GLint hits;
        GLuint selectBuf[512];
        glSelectBuffer(512, selectBuf);

        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(event->x(), (viewport[3] - event->y()), 2.0, 2.0, viewport);

        float width = 4;
        float height = 3;
        gluPerspective(70.f, width / height, 0.1f, 100.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 5, 0,
                  0, 0, 10,
                  0, 1, 0);
        glLoadName(1);


        GLUquadric *barrelQuadric_ = gluNewQuadric();
        gluQuadricDrawStyle(barrelQuadric_, GLU_FILL);

        glPushMatrix();

        // Baril cliquable
        Barrel barrel = stopZone->getBarrel();
        barrel.draw(stopZone->getCoord()[2] + 2.0, barrelQuadric_);
        glPopMatrix();


        gluDeleteQuadric(barrelQuadric_);

        glFlush();

        hits = glRenderMode(GL_RENDER);
        qDebug() << hits;
        if (hits == 1) {
            if (!barrelClicked) {
                // Si le baril n'a pas été cliqué on fait le plein
                gauge->addFuel();
            }
            barrelClicked = true;
            event->accept();
            update();
        }


    }
}


