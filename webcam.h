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
    VideoCapture cap;
    CascadeClassifier face_cascade;
    float angle;
    float distance;
    Mat frame;
public:
    Webcam();
    void capturingFrame();
    void processingDistanceAndAngle();
    float getAngle() const;
    void setAngle(float value);
    float getDistance() const;
    void setDistance(float value);
    Mat getFrame() const;
    void setFrame(const Mat &value);
};

#endif // WEBCAM_H
