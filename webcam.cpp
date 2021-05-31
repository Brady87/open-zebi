#include "webcam.h"

Point findCenter(Rect rectangle) {
    // Calcule le centre des rectangles
    return Point(rectangle.x + int(rectangle.width / 2), rectangle.y + int(rectangle.height / 2));
}

float processDistance(Point point1, Point point2) {
    // Calcule la distance euclidienne entre les points
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

float processAngle(Point point1, Point point2) {
    // Détermine l'angle entre les centres des poings
    if (point1.x < point2.x) {
        // Si le point1 a une abscisse plus petite que le 2 : main gauche
        return atan(float(point2.y - point1.y) / float(point2.x - point1.x)) * 180.0 / 3.14;
    } else {
        // Sinon le point1 : main droite
        return atan(float(point1.y - point2.y) / float(point1.x - point2.x)) * 180.0 / 3.14;
    }

}

Mat Webcam::getFrame() const {
    return frame;
}

Webcam::Webcam() {
    //Ouverture de la webcam
    int frameWidth = 640;
    int frameHeight = 480;

    cap = VideoCapture(0); // Ouvre la caméra par défaut
    cap.set(CAP_PROP_FRAME_WIDTH, frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT, frameHeight);
    if (!cap.isOpened())  // Vérification de l'ouverture de la webcam
    {
        cerr << "Erreur lors de l'ouverture de la webcam" << endl;
    }


    if (!face_cascade.load("C:/Users/thoma/Documents/ProjetBDM/res/fistCascade.xml")) {
        cerr << "Erreur lors du chargement du fichier Cascade de Haar" << endl;
    }

    // Fenêtre auxiliaire
    namedWindow("WebCam", 1);
}

void Webcam::capturingFrame() {
    Mat frame, frame_gray;
    // Image de la webcam
    cap >> frame;
    // Effet Miroir
    cv::flip(frame, frame, 1);
    // Conversion en N&B
    cv::cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    std::vector <Rect> fists;
    std::vector <Point> fistsCenter;
    // Détection des points via la cascade de Haar
    face_cascade.detectMultiScale(frame_gray, fists, 1.1, 4, 0, Size(60, 60));
    if (fists.size() > 0) {
        // Calcul des centres des poings
        for (int i = 0; i < (int) fists.size(); i++) {
            circle(frame, findCenter(fists[i]), 10, Scalar(255), 10);
        }
        if ((int) fists.size() >= 2) {
            //Si on détecte au moins 2 poings
            angle = processAngle(findCenter(fists[0]), findCenter(fists[1]));
            distance = processDistance(findCenter(fists[0]), findCenter(fists[1]));
        } else {
            angle = 0;
            distance = 0.0;
        }

    }
    // On affiche l'image
    imshow("Webcam", frame);
}


float Webcam::getDistance() const {
    return distance;
}

void Webcam::setDistance(float value) {
    distance = value;
}

float Webcam::getAngle() const {
    return angle;
}