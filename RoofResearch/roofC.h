#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <vector>

class RoofC {

protected:
	RoofC() {}

public:
	static cv::Mat generateRoof(int width, int height, int start_displacement, int roofWidth_v1, double roofAspect_v1, int roofWidth_v2, double roofAspect_v2, double rotate, int selected_roof_type, double ridgeRatio_v1, double ridgeRatio_v2, const cv::Scalar& bg_color, const cv::Scalar& fg_color);
	static void generateRoofImages(std::string roofImagesPath, int imageNum, int width, int height, int start_displacement, std::pair<int, int> roofWidth_v1, std::pair<double, double> roofAspect_v1, std::pair<double, double> roofWidth_v2, std::pair<double, double> roofAspect_v2, std::pair<double, double> rotate_range, int selected_roof_type, std::pair<double, double> ridgeRatio_v1, std::pair<double, double> ridgeRatio_v2, const cv::Scalar& bg_color, const cv::Scalar& fg_color);

};