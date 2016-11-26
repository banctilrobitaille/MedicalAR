#include "Application\main.h"

int main(int argc, char* argv[])
{
	int numberOfDepthImages = 102;
	std::vector<cv::Mat> depthImages;
	cv::Mat meanDepth;

	cv::Mat img = cv::imread(IMAGES_PATH + "video.jpg");
	cv::Mat img_depth = cv::imread(IMAGES_PATH + "depth.png", CV_LOAD_IMAGE_UNCHANGED);

	cv::VideoCapture cap;
	cap.open(0);
	cv::Mat img_bgr;

	for (int i = 0; i < numberOfDepthImages; i++){
		depthImages.push_back(cv::imread(INIT_DEPTH_IMAGES_PATH + DEPTH + std::to_string(i) + PNG_EXTENSION, CV_LOAD_IMAGE_UNCHANGED));
	}

	meanDepth = ImageUtils::calculateMeanDepthFrom(depthImages);

	/* Loop until the user closes the window */
	while (true)
	{
		int key = 0;
		cap.read(img_bgr);
		cv::flip(img_bgr, img_bgr, 1);
		if (img_bgr.empty()){
			std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
			cap.open(0);
			continue;
		}
		cv::imshow("img_live", img_bgr);
		cv::imshow("img", img);
		cv::imshow("depth", ImageUtils::scaleDepthImageForDisplay(img_depth));
		cv::imshow("depth sclaed", ImageUtils::scaleDepthImageForDisplay(meanDepth));
		key = cv::waitKey(1);
		if (key == 27){
			break;
		}
	}
	return 0;
}
