#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "roofTypes.h"
#include "roofA.h"
int main(int argc, char** argv)
{
	/*cv::Mat result = RoofA::generateRoof(224, 224, 100, 0.5, RoofTypes::FLAT, 0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofA_flat_test.png", result);
	result = RoofA::generateRoof(224, 224, 100, 0.5, RoofTypes::GABLE, 0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofA_gable_test.png", result);
	result = RoofA::generateRoof(224, 224, 100, 0.5, RoofTypes::HIP, 0.6, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofA_hip_test.png", result);*/
	RoofA::generateRoofImages("../data", 2, 224, 224, std::make_pair(100, 200), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	system("pause");
	return 0;
}