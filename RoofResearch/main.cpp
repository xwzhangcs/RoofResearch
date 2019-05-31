#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "roofTypes.h"
#include "roofA.h"
#include "roofB.h"

int main(int argc, char** argv)
{
	cv::Mat result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_flat_test.png", result);
	result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_gable_test.png", result);
	result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, RoofTypes::HIP, 0.6, 0.7, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_hip_test.png", result);
	//RoofA::generateRoofImages("../data", 2, 224, 224, std::make_pair(100, 200), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	system("pause");
	return 0;
}