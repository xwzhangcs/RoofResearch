#include "roofB.h"
#include "Utils.h"
#include "roofTypes.h"

cv::Mat RoofB::generateRoof(int width, int height, int roofWidth, double roofAspect, double l_width_ratio, double l_aspect, int selected_roof_type, double ridgeRatio, double l_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	/*std::cout << "width is " << width << std::endl;
	std::cout << "height is " << height << std::endl;
	std::cout << "roofType is " << selected_roof_type << std::endl;
	std::cout << "roofWidth is " << roofWidth << std::endl;
	std::cout << "roofAspect is " << roofAspect << std::endl;*/
	cv::Mat result(height, width, CV_8UC3, bg_color);
	int imageRoofWidth = roofWidth;
	double imageRoofAspect = roofAspect;
	double imageLRoofRatio = l_width_ratio;
	double imageLRoofAspect = l_aspect;
	int imageRoofHeight = imageRoofWidth * imageRoofAspect;
	int imageLRoofWidth = imageRoofWidth * imageLRoofRatio;
	int imageLRoofHeight = imageLRoofWidth * imageLRoofAspect;
	int thickness = 2;
	if (selected_roof_type == RoofTypes::FLAT){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		// add L part
		int l_upper_left_w = bottom_right_w - imageLRoofWidth;
		int l_upper_left_h = bottom_right_h;
		int l_bottom_right_w = bottom_right_w;
		int l_bottom_right_h = bottom_right_h + imageLRoofHeight;
		cv::rectangle(result, cv::Point(l_upper_left_w, l_upper_left_h), cv::Point(l_bottom_right_w, l_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(l_upper_left_w + thickness, l_upper_left_h), cv::Point(l_upper_left_w + imageLRoofWidth - thickness, l_upper_left_h), bg_color, thickness);
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
		int l_upper_left_w = bottom_right_w - imageLRoofWidth;
		int l_upper_left_h = bottom_right_h;
		int l_bottom_right_w = bottom_right_w;
		int l_bottom_right_h = bottom_right_h + imageLRoofHeight;
		cv::rectangle(result, cv::Point(l_upper_left_w, l_upper_left_h), cv::Point(l_bottom_right_w, l_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(l_upper_left_w + thickness, l_upper_left_h), cv::Point(l_upper_left_w + imageLRoofWidth - thickness, l_upper_left_h), bg_color, thickness);
		// add other edges
		int l_ridge_upper_w = (l_upper_left_w + l_bottom_right_w) * 0.5;
		int l_ridge_upper_h = (upper_left_h + bottom_right_h) * 0.5;
		int l_ridge_bottom_w = l_ridge_upper_w;
		int l_ridge_bottom_h = l_bottom_right_h;
		cv::line(result, cv::Point(l_ridge_upper_w, l_ridge_upper_h), cv::Point(l_ridge_bottom_w, l_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(l_ridge_upper_w, l_ridge_upper_h), cv::Point(l_upper_left_w, l_upper_left_h), fg_color, thickness);
		cv::line(result, cv::Point(l_ridge_upper_w, l_ridge_upper_h), cv::Point(l_bottom_right_w, l_upper_left_h), fg_color, thickness);

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
		imageLRoofWidth = imageRoofWidth - ridge_length; // fixed
		imageLRoofHeight = imageLRoofWidth * imageLRoofAspect;
		int l_upper_left_w = bottom_right_w - imageLRoofWidth;
		int l_upper_left_h = bottom_right_h;
		int l_bottom_right_w = bottom_right_w;
		int l_bottom_right_h = bottom_right_h + imageLRoofHeight;
		cv::rectangle(result, cv::Point(l_upper_left_w, l_upper_left_h), cv::Point(l_bottom_right_w, l_bottom_right_h), fg_color, thickness);
		// remove the common edge
		cv::line(result, cv::Point(l_upper_left_w + thickness, l_upper_left_h), cv::Point(l_upper_left_w + imageLRoofWidth - thickness, l_upper_left_h), bg_color, thickness);
		// add insect edge
		cv::line(result, cv::Point(l_upper_left_w, l_upper_left_h), cv::Point(ridge_right_w, ridge_right_h), fg_color, thickness);
		//
		int l_ridge_bottom_w = (l_upper_left_w + l_bottom_right_w) * 0.5;
		int l_ridge_bottom_h = bottom_right_h + imageLRoofHeight * l_ridgeRatio;
		cv::line(result, cv::Point(ridge_right_w, ridge_right_h), cv::Point(l_ridge_bottom_w, l_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(l_upper_left_w, l_bottom_right_h), cv::Point(l_ridge_bottom_w, l_ridge_bottom_h), fg_color, thickness);
		cv::line(result, cv::Point(l_bottom_right_w, l_bottom_right_h), cv::Point(l_ridge_bottom_w, l_ridge_bottom_h), fg_color, thickness);
	}
	else{
		// do nothing
	}
	return result;
}

void RoofB::generateRoofImages(std::string roofImagesPath, int imageNum, int width, int height, std::pair<int, int> roofWidth, std::pair<double, double> roofAspect, std::pair<double, double> l_width_ratio, std::pair<double, double> l_aspect, int selected_roof_type, std::pair<double, double> ridgeRatio, std::pair<double, double> l_ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
}
