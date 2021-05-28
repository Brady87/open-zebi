/*#include "webcaminterface.h"


Point findCenter(Rect rectangle){
    return Point(rectangle.x+int(rectangle.width/2),rectangle.y+int(rectangle.height/2));
}

float processDistance(Point point1,Point point2){
    return sqrt((point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y));
}

float processAngle(Point point1, Point point2){
    if (point1.x<point2.x)
    {
        //Si le point1 a une abscisse plus petite que le 2 : main gauche
        return atan(float(point2.y-point1.y)/float(point2.x-point1.x))*180.0/3.14;
    }
    else{
        //Sinon le point1 : main droite
        return atan(float(point1.y-point2.y)/float(point1.x-point2.x))*180.0/3.14;
    }

}


WebcamInterface::WebcamInterface()
{
    int frameWidth=640;
    int frameHeight=480;

    VideoCapture cap(0); // open the default camera
    cout<<"width :"<<cap.get(CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height :"<<cap.get(CAP_PROP_FRAME_HEIGHT)<<endl;
    cap.set(CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }

    CascadeClassifier face_cascade;
    if( !face_cascade.load( "C:/Users/thoma/Documents/Cours/FISE2/Semestre 8/Info/Bibliotheque de developpement multimedia/ProjetBDM/res/fist3.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
    }

    // Init output window
    namedWindow("WebCam",1);

    while(waitKey(5)<0)
    {
        //m.lock();
        Mat frame,frame_gray;
        std::vector<Rect> fists;
        std::vector<Point> fistsCenter;
        // Get frame
        cap >> frame;
        // Mirror effect
        cv::flip(frame,frame,1);
        // Convert to gray
        cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
        // Equalize graylevels
//        equalizeHist( frame_gray, frame_gray );
        //-- Detect fists
        face_cascade.detectMultiScale( frame_gray, fists, 1.1, 4, 0, Size(60, 60) );
        if (fists.size()>0)
        {
            // Draw green rectangle and process fists center
            for (int i=0;i<(int)fists.size();i++){
                //rectangle(frame,fists[i],Scalar(0,255,0),2);
                //fistsCenter.push_back(findCenter(fists[i]));
                circle(frame,findCenter(fists[i]),10,Scalar(255),10);

            }
            if ((int)fists.size()>=2)
            {
                //Si on détecte 2 mains
                //std::cout<<"Angle : "<<processAngle(findCenter(fists[0]),findCenter(fists[1]))<<"/"<<endl;
                angle=processAngle(findCenter(fists[0]),findCenter(fists[1]));
                distance=processDistance(findCenter(fists[0]),findCenter(fists[1]));
            }

            /*if ((int)fists.size()>=1)
            {
                std::cout<<"yCoor : "<<findCenter(fists[0]).y<<"/"<<endl;
            }*/

        //}

        // Display frame
        //imshow("WebCam", frame);
    //}

    // the camera will be deinitialized automatically in VideoCapture destructor

//}

