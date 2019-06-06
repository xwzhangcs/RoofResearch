#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "roofTypes.h"
#include "roofA.h"
#include "roofB.h"
#include "roofC.h"
#include "roofD.h"
#include "roofE.h"
#include "roofF.h"
#include "RoofUtils.h"

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
	/*cv::Mat result = RoofD::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofD_flat_test.png", result);
	result = RoofD::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofD_gable_test.png", result);*/

	/*cv::Mat result = RoofE::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, 0.3, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofE_flat_test.png", result);
	result = RoofE::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, 0.3, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofE_gable_test.png", result);
	result = RoofE::generateRoof(224, 224, 100, 0.4, 0.4, 2.0, 0.0, RoofTypes::HIP, 0.6, 0.6, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofE_hip_test.png", result);*/
	/*cv::Mat result = RoofF::generateRoof(224, 224, 100, 0.3, 0.4, 3.0, RoofTypes::FLAT, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofF_flat_test.png", result);
	result = RoofF::generateRoof(224, 224, 100, 0.3, 0.4, 3.0, RoofTypes::GABLE, 0, 0.0, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofF_gable_test.png", result);
	result = RoofF::generateRoof(224, 224, 100, 0.3, 0.4, 3.0, RoofTypes::HIP, 0.6, 0.7, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	cv::imwrite("../data/roofF_hip_test.png", result);*/
	
	// generate training images
	int start_index = 0;
	start_index = RoofA::generateRoofImages("../data/train", 20000, start_index, 0, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/train", 20000, start_index, 1, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/train", 20000, start_index, 2, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/train", 20000, start_index, 3, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/train", 20000, start_index, 4, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/train", 20000, start_index, 5, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/train", 20000, start_index, 6, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/train", 20000, start_index, 7, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	
	// val
	start_index = 0;
	start_index = RoofA::generateRoofImages("../data/val", 4000, start_index, 0, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/val", 4000, start_index, 1, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/val", 4000, start_index, 2, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/val", 4000, start_index, 3, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/val", 4000, start_index, 4, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/val", 4000, start_index, 5, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/val", 4000, start_index, 6, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/val", 4000, start_index, 7, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

	// test
	//start_index = 0;
	start_index = RoofA::generateRoofImages("../data/test", 100, start_index, 0, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/test", 100, start_index, 1, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofA::generateRoofImages("../data/test", 100, start_index, 2, 224, 224, std::make_pair(80, 200), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/test", 100, start_index, 3, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/test", 100, start_index, 4, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofB::generateRoofImages("../data/test", 100, start_index, 5, 224, 224, std::make_pair(60, 150), std::make_pair(0.3, 0.7), std::make_pair(0.3, 0.5), std::make_pair(0.8, 1.3), std::make_pair(0.3, 0.7), RoofTypes::HIP, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/test", 100, start_index, 6, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::FLAT, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));
	start_index = RoofC::generateRoofImages("../data/test", 100, start_index, 7, 224, 224, std::make_pair(10, 50), std::make_pair(50, 100), std::make_pair(0.3, 0.7), std::make_pair(60, 100), std::make_pair(0.5, 0.8), std::make_pair(30, 50), RoofTypes::GABLE, std::make_pair(0.5, 0.8), std::make_pair(0.5, 0.8), cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255));

	system("pause");
	
	return 0;
	// generate input images
	{
		std::string src_img_file = "../data/building_cluster_0214__hist_seg.png";
		std::vector<cv::Scalar> colorList;
		colorList.push_back(cv::Scalar(139, 0, 0));
		colorList.push_back(cv::Scalar(255, 0, 0));
		colorList.push_back(cv::Scalar(255, 255, 0));
		colorList.push_back(cv::Scalar(0, 100, 0));
		colorList.push_back(cv::Scalar(0, 255, 0));
		colorList.push_back(cv::Scalar(0, 0, 139));
		colorList.push_back(cv::Scalar(0, 0, 255));
		colorList.push_back(cv::Scalar(0, 255, 255));
		std::string output_img_file = "../data/building_cluster_0214__edge_map.png";
		roof_utils::findContours_from_colorList(src_img_file, colorList, output_img_file);
	}
	system("pause");
	return 0;
}