#include "../src/cvpupil.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    cv::namedWindow("test", CV_WINDOW_NORMAL);

    cv::VideoCapture cap(0);

    cvp::eye::Tracker tracker;
    cvp::eye::HaarDetection* strategy = new cvp::eye::HaarDetection("/home/nicolas/repos/git/cv-pupil-cpp/assets/haarcascades/haarcascade_eye.xml", 0.01);

    if (cap.isOpened()) {
        cv::Mat frame, pupil;

        while (cv::waitKey(15)) {
            cap >> frame;
            if (frame.empty())
                break;

            cv::flip(frame, frame, 1);

            tracker.detect(strategy, frame);

            if (tracker.getCount() > 0) {
                vector<cv::Rect> eyes = tracker.getRects();

                cout << "Eyes found: " << eyes.size() << endl;

                for (int i = 0; i < eyes.size(); i++) {
                    cv::rectangle(frame, eyes[i], CV_RGB(255, 0, 0));
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
