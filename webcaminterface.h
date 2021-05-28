#ifndef WEBCAMINTERFACE_H
#define WEBCAMINTERFACE_H
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include "mutex"
#include <thread>

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;


class WebcamInterface
{
public:
    WebcamInterface();
    float angle=0;
    float distance=0;
};

#endif // WEBCAMINTERFACE_H
