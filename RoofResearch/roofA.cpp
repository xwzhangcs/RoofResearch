#include "roofA.h"
#include "Utils.h"
#include "roofTypes.h"

cv::Mat RoofA::generateRoof(int width, int height, int roofWidth, double roofAspect, int selected_roof_type, double ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	/*std::cout << "width is " << width << std::endl;
	std::cout << "height is " << height << std::endl;
	std::cout << "roofType is " << selected_roof_type << std::endl;
	std::cout << "roofWidth is " << roofWidth << std::endl;
	std::cout << "roofAspect is " << roofAspect << std::endl;*/
	cv::Mat result(height, width, CV_8UC3, bg_color);
	int imageRoofWidth = roofWidth;
	double imageRoofAspect = roofAspect;
	int imageRoofHeight = imageRoofWidth * imageRoofAspect;
	int thickness = 2;
	if (selected_roof_type == RoofTypes::FLAT){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
	}
	else if (selected_roof_type == RoofTypes::GABLE){
		int upper_left_w = (width - imageRoofWidth) * 0.5;
		int upper_left_h = (height - imageRoofHeight) * 0.5;
		int bottom_right_w = upper_left_w + imageRoofWidth;
		int bottom_right_h = upper_left_h + imageRoofHeight;
		cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		// add ridge
		cv::line(result, cv::Point(upper_left_w, height / 2), cv::Point(bottom_right_w, height / 2), fg_color, thickness);
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
		int ridge_right_w = ridge_left_w + ridge_length;
		cv::line(result, cv::Point(ridge_left_w, height / 2), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
		// connect other roof edges
		cv::line(result, cv::Point(upper_left_w, upper_left_h), cv::Point(ridge_left_w, height / 2), fg_color, thickness);
		cv::line(result, cv::Point(upper_left_w, bottom_right_h), cv::Point(ridge_left_w, height / 2), fg_color, thickness);
		cv::line(result, cv::Point(bottom_right_w, upper_left_h), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
		cv::line(result, cv::Point(bottom_right_w, bottom_right_h), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
	}
	else{
		// do nothing
	}
	return result;
}

int RoofA::generateRoofImages(std::string roofImagesPath, int imageNum, int start_index, int type, int width, int height, std::pair<int, int> roofWidth, std::pair<double, double> roofAspect, int selected_roof_type, std::pair<double, double> ridgeRatio, const cv::Scalar& bg_color, const cv::Scalar& fg_color){
	std::ofstream out_param(roofImagesPath + "/parameters.txt", std::ios::app);
	int index = start_index;
	for (int l = 0; l < imageNum; l++){
		cv::Mat result(height, width, CV_8UC3, bg_color);
		int imageRoofWidth = utils::genRand(roofWidth.first, roofWidth.second + 1);
		double imageRoofAspect = utils::genRand(roofAspect.first, roofAspect.second);
		int imageRoofHeight = imageRoofWidth * imageRoofAspect;
		int thickness = 2;
		/*std::cout << "imageRoofAspect is " << imageRoofAspect << std::endl;
		std::cout << "imageRoofWidth is " << imageRoofWidth << std::endl;
		std::cout << "imageRoofHeight is " << imageRoofHeight << std::endl;*/
		if (selected_roof_type == RoofTypes::FLAT){
			int upper_left_w = (width - imageRoofWidth) * 0.5;
			int upper_left_h = (height - imageRoofHeight) * 0.5;
			int bottom_right_w = upper_left_w + imageRoofWidth;
			int bottom_right_h = upper_left_h + imageRoofHeight;
			cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
		}
		else if (selected_roof_type == RoofTypes::GABLE){
			int upper_left_w = (width - imageRoofWidth) * 0.5;
			int upper_left_h = (height - imageRoofHeight) * 0.5;
			int bottom_right_w = upper_left_w + imageRoofWidth;
			int bottom_right_h = upper_left_h + imageRoofHeight;
			cv::rectangle(result, cv::Point(upper_left_w, upper_left_h), cv::Point(bottom_right_w, bottom_right_h), fg_color, thickness);
			// add ridge
			cv::line(result, cv::Point(upper_left_w, height / 2), cv::Point(bottom_right_w, height / 2), fg_color, thickness);
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
			int ridge_right_w = ridge_left_w + ridge_length;
			cv::line(result, cv::Point(ridge_left_w, height / 2), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
			// connect other roof edges
			cv::line(result, cv::Point(upper_left_w, upper_left_h), cv::Point(ridge_left_w, height / 2), fg_color, thickness);
			cv::line(result, cv::Point(upper_left_w, bottom_right_h), cv::Point(ridge_left_w, height / 2), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w, upper_left_h), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
			cv::line(result, cv::Point(bottom_right_w, bottom_right_h), cv::Point(ridge_right_w, height / 2), fg_color, thickness);
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
