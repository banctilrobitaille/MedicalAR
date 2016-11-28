#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Application\Utils\ImageUtils.h"
#include "Application\main.h"

const std::string DEPTH = "depth";
const std::string VIDEO_IMAGE_NAME = "video.jpg";
const std::string XRAY_IMAGE_NAME = "Xray.png";
const char* IMAGES_DIRECTORY = "..\\newimages\\";
const char* INIT_DEPTH_IMAGES_DIRECTORY = "..\\init\\depth\\";
const char* VIDEO_IMAGES_DEPTH_DIRECTORY = "..\\newimages\\depth\\";
const char* VIDEO_IMAGES_DIRECTORY = "..\\newimages\\video\\";
const char* MASK_IMAGES_DIRECTORY = "..\\newimages\\mask\\";
const int BEST_QUALITY = 0;
const int ESCAPE = 27;

#endif