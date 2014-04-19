#include "../src/cvpupil.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("img/ojo3.jpg");

    if (!img.empty()) {
        cvp::eye::Tracker tracker;
        cvp::eye::HaarDetection* strategy = new cvp::eye::HaarDetection("/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml", 0.2);

        tracker.detect(strategy, img);

        if (tracker.getCount() > 0) {
            vector<cv::Mat> eyes = tracker.getMats();

            cout << "Eyes found: " << eyes.size() << endl;

            for (int i = 0; i < eyes.size(); i++) {
                string wName = "Eye ";
                char wNum[21];
                sprintf(wNum, "%d", i);
                wName += wNum;

                cv::imshow(wName, eyes[i]);
            }

        } else {
            cout << "Error: no eyes found." << endl;
        }

        delete strategy;

    } else {
        cout << "Error: no image loaded." << endl;
    }

    cout << "Press any key to finish." << endl;

    cv::waitKey(0);

    return 0;
}
