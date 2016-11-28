#include "Application\main.h"

int main(int argc, char* argv[])
{
	int margin = 20;
	std::vector<int> compressionParameters;
	std::vector<cv::Mat> depthImages;
	cv::Mat meanDepthImage;
	cv::Mat xrayImage;
	
	xrayImage = cv::imread(IMAGES_DIRECTORY + XRAY_IMAGE_NAME);
	depthImages = ImageUtils::createImageVectorFromContentOf(INIT_DEPTH_IMAGES_DIRECTORY);
	meanDepthImage = ImageUtils::calculateMeanDepthFrom(depthImages);
	
	compressionParameters.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compressionParameters.push_back(BEST_QUALITY);
	cv::imwrite(std::string(IMAGES_DIRECTORY) + "meanDepth.png", meanDepthImage, compressionParameters);

	std::vector<std::string> videoImageFiles = ImageUtils::getImageFilesNameFrom(VIDEO_IMAGES_DIRECTORY);
	std::vector<std::string> videoDepthImageFiles = ImageUtils::getImageFilesNameFrom(VIDEO_IMAGES_DEPTH_DIRECTORY);

	for (int i = 0; i < videoImageFiles.size();i++){
		cv::Mat associatedDeptdDepthImage = cv::imread(videoDepthImageFiles[i], CV_LOAD_IMAGE_UNCHANGED);
		cv::Mat image = cv::imread(videoImageFiles[i]);
		cv::Mat mask = ImageUtils::createMaskFromImageWithMargin(image, associatedDeptdDepthImage, meanDepthImage, margin);
		cv::imwrite(std::string(MASK_IMAGES_DIRECTORY) + "mask" + std::to_string(i) + PNG_EXTENSION, mask, compressionParameters);
	}

	/* Loop until the user closes the window */
	while (true)
	{
		int key = 0;
		cv::imshow("mean depth", ImageUtils::scaleDepthImageForDisplay(meanDepthImage));
		key = cv::waitKey(1);
		if (key == ESCAPE){
			break;
		}
	}
	return 0;
}
