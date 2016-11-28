#ifndef __IMAGEUTILS_H_
#define __IMAGEUTILS_H_

#include <opencv2/imgproc.hpp>
#include <numeric>
#include <cstdint>
#include <string>
#include <dirent.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

const std::string JPG_EXTENSION = ".jpg";
const std::string PNG_EXTENSION = ".png";

class ImageUtils;

class ImageUtils 
{
public:
	static cv::Mat calculateMeanDepthFrom(std::vector<cv::Mat> depthImages);
	static cv::Mat scaleDepthImageForDisplay(cv::Mat depthImage);
	static std::vector<cv::Mat> createImageVectorFromContentOf(const char* directoryPath);
	static bool isImageFile(std::string fileName);
};

#endif