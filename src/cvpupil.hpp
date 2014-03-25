#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;

/**
 * cvp namespace
 */
namespace cvp
{
/**
 * Tracker interface
 */
class Tracker;

/**
 * Eye tracking class
 */
class Eye;

/**
 * Pupil tracking class
 */
class Pupil;
}

/**
 * Tracker interface
 */
class cvp::Tracker
{
public:
    Tracker(){}
    virtual ~Tracker(){}
    virtual void detect(cv::Mat img)=0;
    virtual void track(cv::Mat img)=0;
};

/**
 * Eye tracking class
 */
class cvp::Eye : cvp::Tracker
{
protected:
    double _minSizeRatio;
    cv::CascadeClassifier _cascade;
    cv::Mat _srcImage;
    vector<cv::Rect> _eyes;

public:
    Eye(const char* cascadePath, double minSizeRatio);
    ~Eye();
    void detect(cv::Mat img);
    void track(cv::Mat img);
    int getCount();
    vector<cv::Rect> getRects();
    vector<cv::Mat> getMats();
};

/**
 * Pupil tracking class
 */
class cvp::Pupil : cvp::Tracker
{
public:
    Pupil(){}
    ~Pupil(){}
    void detect(cv::Mat img){}
    void track(cv::Mat img){}
};