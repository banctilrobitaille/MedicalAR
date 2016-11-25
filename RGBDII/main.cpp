
#include <iostream>
#include <numeric>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

cv::Mat displayDepthImage(cv::Mat depthImage);
cv::Mat calculateMeanDepthFrom(std::vector<cv::Mat> depthImages);

int main(int argc, char* argv[])
{
	const std::string IMAGES_PATH = "..\\Images\\";
	const std::string INIT_DEPTH_IMAGES_PATH = "..\\init\\depth\\";
	const std::string JPG_EXTENSION = ".jpg";
	const std::string PNG_EXTENSION = ".png";
	const std::string DEPTH = "depth";
	const int NUMBER_OF_DEPTH_IMAGES = 102;

	cv::Mat img = cv::imread(IMAGES_PATH + "video.jpg");
	cv::Mat img_depth = cv::imread(IMAGES_PATH + "depth.png", CV_LOAD_IMAGE_UNCHANGED);

	double min;
	double max;
	cv::minMaxIdx(img_depth, &min, &max);
	cv::Mat adjMap;
	cv::convertScaleAbs(img_depth, adjMap, 255 / max);
	cv::applyColorMap(adjMap, adjMap, cv::COLORMAP_JET);

	cv::VideoCapture cap;
	cap.open(0);
	cv::Mat img_bgr;

	std::vector<cv::Mat> depthImages;

	for (int i = 0; i < NUMBER_OF_DEPTH_IMAGES; i++){
		depthImages.push_back(cv::imread(INIT_DEPTH_IMAGES_PATH + DEPTH + std::to_string(i) + PNG_EXTENSION, CV_LOAD_IMAGE_UNCHANGED));
	}

	cv::Mat meanDepth = calculateMeanDepthFrom(depthImages);

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
		cv::imshow("depth sclaed",displayDepthImage(meanDepth));
		key = cv::waitKey(1);
		if (key == 27){
			break;
		}

	}


	return 0;
}

cv::Mat calculateMeanDepthFrom(std::vector<cv::Mat> depthImages){
	cv::Size imageSize = depthImages.back().size();
	cv::Mat meanDepth = cv::Mat::zeros(imageSize.height, imageSize.width, CV_64F);

	for (int row = 0; row < imageSize.height; row++){
		for (int col = 0; col < imageSize.width; col++){
			std::vector<uint16_t> pixelValue;
			for (cv::Mat depthImage : depthImages){
				pixelValue.push_back(depthImage.at<uint16_t>(row, col));
			}
			meanDepth.at<double>(row, col) = (std::accumulate(pixelValue.begin(), pixelValue.end(), 0.0) / depthImages.size());
		}
	}

	return meanDepth;
}

cv::Mat displayDepthImage(cv::Mat depthImage){
	double min;
	double max;
	cv::minMaxIdx(depthImage, &min, &max);
	cv::Mat adjMap;
	cv::convertScaleAbs(depthImage, adjMap, 255 / max);
	cv::applyColorMap(adjMap, adjMap, cv::COLORMAP_JET);
	return adjMap;
}
