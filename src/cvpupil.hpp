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

    namespace eye
    {
    /**
     * Eye tracking class
     */
    class Tracker;

    /**
     * EyeHaarDetection class
     */
    class HaarDetection;
    }

    namespace pupil
    {
    /**
     * Pupil tracking class
     */
    class Tracker;

    /**
     * PupilContourDetection class
     */
    class ContourDetection;

    /**
     * PupilTemplateTracking class
     */
    class TemplateTracking;
    }
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
    virtual void track(cvp::Strategy* strategy, cv::Mat img)=0;
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
 * Eye namespace
 */

/**
 * Eye tracking class
 */
class cvp::eye::Tracker : public cvp::Tracker
{
protected:
    cv::Mat _srcImage;
    vector<cv::Rect> _eyes;

public:
    Tracker();
    ~Tracker();
    void detect(cvp::Strategy* strategy, cv::Mat img);
    void track(cvp::Strategy* strategy, cv::Mat img);
    int getCount();
    vector<cv::Rect> getRects();
    vector<cv::Mat> getMats();
};

/**
 * Eye HaarDetection class
 */
class cvp::eye::HaarDetection : public cvp::Strategy
{
protected:
    double _minSizeRatio;
    const char* _cascadePath;
    cv::CascadeClassifier _cascade;
    cv::Mat _srcImage;
public:
    HaarDetection(const char* cascadePath, double minSizeRatio);
    ~HaarDetection(){}
    vector<cv::Rect> process(cv::Mat img);
};


/**
 * Pupil namespace
 */

/**
 * Pupil tracking class
 */
class cvp::pupil::Tracker : public cvp::Tracker
{
protected:
    cv::Mat _srcImage;
    cv::Rect _rect;

public:
    Tracker();
    ~Tracker();
    void detect(cvp::Strategy* strategy, cv::Mat img);
    void track(cvp::Strategy* strategy, cv::Mat img);
    cv::Rect getRect();
};

/**
 * Pupil ContourDetection class
 */
class cvp::pupil::ContourDetection : public cvp::Strategy
{
protected:
    cv::Mat _srcImage;
    cv::Rect _rect;
    vector<cv::Point> _contour;
public:
    ContourDetection();
    ~ContourDetection(){}
    vector<cv::Rect> process(cv::Mat img);
};

/**
 * PupilTemplateTracking class
 */
class cvp::pupil::TemplateTracking : public cvp::Strategy
{
protected:
    cv::Mat _srcImage;
    cv::Rect _rect;
    vector<cv::Point> _contour;
public:
    TemplateTracking();
    ~TemplateTracking(){}
    vector<cv::Rect> process(cv::Mat img);
};