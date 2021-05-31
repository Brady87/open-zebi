#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class Webcam {
private:
    // Fichier webcam
    VideoCapture cap;

    // Fichier cascade de Haar
    CascadeClassifier face_cascade;

    // Angle et distance des poings
    float angle;
    float distance;

    // Image
    Mat frame;
public:
    Webcam();

    // Capture, affiche l'image de cap et calcule les poings (angle et distance)
    void capturingFrame();

    // renvoie l'angle entre les 2 poings
    float getAngle() const;

    // renvoie la distance entre les 2 poings
    float getDistance() const;

    //renvoie la frame
    Mat getFrame() const;
};

#endif // WEBCAM_H
