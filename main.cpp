#include "trk/trk.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    //showImg("img/ojo.jpg");
    //showImg("img/ojo2.jpg");
	//showImg("img/ojo3.jpg");
	trk::detect("img/ojo4.jpg");

	cv::waitKey(0);

	return 0;
}
