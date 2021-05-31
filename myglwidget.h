#include "car.h"
#include "ground.h"
#include "barrel.h"
#include "gauge.h"
#include "stopzone.h"
#include "webcam.h"

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "mutex"
#include <thread>
#include <QMessageBox>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;


// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget {
private:
    //Voitures
    Car *myCar = new Car(false, 0.0, 0.0);
    Car *opponentCar1 = opponentCar1 = new Car(true, 2.0, 0.0);
    Car *opponentCar2 = new Car(true, -2.0, -20.0);
    Car *opponentCar3 = new Car(true, 0.0, -53.0);
    Car *opponentCar4 = new Car(true, -4.0, -70.0);

    //Sol, ciel et route
    Ground *environment = new Ground();

    //Jauge d'essence
    Gauge *gauge = new Gauge();

    // Barils d'essence
    Barrel *barils;

    //Zone d'arrêt
    StopZone *stopZone = new StopZone(myCar);

    // Gestion des arrêts
    bool isStopZone = false;
    int countdown = 50;

    //Barils pressés ou non
    bool barrelClicked = false;

    // Rafraichissement par un timer
    float timeElapsed{0.0f};
    QTimer animationTimer;
    QTimer pauseTimer;
    float increment = 1.0f;


    // Webcam
    Webcam webcam;
    VideoCapture cap;

    //Angle et distance des poings
    float angle;
    float distance;

    // Fichier Classifieur
    CascadeClassifier face_cascade;

public:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent *event);

    // Constructeurs
    MyGLWidget(QWidget *parent = nullptr);

    void insideStopZone();

    void hitManager();

    void fuelManager();

    void mousePressEvent(QMouseEvent *event);
};
