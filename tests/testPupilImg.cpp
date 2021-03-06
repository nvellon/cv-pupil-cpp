#include "../src/cvpupil.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("img/ojo3.jpg");

    if (!img.empty()) {
        cvp::eye::Tracker eye;

        cvp::eye::HaarDetection* strategy = new cvp::eye::HaarDetection("/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml", 0.2);
        cvp::pupil::ContourDetection* pStrategy = new cvp::pupil::ContourDetection();

        eye.detect(strategy, img);

        if (eye.getCount() > 0) {
            vector<cv::Mat> eyes = eye.getMats();

            cout << "Eyes found: " << eyes.size() << endl;

            for (int i = 0; i < eyes.size(); i++) {

                cvp::pupil::Tracker pupil;
                pupil.detect(pStrategy, eyes[i]);

                cv::rectangle(eyes[i], pupil.getRect(), CV_RGB(255, 0, 0));

                string wName = "Eye ";
                char wNum[21];
                sprintf(wNum, "%d", i);
                wName += wNum;

                cv::imshow(wName, eyes[i]);
            }

        } else {
            cout << "Error: no eyes found." << endl;
        }
    } else {
        cout << "Error: no image loaded." << endl;
    }

    cout << "Press any key to finish." << endl;

    cv::waitKey(0);

    return 0;
}
