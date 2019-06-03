#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "roofTypes.h"
#include "roofA.h"
#include "roofB.h"
#include "roofC.h"
#include "roofD.h"

int main(int argc, char** argv)
{
	/*cv::Mat result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, 0.3, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_flat_test.png", result);
	result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, 0.6, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_gable_test.png", result);
	result = RoofB::generateRoof(224, 224, 100, 0.5, 0.4, 1.2, 0.3, RoofTypes::HIP, 0.6, 0.7, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofB_hip_test.png", result);
	RoofB::generateRoofImages("../data", 5, 224, 224, std::make_pair(100, 200), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.4), RoofTypes::HIP, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));*/
	
	/*cv::Mat result = RoofC::generateRoof(224, 224, 10, 100, 0.5, 100, 0.5, -30, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofC_flat_test.png", result);
	result = RoofC::generateRoof(224, 224, 10, 100, 0.5, 100, 0.5, -30, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofC_gable_test.png", result);
	result = RoofC::generateRoof(224, 224, 10, 100, 0.5, 100, 0.5, -30, RoofTypes::HIP, 0.7, 0.7, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofC_hip_test.png", result);
	RoofC::generateRoofImages("../data", 2, 224, 224, 10, std::make_pair(80, 100), std::make_pair(0.3, 0.7), std::make_pair(80, 100), std::make_pair(0.3, 0.5), std::make_pair(-35, -25), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	system("pause");*/
	cv::Mat result = RoofD::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofD_flat_test.png", result);
	result = RoofD::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofD_gable_test.png", result);
	system("pause");
	return 0;
}