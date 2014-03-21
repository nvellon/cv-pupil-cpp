#include "trk/trk.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    //trk::detect("img/ojo.jpg");
    //trk::detect("img/ojo2.jpg");
	trk::detect("img/ojo3.jpg");
	//trk::detect("img/ojo4.jpg");

	cv::waitKey(0);

	return 0;
}
