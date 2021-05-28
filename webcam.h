#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;



class Webcam
{
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
    float getAngle() const;
    void setAngle(float value);
    float getDistance() const;
    void setDistance(float value);
    Mat getFrame() const;
    void setFrame(const Mat &value);
};

#endif // WEBCAM_H
