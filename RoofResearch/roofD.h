#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <opencv2/opencv.hpp>
#include <vector>

class RoofD {

protected:
	RoofD() {}

public:
	static cv::Mat generateRoof(int width, int height, int roofWidth_main, double roofAspect_main, double roofWidthRatio_sub, double roofAspect_sub, int selected_roof_type, double ridgeRatio_main, double ridgeRatio_sub, const cv::Scalar& bg_color, const cv::Scalar& fg_color);
	static int generateRoofImages(std::string roofImagesPath, int imageNum, int start_index, int type, int width, int height, std::pair<int, int> roofWidth_main, std::pair<double, double> roofAspect_main, std::pair<double, double> roofWidthRatio_sub, std::pair<double, double> roofAspect_sub, int selected_roof_type, std::pair<double, double> ridgeRatio_main, std::pair<double, double> ridgeRatio_sub, const cv::Scalar& bg_color, const cv::Scalar& fg_color);

};