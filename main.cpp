#include "trk/trk.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    //trk::detectFile("img/ojo.jpg");
    //trk::detectFile("img/ojo2.jpg");
	//trk::detectFile("img/ojo3.jpg");
	//trk::detectFile("img/ojo4.jpg");
	
	trk::detectCam();

	cv::waitKey(0);

	return 0;
}
