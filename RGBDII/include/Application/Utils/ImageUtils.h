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
const int WHITE = 255;
const int BLACK = 0;
class ImageUtils;

class ImageUtils 
{
public:
	static cv::Mat calculateMeanDepthFrom(std::vector<cv::Mat> depthImages);
	static cv::Mat scaleDepthImageForDisplay(cv::Mat depthImage);
	static std::vector<cv::Mat> createImageVectorFromContentOf(const char* directoryPath);
	static std::vector<std::string> getImageFilesNameFrom(const char* directoryPath);
	static cv::Mat createMaskFromImageWithMargin(cv::Mat image, cv::Mat depthImage, cv::Mat meanDepth,int margin);
	static bool isImageFile(std::string fileName);
};

#endif