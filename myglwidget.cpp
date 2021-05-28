#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>

// Declarations des constantes
const unsigned int WIN = 900;

Point findCenter(Rect rectangle){
    return Point(rectangle.x+int(rectangle.width/2),rectangle.y+int(rectangle.height/2));
}

float processDistance(Point point1,Point point2){
    return sqrt((point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y));
}

float processAngle(Point point1, Point point2){
    if (point1.x<point2.x)
    {
        // Si le point1 a une abscisse plus petite que le 2 : main gauche
        return atan(float(point2.y-point1.y)/float(point2.x-point1.x))*180.0/3.14;
    }
    else{
        // Sinon le point1 : main droite
        return atan(float(point1.y-point2.y)/float(point1.x-point2.x))*180.0/3.14;
    }

}

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{

    // Reglage de la taille/position
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    //Ouverture de la webcam

    int frameWidth=640;
    int frameHeight=480;


    cap=VideoCapture(0); // open the default camera
    cout<<"width :"<<cap.get(CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height :"<<cap.get(CAP_PROP_FRAME_HEIGHT)<<endl;
    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }


    if(!face_cascade.load("C:/Users/thoma/Documents/ProjetBDM/res/fistCascade.xml"))
    {
        cerr<<"Error loading haarcascade"<<endl;
    }

    // Init output window
    namedWindow("WebCam",1);


    //Gestion du temps
    animationTimer.setInterval(15);
    animationTimer.start();


    connect(&animationTimer,  &QTimer::timeout, [&] {
        timeElapsed += increment;
        update();
    });


}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    //Couleur du fond
    glClearColor(0.f,0.f,0.f,.0f);

    //Activer le mode profondeur
    glEnable(GL_DEPTH_TEST);

    // Light activation
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // ambiant lignt
    GLfloat light_color_tab[] = { 1.f, 1.f, 1.f, 0.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_tab);

    GLfloat light_tab[] = { 0.f, 2.f, 0.f, 1.f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);

    barils=new Barrel();
    environment=new Ground();

    // Nettoyer les buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH);

    // Matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-5, 5, -5, 5, 3, 2000);
    float width=4;
    float height=3;
    gluPerspective(70.f,width/height,0.1f, 100.f);

    // Position de la caméra
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Placer la caméra
    //X latéral
    //Y hauteur
    //Z déplacement sens voiture
    gluLookAt(0,5,0,
              0,0,10,
              0,1,0);


}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{

    // Récupération de l'image webcam

    Mat frame,frame_gray;
    std::vector<Rect> fists;
    std::vector<Point> fistsCenter;
    // Get frame
    cap >> frame;
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    //-- Detect fists
    face_cascade.detectMultiScale(frame_gray, fists, 1.1, 4, 0, Size(60, 60));
    if (fists.size()>0)
    {
        // Process and draw fists center
        for (int i=0;i<(int)fists.size();i++){
            circle(frame,findCenter(fists[i]),10,Scalar(255),10);
        }
        if ((int)fists.size()>=2)
        {
            //Si on détecte au moins 2 poings
            angle=processAngle(findCenter(fists[0]),findCenter(fists[1]));
            distance=processDistance(findCenter(fists[0]),findCenter(fists[1]));
        }

        else
        {
            angle=0;
            distance=0.0;
        }

    }

    // Display frame
    imshow("WebCam", frame);


    //Vérifie si zone d'arrêt
    insideStopZone();


    //Zone d'arrêt
    if(isStopZone && countdown>=0){
        //Si on est arrêté
        increment=0.0f;
        countdown-=1;
        angle=0;
    }
    else if (countdown<0)
    {
        //On quitte la zone d'arrêt
        increment=1.0f;
        countdown=50;
        myCar->parked();
        barrelPressed=false;
    }

    else if (distance<300 && distance>0){
        // Arrêt si les poings sont proches
        increment=0.0f;
        angle=0;
    }
    else{
        increment=1.0f;
        gauge->decrease();
    }


    //Sol
    environment->display(timeElapsed);
    gauge->display();


    // Zone d'arrêt
    stopZone=new StopZone(myCar,timeElapsed);
    stopZone->display(barrelPressed);
    if (stopZone->getCoord()[2]<=-3){
        // Si les barils sont passés en négatifs on les reremplis
        barrelPressed=false;
    }


    // Voiture principale
    myCar->turn(0.4/45.0*angle);

    // Rafraichissement des voitures
    opponentCar1->display(timeElapsed);
    opponentCar2->display(timeElapsed);
    opponentCar3->display(timeElapsed);
    opponentCar4->display(timeElapsed);
    myCar->display(timeElapsed);




    //Gestion des collisions
    hitManager();

    // Vérifie s'il reste de l'essence
    emptyFuelManager();


}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
    {
        animationTimer.stop();
        int reponse = QMessageBox::question(this, "Fermer", "Voulez-vous vraiment quitter la partie ? \n Score actuel : "+QString::fromStdString(std::to_string(int(timeElapsed))), QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            exit(0);
        }
        else{
            animationTimer.start();
        }
        break;
    }


        // Cas par defaut
    default:
    {
        // Ignorer l'evenement
        event->ignore();
        return;
    }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    update();
}


void MyGLWidget::insideStopZone(){
    //Vérifie si la voiture est dans une zone d'arrêt
    if(abs(myCar->getCoord()[0]+stopZone->getCoord()[0])<0.5 &&
            abs(myCar->getCoord()[2]-stopZone->getCoord()[2])<2){
        isStopZone=true;
    }
    else{
        isStopZone=false;
    }

}

void MyGLWidget::emptyFuelManager(){
    if (gauge->getRate()<=0){
        animationTimer.stop();
        QMessageBox::information(this, "Perdu", "Vous êtes à sec. Votre score est de : "+QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
}

void MyGLWidget::hitManager(){
    //Gestion des collisions entre maVoiture et les voitures voitureOpposee
    if(abs(myCar->getCoord()[0]-opponentCar1->getCoord()[0])<0.8 &&
            abs(myCar->getCoord()[2]-opponentCar1->getCoord()[2])<0.8){
        animationTimer.stop();
        QMessageBox::about(this,"Perdu","Aïe, collision. Votre score est de : "+QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
    if(abs(myCar->getCoord()[0]-opponentCar2->getCoord()[0])<0.8 &&
            abs(myCar->getCoord()[2]-opponentCar2->getCoord()[2])<0.8){
        animationTimer.stop();
        QMessageBox::about(this,"Perdu","Aïe, collision. Votre score est de : "+QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
    if(abs(myCar->getCoord()[0]-opponentCar3->getCoord()[0])<0.8 &&
            abs(myCar->getCoord()[2]-opponentCar3->getCoord()[2])<0.8){
        animationTimer.stop();
        QMessageBox::about(this,"Perdu","Aïe, collision. Votre score est de : "+QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
    if(abs(myCar->getCoord()[0]-opponentCar4->getCoord()[0])<0.8 &&
            abs(myCar->getCoord()[2]-opponentCar4->getCoord()[2])<0.8){
        animationTimer.stop();
        QMessageBox::about(this,"Perdu","Aïe, collision. Votre score est de : "+QString::fromStdString(std::to_string(int(timeElapsed))));
        exit(0);
    }
}




void MyGLWidget::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
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

        float width=4;
        float height=3;
        gluPerspective(70.f,width/height,0.1f, 100.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,5,0,
                  0,0,10,
                  0,1,0);
        glLoadName(1);


        GLUquadric* barrelQuadric_ = gluNewQuadric();
        gluQuadricDrawStyle(barrelQuadric_, GLU_FILL);

        glPushMatrix();
        stopZone->baril1->drawBarrel(true,stopZone->getCoord()[2]+2.0,barrelQuadric_);
        glPopMatrix();


        gluDeleteQuadric(barrelQuadric_);

        glFlush();

        hits = glRenderMode(GL_RENDER);
        qDebug()<<hits;
        if (hits == 1){
            if (!barrelPressed){
                // Si le baril n'a pas été cliqué on fait le plein
                gauge->addFuel();
            }
            barrelPressed = true;
            event->accept();
            update();
        }


    }
}


