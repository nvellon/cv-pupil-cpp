#include "trk.hpp"

/**
 * Eyes detection
 *
 * @param const char* cascadePath Cascade classifier file path
 * @param cv::Mat     img         Image matrix
 *
 * @return std::vector<cv::Rect>
 */
std::vector<cv::Rect> trk::detectEyes(const char* cascadePath, cv::Mat img) 
{
std::vector<cv::Rect> areas;
cv::Mat img_gray;

    cv::CascadeClassifier cascade;
    cascade.load(cascadePath);

    cv::cvtColor(img, img_gray, CV_RGB2GRAY);

    cascade.detectMultiScale(
        img_gray, 
        areas,
        1.1, // scale factor 
        2, // min neighbors
        0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        //|CV_HAAR_DO_CANNY_PRUNING
        |CV_HAAR_SCALE_IMAGE
        ,
        cv::Size(cvRound(img.rows*0.3), cvRound(img.cols*0.3)) // min size
    );

    return areas;
}

/**
 * Pupil detection
 *
 * @param cv::Mat eye Eye image matrix
 *
 * @return cv::Rect
 */
cv::Rect trk::detectPupil(cv::Mat eye)
{
cv::Mat gray;

	// Invert the source image and convert to grayscale
	cv::cvtColor(eye, gray, CV_BGR2GRAY);

	// Other filters
	//cv:equalizeHist(gray, gray); 
    //cv::blur(gray, gray, Size(30, 30), Point(-1,-1), BORDER_DEFAULT);

    cv::Mat candidate;
	std::vector<cv::Point> maxContour;

	for (int threshold = 0; threshold <= 255; threshold++) {
	    // Convert to binary image by thresholding it
	    cv::threshold(gray, candidate, threshold, 255, cv::THRESH_BINARY_INV);

	    // Find all contours
	    std::vector<std::vector<cv::Point> > contours;
	    findContours(candidate, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	    // Fill holes in each contour
	    cv::drawContours(candidate, contours, -1, CV_RGB(255,255,255), -1);

	    for (int i = 0; i < contours.size(); i++) {
	        if (maxContour.empty())
	            maxContour = contours[i];

	        double areaMaxContour = cv::contourArea(maxContour);

		    double area = cv::contourArea(contours[i]);
		    cv::Rect rect = cv::boundingRect(contours[i]);
		    int radius = rect.width/2;

		    // If contour: has round shape
		    // Then it is the pupil
		    if (area >= 200 &&
		        std::abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
			    std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2 &&
			    area > areaMaxContour)
		    {
		        maxContour = contours[i];
		    }
	    }
	}

	return cv::boundingRect(maxContour);
}

/**
 * Pupil tracking
 *
 * @param cv::Mat eye Eye image matrix
 * @param cv::Mat tpl Template image matrix
 *
 * @return cv::Point
 */
cv::Point trk::trackPupil(cv::Mat eye, cv::Mat tpl)
{
cv::Mat result;
int match_method = CV_TM_CCORR_NORMED;

    cv::matchTemplate(eye, tpl, result, match_method);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

	double minVal; double maxVal; 
	cv::Point minLoc, maxLoc, matchLoc;
	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
	if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
	    matchLoc = minLoc;
	else 
	    matchLoc = maxLoc;
	
	return matchLoc;
}

/**
 * Run detection and show result
 *
 * @param const char* name Image file path to process
 *
 * @return void
 */
void trk::detect(const char* name)
{
    // Load image
	cv::Mat img = cv::imread(name);
	if (!img.empty()) {
	    // shrink image
	    int minRows = 300;
	    if (img.rows > minRows) {
	        int minCols = cvRound(((double)minRows / (double)img.rows) * (double)img.cols);
            cv::resize(img, img, cv::Size(minCols, minRows), 0, 0, cv::INTER_LINEAR);
	    }

        cv::namedWindow(name, CV_WINDOW_NORMAL);

        // Eyes detection
        std::cout << "Eyes detection" << std::endl;
        double t = (double)cvGetTickCount();
        
        const char* cascadePath = "/usr/share/opencv/haarcascades/haarcascade_eye.xml";
        std::vector<cv::Rect> eyes = trk::detectEyes(cascadePath, img);
        
        t = (double)cvGetTickCount() - t;
        printf("- time = %g ms\n", t/((double)cvGetTickFrequency()*1000.));

        cv::Mat eye;
        cv::Rect eyeArea;
        if (!eyes.empty()) {
	        eyeArea = eyes[0];
		    eye = img(eyeArea);
	    } else {
	        eye = img.clone();
	        eyeArea.x = 0;
	        eyeArea.y = 0;
	        eyeArea.width = eye.cols;
	        eyeArea.height = eye.rows;
	    }

        // Pupil detection
        std::cout << "Pupil detection" << std::endl;
        t = (double)cvGetTickCount();

        cv::Rect pupil = trk::detectPupil(eye);

        t = (double)cvGetTickCount() - t;
        printf("- time = %g ms\n", t/((double)cvGetTickFrequency()*1000.));
        
        if (pupil.width > 0) {
            std::cout << "Pupil tracking" << std::endl;
            t = (double)cvGetTickCount();

	        cv::Point match = trackPupil(img, img(pupil));
	        
	        t = (double)cvGetTickCount() - t;
            printf("- time = %g ms\n", t/((double)cvGetTickFrequency()*1000.));
	        
	        int radius = pupil.width/2;
	        int x = eyeArea.x + match.x + radius;
	        int y = eyeArea.y + match.y + radius;
		    cv::circle(img, cv::Point(x, y), radius, CV_RGB(255,0,0), 2);
        }

        cv::imshow(name, img);
    }
}
