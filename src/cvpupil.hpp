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
 * Strategy interface
 */
class Strategy;

/**
 * EyeHaarDetection class
 */
class EyeHaarDetection;

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
    virtual void detect(cvp::Strategy* strategy, cv::Mat img)=0;
    virtual void track(cv::Mat img)=0;
};

/**
 * Strategy interface
 */
class cvp::Strategy
{
public:
    Strategy(){}
    virtual ~Strategy(){}
    virtual vector<cv::Rect> process(cv::Mat img)=0;
};

/**
 * EyeHaarDetection class
 */
class cvp::EyeHaarDetection : public cvp::Strategy
{
protected:
    double _minSizeRatio;
    cv::CascadeClassifier _cascade;
    cv::Mat _srcImage;
public:
    EyeHaarDetection(const char* cascadePath, double minSizeRatio);
    ~EyeHaarDetection(){}
    vector<cv::Rect> process(cv::Mat img);
};

/**
 * Eye tracking class
 */
class cvp::Eye : public cvp::Tracker
{
protected:
    cv::Mat _srcImage;
    vector<cv::Rect> _eyes;

public:
    Eye();
    ~Eye();
    void detect(cvp::Strategy* strategy, cv::Mat img);
    void track(cv::Mat img);
    int getCount();
    vector<cv::Rect> getRects();
    vector<cv::Mat> getMats();
};

/**
 * Pupil tracking class
 */
class cvp::Pupil : public cvp::Tracker
{
protected:
    cv::Mat _srcImage;
    cv::Rect _rect;
    vector<cv::Point> _contour;

public:
    Pupil();
    ~Pupil();
    void detect(cv::Mat img);
    void track(cv::Mat img);
    cv::Rect getRect();
};