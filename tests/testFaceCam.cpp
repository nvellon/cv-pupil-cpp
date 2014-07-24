#include "../src/cvpupil.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    cv::namedWindow("test", CV_WINDOW_NORMAL);

    cv::VideoCapture cap(0);

    cvp::face::Tracker tracker;
    cvp::face::HaarDetection* strategy = new cvp::face::HaarDetection("/home/nicolas/repos/git/cv-pupil-cpp/assets/haarcascades/haarcascade_frontalface_default.xml", 0.01);

    if (cap.isOpened()) {
        cv::Mat frame, pupil;

        while (cv::waitKey(15)) {
            cap >> frame;
            if (frame.empty())
                break;

            cv::flip(frame, frame, 1);

            tracker.detect(strategy, frame);

            if (tracker.getCount() > 0) {
                vector<cv::Rect> faces = tracker.getRects();

                cout << "Faces found: " << faces.size() << endl;

                for (int i = 0; i < faces.size(); i++) {
                    cv::rectangle(frame, faces[i], CV_RGB(255, 0, 0));
                }
            }

            cv::imshow("test", frame);
        }
    } else {
        cout << "Error: no camera loaded." << endl;
    }

    delete strategy;

    return 0;
}
