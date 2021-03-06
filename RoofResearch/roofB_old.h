#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <vector>

class RoofB {

protected:
	RoofB() {}

public:
	static cv::Mat generateRoof(int width, int height, int roofWidth, double roofAspect, double l_width_ratio, double l_aspect, int selected_roof_type, double ridgeRatio, double l_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color);
	static void generateRoofImages(std::string roofImagesPath, int imageNum, int width, int height, std::pair<int, int> roofWidth, std::pair<double, double> roofAspect, std::pair<double, double> l_width_ratio, std::pair<double, double> l_aspect, int selected_roof_type, std::pair<double, double> ridgeRatio, std::pair<double, double> l_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color);

};