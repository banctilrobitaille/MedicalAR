#include "Application\main.h"

int main(int argc, char* argv[])
{
	int margin = 20;
	double alpha = 0.5;
	std::vector<int> compressionParameters;
	std::vector<cv::Mat> depthImages;
	cv::Mat meanDepthImage;
	cv::Mat xrayImage = cv::imread(IMAGES_DIRECTORY + XRAY_IMAGE_NAME, CV_LOAD_IMAGE_GRAYSCALE);
	
	depthImages = ImageUtils::createImageVectorFromContentOf(INIT_DEPTH_IMAGES_DIRECTORY);
	//meanDepthImage = ImageUtils::calculateMeanDepthFrom(depthImages);
	
	compressionParameters.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compressionParameters.push_back(BEST_QUALITY);
	//cv::imwrite(std::string(IMAGES_DIRECTORY) + "meanDepth.png", meanDepthImage, compressionParameters);

	std::vector<std::string> videoImageFiles = ImageUtils::getImageFilesNameFrom(VIDEO_IMAGES_DIRECTORY);
	std::vector<std::string> videoDepthImageFiles = ImageUtils::getImageFilesNameFrom(VIDEO_IMAGES_DEPTH_DIRECTORY);

	/*for (int i = 0; i < videoImageFiles.size();i++){
		cv::Mat associatedDeptdDepthImage = cv::imread(videoDepthImageFiles[i], CV_LOAD_IMAGE_UNCHANGED);
		cv::Mat image = cv::imread(videoImageFiles[i]);
		cv::Mat mask = ImageUtils::createMaskFromImageWithMargin(image, associatedDeptdDepthImage, meanDepthImage, margin);
		cv::imwrite(std::string(MASK_IMAGES_DIRECTORY) + "mask" + std::to_string(i) + PNG_EXTENSION, mask, compressionParameters);
	}*/

	std::vector<std::string> maskImages = ImageUtils::getImageFilesNameFrom(MASK_IMAGES_DIRECTORY);

	for (int i = 0; i < videoImageFiles.size(); i++){
		cv::Mat mask = cv::imread(std::string(MASK_IMAGES_DIRECTORY) + "mask" + std::to_string(i) + PNG_EXTENSION, CV_LOAD_IMAGE_GRAYSCALE);
		cv::Mat videoImage = cv::imread(videoImageFiles[i], CV_LOAD_IMAGE_UNCHANGED);
		cv::Size imageSize = videoImage.size();
		cv::Mat overlay = cv::Mat::zeros(imageSize.height, imageSize.width, CV_64FC3);
		int channel = xrayImage.channels();
		for (int row = 0; row < imageSize.height; row++){
			for (int col = 0; col < imageSize.width; col++){
				if (xrayImage.at<uint8_t>(row, col) == BLACK || mask.at<uint8_t>(row, col) == WHITE){
					overlay.at<cv::Vec3d>(row, col) = videoImage.at<cv::Vec3b>(row, col);
				}else {
					overlay.at<cv::Vec3d>(row, col)[0] = (alpha * videoImage.at<cv::Vec3b>(row, col)[0] + (1 - alpha)*xrayImage.at<uint8_t>(row, col));
					overlay.at<cv::Vec3d>(row, col)[1] = (alpha * videoImage.at<cv::Vec3b>(row, col)[1] + (1 - alpha)*xrayImage.at<uint8_t>(row, col));
					overlay.at<cv::Vec3d>(row, col)[2] = (alpha * videoImage.at<cv::Vec3b>(row, col)[2] + (1 - alpha)*xrayImage.at<uint8_t>(row, col));
				}
			}
		}
		cv::imwrite(std::string(OVERLAY_IMAGES_DIRECTORY) + "overlay" + std::to_string(i) + PNG_EXTENSION, overlay, compressionParameters);
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
