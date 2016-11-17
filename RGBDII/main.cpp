
#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char* argv[])
{

	// setup OpenCV
	cv::Mat img = cv::imread("C:\\Users\\Benoit\\Desktop\\ETS\\TUM\\Medical AR\\Exercise\\medicalAR-RGBDII\\Images\\video.jpg");
	cv::Mat img_depth = cv::imread("C:\\Users\\Benoit\\Desktop\\ETS\\TUM\\Medical AR\\Exercise\\medicalAR-RGBDII\\Images\\depth.png", CV_LOAD_IMAGE_UNCHANGED);

	double min;
	double max;
	cv::minMaxIdx(img_depth, &min, &max);
	cv::Mat adjMap;
	cv::convertScaleAbs(img_depth, adjMap, 255 / max);
	cv::applyColorMap(adjMap, adjMap, cv::COLORMAP_JET);

	cv::VideoCapture cap;
	cap.open(0);
	cv::Mat img_bgr;
	/* Loop until the user closes the window */
	while (true)
	{

		int key = 0;
		cap.read(img_bgr);
		cv::flip(img_bgr, img_bgr, 1);
		if (img_bgr.empty()){
			std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
			cap.open(0);
			//cv::waitKey(1000); // Wait for one sec.

			continue;
		}
		cv::imshow("img_live", img_bgr);
		cv::imshow("img", img);
		cv::imshow("depth", adjMap);
		key = cv::waitKey(1);
		if (key == 27){
			break;
		}

	}


	return 0;
}
