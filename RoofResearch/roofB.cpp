#include "roofB.h"
#include "Utils.h"
#include "roofTypes.h"

cv::Mat RoofB::generateRoof(int width, int height, int roofWidth, double roofAspect, double t_width_ratio, double t_aspect, double t_displacement, int selected_roof_type, double ridgeRatio, double t_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	/*std::cout << "width is " << width << std::endl;
	std::cout << "height is " << height << std::endl;
	std::cout << "roofType is " << selected_roof_type << std::endl;
	std::cout << "roofWidth is " << roofWidth << std::endl;
	std::cout << "roofAspect is " << roofAspect << std::endl;*/
	// check validness
	if (t_width_ratio + t_displacement > 1.0){
		std::cout << "t_width_ratio + t_displacement is bigger than 1.0" << std::endl;
		t_displacement = 1.0 - t_width_ratio;
	}
	cv::Mat result(height, width, CV_8UC3, bg_color);
	int imageRoofWidth = roofWidth;
	double imageRoofAspect = roofAspect;
	double imageLRoofRatio = t_width_ratio;
	double imageLRoofAspect = t_aspect;
	int imageRoofHeight = imageRoofWidth * imageRoofAspect;
	int imageTRoofWidth = imageRoofWidth * imageLRoofRatio;
	int imageTRoofHeight = imageTRoofWidth * imageLRoofAspect;

	int thickness = 2;
	if (selected_roof_type == RoofTypes::FLAT){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		// add L part
		int t_upper_left_w = upper_left_w + imageRoofWidth * t_displacement;
		int t_upper_left_h = bottom_right_h;
		int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
		int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
		cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
	}
	else if (selected_roof_type == RoofTypes::GABLE){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		// add ridge
		cv::line(result, cv::Point(upper_left_w, height / 2), cv::Point(bottom_right_w, height / 2), fg_color, thickness);
		// add L part
		int t_upper_left_w = upper_left_w + imageRoofWidth * t_displacement;
		int t_upper_left_h = bottom_right_h;
		int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
		int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
		cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
		// add other edges
		int t_ridge_upper_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
		int t_ridge_upper_h = (upper_left_h + bottom_right_h) * 0.5;
		int t_ridge_bottom_w = t_ridge_upper_w;
		int t_ridge_bottom_h = t_bottom_right_h;
		cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_upper_left_w, t_upper_left_h), fg_color, thickness);
		cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_bottom_right_w, t_upper_left_h), fg_color, thickness);
	}
	else if (selected_roof_type == RoofTypes::HIP){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		// add ridge
		int ridge_length = ridgeRatio * imageRoofWidth;
		int ridge_left_w = (width - ridge_length) * 0.5;
		int ridge_left_h = height / 2;
		int ridge_right_w = ridge_left_w + ridge_length;
		int ridge_right_h = height / 2;
		cv::line(result, cv::Point(ridge_left_w, ridge_left_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
		// connect other roof edges
		cv::line(result, cv::Point(upper_left_w, upper_left_h), cv::Point(ridge_left_w, ridge_left_h), fg_color, thickness);
		cv::line(result, cv::Point(upper_left_w, bottom_right_h), cv::Point(ridge_left_w, ridge_left_h), fg_color, thickness);
		cv::line(result, cv::Point(bottom_right_w, upper_left_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
		cv::line(result, cv::Point(bottom_right_w, bottom_right_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
		// add L part
		int t_upper_left_w = upper_left_w + imageRoofWidth * t_displacement;
		int t_upper_left_h = bottom_right_h;
		int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
		int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
		cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
		// add edges
		int t_ridge_upper_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
		int t_ridge_upper_h = (upper_left_h + bottom_right_h) * 0.5;
		int t_ridge_bottom_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
		int t_ridge_bottom_h = bottom_right_h + imageTRoofHeight * t_ridgeRatio;
		cv::line(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_ridge_upper_w, t_ridge_upper_h), fg_color, thickness);
		cv::line(result, cv::Point(t_bottom_right_w, t_upper_left_h), cv::Point(t_ridge_upper_w, t_ridge_upper_h), fg_color, thickness);
		cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(t_upper_left_w, t_bottom_right_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(t_bottom_right_w, t_bottom_right_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
	}
	else{
		// do nothing
	}
	return result;
}

void RoofB::generateRoofImages(std::string roofImagesPath, int imageNum, int width, int height, std::pair<int, int> roofWidth, std::pair<double, double> roofAspect, std::pair<double, double> t_width_ratio, std::pair<double, double> t_aspect, std::pair<double, double> t_displacement, int selected_roof_type, std::pair<double, double> ridgeRatio, std::pair<double, double> t_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	std::ofstream out_param(roofImagesPath + "/parameters.txt", std::ios::app);
	int index = 0;
	for (int l = 0; l < imageNum; l++){
		cv::Mat result(height, width, CV_8UC3, bg_color);
		int imageRoofWidth = utils::genRand(roofWidth.first, roofWidth.second + 1);
		double imageRoofAspect = utils::genRand(roofAspect.first, roofAspect.second);
		double imageTRoofRatio = utils::genRand(t_width_ratio.first, t_width_ratio.second);
		double imageTRoofAspect = utils::genRand(t_aspect.first, t_aspect.second);
		int imageRoofHeight = imageRoofWidth * imageRoofAspect;
		int imageTRoofWidth = imageRoofWidth * imageTRoofRatio;
		int imageTRoofHeight = imageTRoofWidth * imageTRoofAspect;
		if (imageRoofHeight + imageTRoofHeight > 0.5 * (height + imageRoofHeight))
			continue;
		int thickness = 2;
		if (selected_roof_type == RoofTypes::FLAT){
			int upper_left_w = (width - imageRoofWidth) * 0.5;
			int upper_left_h = (height - imageRoofHeight) * 0.5;
			int bottom_right_w = upper_left_w + imageRoofWidth;
			int bottom_right_h = upper_left_h + imageRoofHeight;
			cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
			// add L part
			int t_upper_left_w = upper_left_w + imageRoofWidth * utils::genRand(t_displacement.first, t_displacement.second);
			int t_upper_left_h = bottom_right_h;
			int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
			int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
			cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
			// remove the common edge
			cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
		}
		else if (selected_roof_type == RoofTypes::GABLE){
			int upper_left_w = (width - imageRoofWidth) * 0.5;
			int upper_left_h = (height - imageRoofHeight) * 0.5;
			int bottom_right_w = upper_left_w + imageRoofWidth;
			int bottom_right_h = upper_left_h + imageRoofHeight;
			cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
			// add ridge
			cv::line(result, cv::Point(upper_left_w, height / 2), cv::Point(bottom_right_w, height / 2), fg_color, thickness);
			// add L part
			int t_upper_left_w = upper_left_w + imageRoofWidth * utils::genRand(t_displacement.first, t_displacement.second);
			int t_upper_left_h = bottom_right_h;
			int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
			int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
			cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
			// remove the common edge
			cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
			// add other edges
			int t_ridge_upper_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
			int t_ridge_upper_h = (upper_left_h + bottom_right_h) * 0.5;
			int t_ridge_bottom_w = t_ridge_upper_w;
			int t_ridge_bottom_h = t_bottom_right_h;
			cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
			cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_upper_left_w, t_upper_left_h), fg_color, thickness);
			cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_bottom_right_w, t_upper_left_h), fg_color, thickness);

		}
		else if (selected_roof_type == RoofTypes::HIP){
			int upper_left_w = (width - imageRoofWidth) * 0.5;
			int upper_left_h = (height - imageRoofHeight) * 0.5;
			int bottom_right_w = upper_left_w + imageRoofWidth;
			int bottom_right_h = upper_left_h + imageRoofHeight;
			cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
			// add ridge
			int ridge_length = utils::genRand(ridgeRatio.first, ridgeRatio.second) * imageRoofWidth;
			int ridge_left_w = (width - ridge_length) * 0.5;
			int ridge_left_h = height / 2;
			int ridge_right_w = ridge_left_w + ridge_length;
			int ridge_right_h = height / 2;
			cv::line(result, cv::Point(ridge_left_w, ridge_left_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
			// connect other roof edges
			cv::line(result, cv::Point(upper_left_w, upper_left_h), cv::Point(ridge_left_w, ridge_left_h), fg_color, thickness);
			cv::line(result, cv::Point(upper_left_w, bottom_right_h), cv::Point(ridge_left_w, ridge_left_h), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w, upper_left_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w, bottom_right_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
			// add L part
			int t_upper_left_w = upper_left_w + imageRoofWidth * utils::genRand(t_displacement.first, t_displacement.second);
			int t_upper_left_h = bottom_right_h;
			int t_bottom_right_w = t_upper_left_w + imageTRoofWidth;
			int t_bottom_right_h = t_upper_left_h + imageTRoofHeight;
			cv::rectangle(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_bottom_right_w, t_bottom_right_h), fg_color, thickness);
			// remove the common edge
			cv::line(result, cv::Point(t_upper_left_w + thickness, t_upper_left_h), cv::Point(t_bottom_right_w - thickness, t_upper_left_h), bg_color, thickness);
			// add edges
			int t_ridge_upper_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
			int t_ridge_upper_h = (upper_left_h + bottom_right_h) * 0.5;
			int t_ridge_bottom_w = (t_upper_left_w + t_bottom_right_w) * 0.5;
			int t_ridge_bottom_h = bottom_right_h + imageTRoofHeight * utils::genRand(t_ridgeRatio.first, t_ridgeRatio.second);
			cv::line(result, cv::Point(t_upper_left_w, t_upper_left_h), cv::Point(t_ridge_upper_w, t_ridge_upper_h), fg_color, thickness);
			cv::line(result, cv::Point(t_bottom_right_w, t_upper_left_h), cv::Point(t_ridge_upper_w, t_ridge_upper_h), fg_color, thickness);
			cv::line(result, cv::Point(t_ridge_upper_w, t_ridge_upper_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
			cv::line(result, cv::Point(t_upper_left_w, t_bottom_right_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
			cv::line(result, cv::Point(t_bottom_right_w, t_bottom_right_h), cv::Point(t_ridge_bottom_w, t_ridge_bottom_h), fg_color, thickness);
		}
		else{
			// do nothing
		}

		char buffer[50];
		sprintf(buffer, "/roofB_image_%06d.png", index);
		std::string img_filename = roofImagesPath + std::string(buffer);
		cv::imwrite(img_filename, result);
		index++;
	}
}
