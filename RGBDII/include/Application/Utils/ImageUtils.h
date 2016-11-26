#ifndef __IMAGEUTILS_H_
#define __IMAGEUTILS_H_

#include <opencv2/imgproc.hpp>
#include <numeric>
#include <cstdint>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

class ImageUtils;

class ImageUtils 
{
public:
	static cv::Mat calculateMeanDepthFrom(std::vector<cv::Mat> depthImages);
	static cv::Mat scaleDepthImageForDisplay(cv::Mat depthImage);
};

#endif