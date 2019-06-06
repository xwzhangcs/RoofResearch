#include "roofC.h"
#include "Utils.h"
#include "roofTypes.h"
const float M_PI = 3.1415926535;

cv::Mat RoofC::generateRoof(int width, int height, int start_displacement, int roofWidth_v1, double roofAspect_v1, int roofWidth_v2, double roofAspect_v2, double rotate, int selected_roof_type, double ridgeRatio_v1, double ridgeRatio_v2, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	/*std::cout << "width is " << width << std::endl;
	std::cout << "height is " << height << std::endl;
	std::cout << "roofType is " << selected_roof_type << std::endl;
	std::cout << "roofWidth is " << roofWidth << std::endl;
	std::cout << "roofAspect is " << roofAspect << std::endl;*/
	cv::Mat result(height, width, CV_8UC3, bg_color);
	int imageRoofWidth_v1 = roofWidth_v1;
	double imageRoofAspect_v1 = roofAspect_v1;
	int imageRoofHeight_v1 = imageRoofWidth_v1 * imageRoofAspect_v1;
	int imageRoofWidth_v2 = roofWidth_v2;
	double imageRoofAspect_v2 = roofAspect_v2;
	int imageRoofHeight_v2 = imageRoofWidth_v2 * imageRoofAspect_v2;
	if (rotate != 0){
		imageRoofHeight_v2 = imageRoofHeight_v1;
		imageRoofWidth_v2 = imageRoofWidth_v1;
	}

	int thickness = 2;
	if (selected_roof_type == RoofTypes::FLAT){
		// add the first part
		int upper_left_w_v1 = start_displacement;
		int upper_left_h_v1 = (height - imageRoofHeight_v1) * 0.5;
		int bottom_right_w_v1 = upper_left_w_v1 + imageRoofWidth_v1;
		int bottom_right_h_v1 = upper_left_h_v1 + imageRoofHeight_v1;
		// add three sides
		cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
		cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
		// add the second part
		int upper_left_w_v2 = bottom_right_w_v1;
		int upper_left_h_v2 = (height - imageRoofHeight_v2) * 0.5;
		int bottom_right_w_v2 = upper_left_w_v2 + imageRoofWidth_v2;
		int bottom_right_h_v2 = upper_left_h_v2 + imageRoofHeight_v2;
		cv::Point2f upper_left_v2(upper_left_w_v2, upper_left_h_v2);
		cv::Point2f bottom_right_new_v2 = utils::RotatePoint(upper_left_v2, cv::Point2f(bottom_right_w_v2, bottom_right_h_v2), (rotate)* M_PI / 180.0);
		cv::Point2f center((upper_left_v2.x + bottom_right_new_v2.x) * 0.5, (upper_left_v2.y + bottom_right_new_v2.y) * 0.5);
		cv::RotatedRect rRect = cv::RotatedRect(center, cv::Size2f(imageRoofWidth_v2, imageRoofHeight_v2), rotate);
		cv::Point2f vertices[4];
		rRect.points(vertices);
		// add three sides
		cv::line(result, vertices[3], vertices[2], fg_color, thickness);
		cv::line(result, vertices[2], vertices[1], fg_color, thickness);
		// compute the intersection
		cv::Point2f int_pt;
		double tab, tcd;
		cv::Point2f left_v1(upper_left_w_v1, bottom_right_h_v1);
		cv::Point2f right_v1(bottom_right_w_v1, bottom_right_h_v1);
		cv::Point2f left_v2 = vertices[0];
		cv::Point2f right_v2 = vertices[3];

		if (utils::lineLineIntersection(left_v1, right_v1, left_v2, right_v2, &tab, &tcd, false, int_pt)){
			// add the common edge
			//cv::line(result, int_pt, cv::Point(upper_left_w_v2, upper_left_h_v2), fg_color, thickness);
			cv::line(result, int_pt, cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, int_pt, vertices[3], fg_color, thickness);
		}
		else{
			cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
			cv::line(result, vertices[1], vertices[0], fg_color, thickness);
			cv::line(result, vertices[0], vertices[3], fg_color, thickness);
			// remove the common edge
			cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1 > bottom_right_h_v2 ? bottom_right_h_v2 - thickness : bottom_right_h_v1 - thickness),
				cv::Point(bottom_right_w_v1, upper_left_h_v1 > upper_left_h_v2 ? upper_left_h_v1 + thickness : upper_left_h_v2 + thickness), bg_color, thickness);
		}

	}
	else if (selected_roof_type == RoofTypes::GABLE){
		// add the first part
		int upper_left_w_v1 = start_displacement;
		int upper_left_h_v1 = (height - imageRoofHeight_v1) * 0.5;
		int bottom_right_w_v1 = upper_left_w_v1 + imageRoofWidth_v1;
		int bottom_right_h_v1 = upper_left_h_v1 + imageRoofHeight_v1;
		// add three sides
		cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
		cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
		// add the second part
		int upper_left_w_v2 = bottom_right_w_v1;
		int upper_left_h_v2 = (height - imageRoofHeight_v2) * 0.5;
		int bottom_right_w_v2 = upper_left_w_v2 + imageRoofWidth_v2;
		int bottom_right_h_v2 = upper_left_h_v2 + imageRoofHeight_v2;
		cv::Point2f upper_left_v2(upper_left_w_v2, upper_left_h_v2);
		cv::Point2f bottom_right_new_v2 = utils::RotatePoint(upper_left_v2, cv::Point2f(bottom_right_w_v2, bottom_right_h_v2), (rotate)* M_PI / 180.0);
		cv::Point2f center((upper_left_v2.x + bottom_right_new_v2.x) * 0.5, (upper_left_v2.y + bottom_right_new_v2.y) * 0.5);
		cv::RotatedRect rRect = cv::RotatedRect(center, cv::Size2f(imageRoofWidth_v2, imageRoofHeight_v2), rotate);
		cv::Point2f vertices[4];
		rRect.points(vertices);
		// add three sides
		cv::line(result, vertices[3], vertices[2], fg_color, thickness);
		cv::line(result, vertices[2], vertices[1], fg_color, thickness);
		// compute the intersection
		cv::Point2f int_pt;
		double tab, tcd;
		cv::Point2f left_v1(upper_left_w_v1, bottom_right_h_v1);
		cv::Point2f right_v1(bottom_right_w_v1, bottom_right_h_v1);
		cv::Point2f left_v2 = vertices[0];
		cv::Point2f right_v2 = vertices[3];

		if (utils::lineLineIntersection(left_v1, right_v1, left_v2, right_v2, &tab, &tcd, false, int_pt)){
			// add the common edge
			cv::line(result, int_pt, cv::Point(upper_left_w_v2, upper_left_h_v2), fg_color, thickness);
			cv::line(result, int_pt, cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, int_pt, vertices[3], fg_color, thickness);
			// add ridge
			cv::line(result, (int_pt + vertices[1]) / 2, (vertices[2] + vertices[3]) / 2, fg_color, thickness);
			cv::line(result, (int_pt + vertices[1]) / 2, cv::Point(upper_left_w_v1, (upper_left_h_v1 + bottom_right_h_v1) * 0.5), fg_color, thickness);
		}
		else{
			cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
			cv::line(result, vertices[1], vertices[0], fg_color, thickness);
			cv::line(result, vertices[0], vertices[3], fg_color, thickness);
			cv::line(result, (vertices[0] + vertices[1]) / 2, cv::Point(upper_left_w_v1, (upper_left_h_v1 + bottom_right_h_v1) * 0.5), fg_color, thickness);
			cv::line(result, (vertices[0] + vertices[1]) / 2, (vertices[2] + vertices[3]) / 2, fg_color, thickness);

		}
	}
	else if (selected_roof_type == RoofTypes::HIP){

	}
	else{
		// do nothing
	}
	return result;
}

int RoofC::generateRoofImages(std::string roofImagesPath, int imageNum, int start_index, int type, int width, int height, std::pair<int, int> displacement_range, std::pair<int, int> roofWidth_v1, std::pair<double, double> roofAspect_v1, std::pair<double, double> roofWidth_v2, std::pair<double, double> roofAspect_v2, std::pair<double, double> rotate_range, int selected_roof_type, std::pair<double, double> ridgeRatio_v1, std::pair<double, double> ridgeRatio_v2, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	std::ofstream out_param(roofImagesPath + "/parameters.txt", std::ios::app);
	int index = start_index;
	for (int l = 0; l < imageNum; l++){
		cv::Mat result(height, width, CV_8UC3, bg_color);
		int imageRoofWidth_v1 = utils::genRand(roofWidth_v1.first, roofWidth_v1.second + 1);
		double imageRoofAspect_v1 = utils::genRand(roofAspect_v1.first, roofAspect_v1.second);
		int imageRoofHeight_v1 = imageRoofWidth_v1 * imageRoofAspect_v1;
		int imageRoofWidth_v2 = utils::genRand(roofWidth_v2.first, roofWidth_v2.second + 1);
		double imageRoofAspect_v2 = utils::genRand(roofAspect_v2.first, roofAspect_v2.second);
		int imageRoofHeight_v2 = imageRoofWidth_v2 * imageRoofAspect_v2;
		double rotate = utils::genRand(rotate_range.first, rotate_range.second);
		int start_displacement = utils::genRand(displacement_range.first, displacement_range.second + 1);
		if (imageRoofWidth_v1 + imageRoofWidth_v2 + start_displacement > width){
			std::cout << "Too wide" << std::endl;
			continue;
		}
		if (rotate != 0){
			imageRoofWidth_v2 = imageRoofWidth_v1;
			imageRoofHeight_v2 = imageRoofHeight_v1;
		}
		int thickness = 2;
		if (selected_roof_type == RoofTypes::FLAT){
			// add the first part
			int upper_left_w_v1 = start_displacement;
			int upper_left_h_v1 = (height - imageRoofHeight_v1) * 0.5;
			int bottom_right_w_v1 = upper_left_w_v1 + imageRoofWidth_v1;
			int bottom_right_h_v1 = upper_left_h_v1 + imageRoofHeight_v1;
			// add three sides
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
			// add the second part
			int upper_left_w_v2 = bottom_right_w_v1;
			int upper_left_h_v2 = (height - imageRoofHeight_v2) * 0.5;
			int bottom_right_w_v2 = upper_left_w_v2 + imageRoofWidth_v2;
			int bottom_right_h_v2 = upper_left_h_v2 + imageRoofHeight_v2;
			cv::Point2f upper_left_v2(upper_left_w_v2, upper_left_h_v2);
			cv::Point2f bottom_right_new_v2 = utils::RotatePoint(upper_left_v2, cv::Point2f(bottom_right_w_v2, bottom_right_h_v2), (rotate)* M_PI / 180.0);
			cv::Point2f center((upper_left_v2.x + bottom_right_new_v2.x) * 0.5, (upper_left_v2.y + bottom_right_new_v2.y) * 0.5);
			cv::RotatedRect rRect = cv::RotatedRect(center, cv::Size2f(imageRoofWidth_v2, imageRoofHeight_v2), rotate);
			cv::Point2f vertices[4];
			rRect.points(vertices);
			// add three sides
			cv::line(result, vertices[3], vertices[2], fg_color, thickness);
			cv::line(result, vertices[2], vertices[1], fg_color, thickness);
			// compute the intersection
			cv::Point2f int_pt;
			double tab, tcd;
			cv::Point2f left_v1(upper_left_w_v1, bottom_right_h_v1);
			cv::Point2f right_v1(bottom_right_w_v1, bottom_right_h_v1);
			cv::Point2f left_v2 = vertices[0];
			cv::Point2f right_v2 = vertices[3];

			if (utils::lineLineIntersection(left_v1, right_v1, left_v2, right_v2, &tab, &tcd, false, int_pt)){
				// add the common edge
				//cv::line(result, int_pt, cv::Point(upper_left_w_v2, upper_left_h_v2), fg_color, thickness);
				cv::line(result, int_pt, cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, int_pt, vertices[3], fg_color, thickness);
			}
			else{
				cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
				cv::line(result, vertices[1], vertices[0], fg_color, thickness);
				cv::line(result, vertices[0], vertices[3], fg_color, thickness);
				// remove the common edge
				cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1 > bottom_right_h_v2 ? bottom_right_h_v2 - thickness : bottom_right_h_v1 - thickness),
					cv::Point(bottom_right_w_v1, upper_left_h_v1 > upper_left_h_v2 ? upper_left_h_v1 + thickness : upper_left_h_v2 + thickness), bg_color, thickness);
			}
		}
		else if (selected_roof_type == RoofTypes::GABLE){
			// add the first part
			int upper_left_w_v1 = start_displacement;
			int upper_left_h_v1 = (height - imageRoofHeight_v1) * 0.5;
			int bottom_right_w_v1 = upper_left_w_v1 + imageRoofWidth_v1;
			int bottom_right_h_v1 = upper_left_h_v1 + imageRoofHeight_v1;
			// add three sides
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
			// add the second part
			int upper_left_w_v2 = bottom_right_w_v1;
			int upper_left_h_v2 = (height - imageRoofHeight_v2) * 0.5;
			int bottom_right_w_v2 = upper_left_w_v2 + imageRoofWidth_v2;
			int bottom_right_h_v2 = upper_left_h_v2 + imageRoofHeight_v2;
			cv::Point2f upper_left_v2(upper_left_w_v2, upper_left_h_v2);
			cv::Point2f bottom_right_new_v2 = utils::RotatePoint(upper_left_v2, cv::Point2f(bottom_right_w_v2, bottom_right_h_v2), (rotate)* M_PI / 180.0);
			cv::Point2f center((upper_left_v2.x + bottom_right_new_v2.x) * 0.5, (upper_left_v2.y + bottom_right_new_v2.y) * 0.5);
			cv::RotatedRect rRect = cv::RotatedRect(center, cv::Size2f(imageRoofWidth_v2, imageRoofHeight_v2), rotate);
			cv::Point2f vertices[4];
			rRect.points(vertices);
			// add three sides
			cv::line(result, vertices[3], vertices[2], fg_color, thickness);
			cv::line(result, vertices[2], vertices[1], fg_color, thickness);
			// compute the intersection
			cv::Point2f int_pt;
			double tab, tcd;
			cv::Point2f left_v1(upper_left_w_v1, bottom_right_h_v1);
			cv::Point2f right_v1(bottom_right_w_v1, bottom_right_h_v1);
			cv::Point2f left_v2 = vertices[0];
			cv::Point2f right_v2 = vertices[3];

			if (utils::lineLineIntersection(left_v1, right_v1, left_v2, right_v2, &tab, &tcd, false, int_pt)){
				// add the common edge
				cv::line(result, int_pt, cv::Point(upper_left_w_v2, upper_left_h_v2), fg_color, thickness);
				cv::line(result, int_pt, cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, int_pt, vertices[3], fg_color, thickness);
				// add ridge
				cv::line(result, (int_pt + vertices[1]) / 2, (vertices[2] + vertices[3]) / 2, fg_color, thickness);
				cv::line(result, (int_pt + vertices[1]) / 2, cv::Point(upper_left_w_v1, (upper_left_h_v1 + bottom_right_h_v1) * 0.5), fg_color, thickness);
			}
			else{
				cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
				cv::line(result, vertices[1], vertices[0], fg_color, thickness);
				cv::line(result, vertices[0], vertices[3], fg_color, thickness);
				cv::line(result, (vertices[0] + vertices[1]) / 2, cv::Point(upper_left_w_v1, (upper_left_h_v1 + bottom_right_h_v1) * 0.5), fg_color, thickness);
				cv::line(result, (vertices[0] + vertices[1]) / 2, (vertices[2] + vertices[3]) / 2, fg_color, thickness);
				
			}
		}
		else if (selected_roof_type == RoofTypes::HIP){
			// add the first part
			int upper_left_w_v1 = start_displacement;
			int upper_left_h_v1 = (height - imageRoofHeight_v1) * 0.5;
			int bottom_right_w_v1 = upper_left_w_v1 + imageRoofWidth_v1;
			int bottom_right_h_v1 = upper_left_h_v1 + imageRoofHeight_v1;
			// add three sides
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
			cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
			// add the second part
			int upper_left_w_v2 = bottom_right_w_v1;
			int upper_left_h_v2 = (height - imageRoofHeight_v2) * 0.5;
			int bottom_right_w_v2 = upper_left_w_v2 + imageRoofWidth_v2;
			int bottom_right_h_v2 = upper_left_h_v2 + imageRoofHeight_v2;
			cv::Point2f upper_left_v2(upper_left_w_v2, upper_left_h_v2);
			cv::Point2f bottom_right_new_v2 = utils::RotatePoint(upper_left_v2, cv::Point2f(bottom_right_w_v2, bottom_right_h_v2), (rotate)* M_PI / 180.0);
			cv::Point2f center((upper_left_v2.x + bottom_right_new_v2.x) * 0.5, (upper_left_v2.y + bottom_right_new_v2.y) * 0.5);
			cv::RotatedRect rRect = cv::RotatedRect(center, cv::Size2f(imageRoofWidth_v2, imageRoofHeight_v2), rotate);
			cv::Point2f vertices[4];
			rRect.points(vertices);
			// add three sides
			cv::line(result, vertices[3], vertices[2], fg_color, thickness);
			cv::line(result, vertices[2], vertices[1], fg_color, thickness);
			// compute the intersection
			cv::Point2f int_pt;
			double tab, tcd;
			cv::Point2f left_v1(upper_left_w_v1, bottom_right_h_v1);
			cv::Point2f right_v1(bottom_right_w_v1, bottom_right_h_v1);
			cv::Point2f left_v2 = vertices[0];
			cv::Point2f right_v2 = vertices[3];

			if (utils::lineLineIntersection(left_v1, right_v1, left_v2, right_v2, &tab, &tcd, false, int_pt)){
				//remove thse two edges
				// add the common edge
				cv::line(result, int_pt, cv::Point(upper_left_w_v2, upper_left_h_v2), fg_color, thickness);
				cv::line(result, int_pt, cv::Point(upper_left_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, int_pt, vertices[3], fg_color, thickness);
				// add ridges
				int ridge_length_v1 = utils::genRand(ridgeRatio_v1.first, ridgeRatio_v1.second) * imageRoofWidth_v1;
				int ridge_w_v1 = upper_left_w_v1 + (imageRoofWidth_v1 - ridge_length_v1) * 0.5;
				int ridge_h_v1 = (upper_left_h_v1 + bottom_right_h_v1) * 0.5;
				int ridge_length_v2 = utils::genRand(ridgeRatio_v2.first, ridgeRatio_v2.second) * imageRoofWidth_v2;
				int ridge_w_v2 = bottom_right_w_v2 - (imageRoofWidth_v2 - ridge_length_v2) * 0.5;
				int ridge_h_v2 = (upper_left_h_v2 + bottom_right_h_v2) * 0.5;
				cv::Point2f ridge_h_v2_new = utils::RotatePoint(cv::Point2f(upper_left_w_v2, upper_left_h_v2), cv::Point2f(ridge_w_v2, ridge_h_v2), (rotate)* M_PI / 180.0);
				cv::line(result, (int_pt + vertices[1]) / 2, ridge_h_v2_new, fg_color, thickness);
				cv::line(result, vertices[2], ridge_h_v2_new, fg_color, thickness);
				cv::line(result, vertices[3], ridge_h_v2_new, fg_color, thickness);
				cv::line(result, (int_pt + vertices[1]) / 2, cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
			}
			else{
				// add ridges
				int ridge_length_v1 = utils::genRand(ridgeRatio_v1.first, ridgeRatio_v1.second) * imageRoofWidth_v1;
				int ridge_w_v1 = upper_left_w_v1 + (imageRoofWidth_v1 - ridge_length_v1) * 0.5;
				int ridge_h_v1 = (upper_left_h_v1 + bottom_right_h_v1) * 0.5;
				int ridge_intersect_w = (upper_left_w_v2 + bottom_right_w_v2)* 0.5;
				int ridge_intersect_h = (upper_left_h_v2 + bottom_right_h_v2) * 0.5;
				int ridge_length_v2 = utils::genRand(ridgeRatio_v2.first, ridgeRatio_v2.second) * imageRoofWidth_v2;
				int ridge_w_v2 = bottom_right_w_v2 - (imageRoofWidth_v2 - ridge_length_v2) * 0.5;
				int ridge_h_v2 = (upper_left_h_v2 + bottom_right_h_v2) * 0.5;
				cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, bottom_right_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(bottom_right_w_v1, bottom_right_h_v1), cv::Point(bottom_right_w_v1, upper_left_h_v1), fg_color, thickness);
				cv::line(result, vertices[1], vertices[0], fg_color, thickness);
				cv::line(result, vertices[0], vertices[3], fg_color, thickness);
				cv::line(result, (vertices[0] + vertices[1]) / 2, cv::Point(ridge_w_v2, ridge_h_v2), fg_color, thickness);
				cv::line(result, vertices[2], cv::Point(ridge_w_v2, ridge_h_v2), fg_color, thickness);
				cv::line(result, vertices[3], cv::Point(ridge_w_v2, ridge_h_v2), fg_color, thickness);
				cv::line(result, (vertices[0] + vertices[1]) / 2, cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(upper_left_w_v1, upper_left_h_v1), cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
				cv::line(result, cv::Point(upper_left_w_v1, bottom_right_h_v1), cv::Point(ridge_w_v1, ridge_h_v1), fg_color, thickness);
			}
		}
		else{
			// do nothing
		}

		char buffer[50];
		sprintf(buffer, "roof_image_%06d.png", index);
		std::string img_filename = roofImagesPath + "/" + std::string(buffer);
		cv::imwrite(img_filename, result);
		{
			out_param << std::string(buffer);
			for (int cluster = 0; cluster < 8; cluster++){
				out_param << ",";
				if (cluster == type){
					out_param << 1;
				}
				else
					out_param << 0;
			}
			out_param << "\n";
		}
		index++;
	}
	return index;
}
