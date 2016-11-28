#include "Application\main.h"

int main(int argc, char* argv[])
{
	std::vector<cv::Mat> depthImages;
	cv::Mat meanDepthImage;

	cv::Mat img = cv::imread(IMAGES_DIRECTORY + "video.jpg");
	cv::Mat img_depth = cv::imread(IMAGES_DIRECTORY + "depth.png", CV_LOAD_IMAGE_UNCHANGED);

	depthImages = ImageUtils::createImageVectorFromContentOf(INIT_DEPTH_IMAGES_DIRECTORY);
	meanDepthImage = ImageUtils::calculateMeanDepthFrom(depthImages);

	/* Loop until the user closes the window */
	while (true)
	{
		int key = 0;
		cv::imshow("img", img);
		cv::imshow("depth", ImageUtils::scaleDepthImageForDisplay(img_depth));
		cv::imshow("mean depth", ImageUtils::scaleDepthImageForDisplay(meanDepthImage));
		key = cv::waitKey(1);
		if (key == ESCAPE){
			break;
		}
	}
	return 0;
}
