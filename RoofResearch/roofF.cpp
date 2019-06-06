#include "roofF.h"
#include "Utils.h"
#include "roofTypes.h"
const float M_PI = 3.1415926535;

cv::Mat RoofF::generateRoof(int width, int height, int roofWidth_main, double roofAspect_main, double roofWidthRatio_sub, double roofAspect_sub, int selected_roof_type, double ridgeRatio_main, double ridgeRatio_sub, const cv::Scalar& bg_color, const cv::Scalar& fg_color){

	cv::Mat result(height, width, CV_8UC3, bg_color);
	int imageRoofWidth_main = roofWidth_main;
	double imageRoofAspect_main = roofAspect_main;
	int imageRoofHeight_main = imageRoofWidth_main * imageRoofAspect_main;
	int imageRoofWidth_sub = roofWidthRatio_sub * imageRoofWidth_main;
	double imageRoofAspect_sub = roofAspect_sub;
	int imageRoofHeight_sub = imageRoofWidth_sub * imageRoofAspect_sub;
	if (2 * imageRoofHeight_main >= imageRoofHeight_sub)
		imageRoofHeight_main = imageRoofHeight_sub * 0.4;
	int thickness = 2;
	if (selected_roof_type == RoofTypes::FLAT){
		// add the left part
		int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int left_w_main = bottom_right_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		// add the right part
		upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int right_w_main = upper_left_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		// add the top main rect in the end
		int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		// add the bottom main rect in the end
		upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
		bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);

	}
	else if (selected_roof_type == RoofTypes::GABLE){
		// add the left part
		int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int left_w_main = bottom_right_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, upper_left_h_sub), cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, bottom_right_h_sub), fg_color, thickness);
		// add the right part
		upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int right_w_main = upper_left_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, upper_left_h_sub), cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, bottom_right_h_sub), fg_color, thickness);
		// add the top main rect in the end
		int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		cv::Point ridege_left_main(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		cv::Point ridege_right_main(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		// add the bottom main rect in the end
		upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
		bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		ridege_left_main = cv::Point(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		ridege_right_main = cv::Point(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		//
	}
	else if (selected_roof_type == RoofTypes::HIP){
		// add the left part
		int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int left_w_main = bottom_right_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		int ridge_length_sub = ridgeRatio_sub * imageRoofHeight_sub;
		int ridge_left_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
		int ridge_left_h_sub = upper_left_h_sub + (imageRoofHeight_sub - ridge_length_sub) * 0.5;
		int ridge_right_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
		int ridge_right_h_sub = ridge_left_h_sub + ridge_length_sub;
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(ridge_right_w_sub, ridge_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(upper_left_w_sub, upper_left_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(bottom_right_w_sub, upper_left_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(upper_left_w_sub, bottom_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);		
		// add the right part
		upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
		upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
		bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
		bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
		int right_w_main = upper_left_w_sub;
		cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		ridge_length_sub = ridgeRatio_sub * imageRoofHeight_sub;
		ridge_left_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
		ridge_left_h_sub = upper_left_h_sub + (imageRoofHeight_sub - ridge_length_sub) * 0.5;
		ridge_right_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
		ridge_right_h_sub = ridge_left_h_sub + ridge_length_sub;
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(ridge_right_w_sub, ridge_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(upper_left_w_sub, upper_left_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(bottom_right_w_sub, upper_left_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(upper_left_w_sub, bottom_right_h_sub), fg_color, thickness);
		cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
		// add the top main rect in the end
		int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
		int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		cv::Point ridege_left_main(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		cv::Point ridege_right_main(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		// add the bottom main rect in the end
		upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
		upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
		bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
		bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
		ridege_left_main = cv::Point(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		ridege_right_main = cv::Point(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
		// remove edges
		cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
		// add edges 
		cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
		cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
		//
	}
	else{
		// do nothing
	}
	return result;
}

int RoofF::generateRoofImages(std::string roofImagesPath, int imageNum, int start_index, int type, int width, int height, std::pair<int, int> roofWidth_main, std::pair<double, double> roofAspect_main, std::pair<double, double> roofWidthRatio_sub, std::pair<double, double> roofAspect_sub, int selected_roof_type, std::pair<double, double> ridgeRatio_main, std::pair<double, double> ridgeRatio_sub, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	std::ofstream out_param(roofImagesPath + "/parameters.txt", std::ios::app);
	int index = start_index;
	for (int l = 0; l < imageNum; l++){
		cv::Mat result(height, width, CV_8UC3, bg_color);
		int imageRoofWidth_main = utils::genRand(roofWidth_main.first, roofWidth_main.second + 1);
		double imageRoofAspect_main = utils::genRand(roofAspect_main.first, roofAspect_main.second);
		int imageRoofHeight_main = imageRoofWidth_main * imageRoofAspect_main;
		int imageRoofWidth_sub = utils::genRand(roofWidthRatio_sub.first, roofWidthRatio_sub.second) * imageRoofWidth_main;
		double imageRoofAspect_sub = utils::genRand(roofAspect_sub.first, roofAspect_sub.second);
		int imageRoofHeight_sub = imageRoofWidth_sub * imageRoofAspect_sub;
		if (2 * imageRoofHeight_main >= imageRoofHeight_sub)
			imageRoofHeight_main = imageRoofHeight_sub * 0.4;
		int thickness = 2;
		if (selected_roof_type == RoofTypes::FLAT){
			// add the left part
			int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int left_w_main = bottom_right_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			// add the right part
			upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int right_w_main = upper_left_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			// add the top main rect in the end
			int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			// add the bottom main rect in the end
			upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
			bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);

		}
		else if (selected_roof_type == RoofTypes::GABLE){
			// add the left part
			int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int left_w_main = bottom_right_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, upper_left_h_sub), cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, bottom_right_h_sub), fg_color, thickness);
			// add the right part
			upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int right_w_main = upper_left_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, upper_left_h_sub), cv::Point((upper_left_w_sub + bottom_right_w_sub) * 0.5, bottom_right_h_sub), fg_color, thickness);
			// add the top main rect in the end
			int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			cv::Point ridege_left_main(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			cv::Point ridege_right_main(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			// add the bottom main rect in the end
			upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
			bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			ridege_left_main = cv::Point(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			ridege_right_main = cv::Point(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			//
		}
		else if (selected_roof_type == RoofTypes::HIP){
			// add the left part
			int upper_left_w_sub = (width - imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			int upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			int bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int left_w_main = bottom_right_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			int ridge_length_sub = utils::genRand(ridgeRatio_sub.first, ridgeRatio_sub.second) * imageRoofHeight_sub;
			int ridge_left_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
			int ridge_left_h_sub = upper_left_h_sub + (imageRoofHeight_sub - ridge_length_sub) * 0.5;
			int ridge_right_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
			int ridge_right_h_sub = ridge_left_h_sub + ridge_length_sub;
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(ridge_right_w_sub, ridge_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(upper_left_w_sub, upper_left_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(bottom_right_w_sub, upper_left_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(upper_left_w_sub, bottom_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			// add the right part
			upper_left_w_sub = (width + imageRoofWidth_main - imageRoofWidth_sub) * 0.5;
			upper_left_h_sub = (height - imageRoofHeight_sub) * 0.5;
			bottom_right_w_sub = upper_left_w_sub + imageRoofWidth_sub;
			bottom_right_h_sub = upper_left_h_sub + imageRoofHeight_sub;
			int right_w_main = upper_left_w_sub;
			cv::rectangle(result, cv::Point(upper_left_w_sub, upper_left_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			ridge_left_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
			ridge_left_h_sub = upper_left_h_sub + (imageRoofHeight_sub - ridge_length_sub) * 0.5;
			ridge_right_w_sub = (upper_left_w_sub + bottom_right_w_sub) * 0.5;
			ridge_right_h_sub = ridge_left_h_sub + ridge_length_sub;
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(ridge_right_w_sub, ridge_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(upper_left_w_sub, upper_left_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_left_w_sub, ridge_left_h_sub), cv::Point(bottom_right_w_sub, upper_left_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(upper_left_w_sub, bottom_right_h_sub), fg_color, thickness);
			cv::line(result, cv::Point(ridge_right_w_sub, ridge_right_h_sub), cv::Point(bottom_right_w_sub, bottom_right_h_sub), fg_color, thickness);
			// add the top main rect in the end
			int upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			int upper_left_h_main = (height - imageRoofHeight_sub) * 0.5;
			int bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			int bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			cv::Point ridege_left_main(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			cv::Point ridege_right_main(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			// add the bottom main rect in the end
			upper_left_w_main = (width - imageRoofWidth_main) * 0.5;;
			upper_left_h_main = (height + imageRoofHeight_sub) * 0.5 - imageRoofHeight_main;
			bottom_right_w_main = upper_left_w_main + imageRoofWidth_main;
			bottom_right_h_main = upper_left_h_main + imageRoofHeight_main;
			ridege_left_main = cv::Point(upper_left_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			ridege_right_main = cv::Point(bottom_right_w_main, (upper_left_h_main + bottom_right_h_main) * 0.5);
			// remove edges
			cv::line(result, cv::Point(left_w_main, upper_left_h_main + thickness), cv::Point(left_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			cv::line(result, cv::Point(right_w_main, upper_left_h_main + thickness), cv::Point(right_w_main, bottom_right_h_main - thickness), bg_color, thickness);
			// add edges 
			cv::line(result, cv::Point(left_w_main, upper_left_h_main), cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, cv::Point(left_w_main, bottom_right_h_main), cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, ridege_right_main, fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_left_main, cv::Point(left_w_main, bottom_right_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, upper_left_h_main), fg_color, thickness);
			cv::line(result, ridege_right_main, cv::Point(right_w_main, bottom_right_h_main), fg_color, thickness);
			//
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
