#include "Application\Utils\ImageUtils.h"

cv::Mat ImageUtils::calculateMeanDepthFrom(std::vector<cv::Mat> depthImages){
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

cv::Mat ImageUtils::scaleDepthImageForDisplay(cv::Mat depthImage){
	double min;
	double max;
	cv::minMaxIdx(depthImage, &min, &max);
	cv::Mat adjMap;
	cv::convertScaleAbs(depthImage, adjMap, 255 / max);
	cv::applyColorMap(adjMap, adjMap, cv::COLORMAP_JET);
	return adjMap;
}

std::vector<cv::Mat> ImageUtils::createImageVectorFromContentOf(const char* directoryPath){
	DIR *directory;
	struct dirent *file;
	std::vector<cv::Mat> imageVector;

	if ((directory = opendir(directoryPath)) != NULL) {
		while ((file = readdir(directory)) != NULL) {
			if (ImageUtils::isImageFile(file->d_name)){
				imageVector.push_back(cv::imread(std::string(directoryPath) + file->d_name, CV_LOAD_IMAGE_UNCHANGED));
			}
		}
		closedir(directory);
	}
	return imageVector;
}

bool ImageUtils::isImageFile(std::string fileName){
	return fileName.find(JPG_EXTENSION) != std::string::npos || fileName.find(PNG_EXTENSION) != std::string::npos;
}