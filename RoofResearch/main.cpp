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

std::vector<int> adjust_chip(cv::Mat chip);
void generate_test_img(std::string path, int res_src, int res_dst, int padding, bool bDownSampling);

int main(int argc, char** argv)
{
	std::string path = "../data/ex7";
	generate_test_img(std::string path, int res_src, int res_dst, int padding, false);
	system("pause");
	return 0;
}

std::vector<int> adjust_chip(cv::Mat chip) {
	std::vector<int> boundaries;
	boundaries.resize(4); // top, bottom, left and right
	if (chip.channels() == 4)
		cv::cvtColor(chip, chip, CV_RGBA2GRAY);
	if (chip.channels() == 3)
		cv::cvtColor(chip, chip, CV_RGB2GRAY);
	// find the boundary
	double thre_upper = 1.1; // don't apply here
	double thre_lower = 0.1;
	// top 
	int pos_top = 0;
	int black_pixels = 0;
	for (int i = 0; i < chip.size().height; i++) {
		black_pixels = 0;
		for (int j = 0; j < chip.size().width; j++) {
			if ((int)chip.at<uchar>(i, j) == 255) {
				black_pixels++;
			}
		}
		double ratio = black_pixels * 1.0 / chip.size().width;
		if (ratio < thre_upper && ratio > thre_lower) {
			pos_top = i;
			break;
		}
	}

	// bottom 
	black_pixels = 0;
	int pos_bot = 0;
	for (int i = chip.size().height - 1; i >= 0; i--) {
		black_pixels = 0;
		for (int j = 0; j < chip.size().width; j++) {
			//noise
			if ((int)chip.at<uchar>(i, j) == 255) {
				black_pixels++;
			}
		}
		double ratio = black_pixels * 1.0 / chip.size().width;
		if (ratio < thre_upper && ratio > thre_lower) {
			pos_bot = i;
			break;
		}
	}

	// left
	black_pixels = 0;
	int pos_left = 0;
	for (int i = 0; i < chip.size().width; i++) {
		black_pixels = 0;
		for (int j = 0; j < chip.size().height; j++) {
			//noise
			if ((int)chip.at<uchar>(j, i) == 255) {
				black_pixels++;
			}
		}
		double ratio = black_pixels * 1.0 / chip.size().height;
		if (ratio < thre_upper && ratio > thre_lower) {
			pos_left = i;
			break;
		}
	}
	// right
	black_pixels = 0;
	int pos_right = 0;
	for (int i = chip.size().width - 1; i >= 0; i--) {
		black_pixels = 0;
		for (int j = 0; j < chip.size().height; j++) {
			//noise
			if ((int)chip.at<uchar>(j, i) == 255) {
				black_pixels++;
			}
		}
		double ratio = black_pixels * 1.0 / chip.size().height;
		if (ratio < thre_upper && ratio > thre_lower) {
			pos_right = i;
			break;
		}
	}
	boundaries[0] = pos_top;
	boundaries[1] = pos_bot;
	boundaries[2] = pos_left;
	boundaries[3] = pos_right;
	return boundaries;
}

void generate_test_img(std::string path, int res_src, int res_dst, int padding, bool bDownSampling){
	cv::Mat src = cv::imread(path + "/src.png", CV_LOAD_IMAGE_UNCHANGED);
	bool bChanged = false;
	if (src.channels() == 4){
		cv::cvtColor(src, src, CV_RGBA2GRAY);
		bChanged = true;
	}
	if (src.channels() == 3){
		cv::cvtColor(src, src, CV_RGB2GRAY);
		bChanged = true;
	}
	if (bChanged){
		// correct the color
		for (int i = 0; i < src.size().height; i++) {
			for (int j = 0; j < src.size().width; j++) {
				//noise
				if ((int)src.at<uchar>(i, j) < 128) {
					src.at<uchar>(i, j) = (uchar)0;
				}
				else
					src.at<uchar>(i, j) = (uchar)255;
			}
		}
		cv::imwrite(path + "/correct.png", src);
	}
	std::vector<int> boundaries = adjust_chip(src);
	cv::Mat adjust_img = src(cv::Rect(boundaries[2], boundaries[0], boundaries[3] - boundaries[2] + 1, boundaries[1] - boundaries[0] + 1));
	cv::imwrite(path + "/asjust.png", adjust_img);

	int target_small_width = res_src;
	int target_small_height = res_src;
	int target_big_width = res_dst;
	int target_big_height = res_dst;
	int step = res_dst / res_src;
	int padding_size = padding;

	if (!bDownSampling){
		cv::Mat big_img;
		cv::resize(adjust_img, big_img, cv::Size(target_big_width, target_big_height));
		// correct the color
		for (int i = 0; i < big_img.size().height; i++) {
			for (int j = 0; j < big_img.size().width; j++) {
				//noise
				if ((int)big_img.at<uchar>(i, j) < 200) {
					big_img.at<uchar>(i, j) = (uchar)0;
				}
				else
					big_img.at<uchar>(i, j) = (uchar)255;
			}
		}
		cv::imwrite(path + "/big.png", big_img);
		// add padding
		int borderType = cv::BORDER_CONSTANT;
		cv::Mat img_padding;
		cv::copyMakeBorder(big_img, img_padding, padding_size, padding_size, padding_size, padding_size, borderType, cv::Scalar(0, 0, 0));
		cv::imwrite(path + "/final.png", img_padding);
	}
	else{
		cv::Mat small_img;
		cv::resize(adjust_img, small_img, cv::Size(target_small_width, target_small_height));
		// correct color
		for (int i = 0; i < small_img.size().height; i++) {
			for (int j = 0; j < small_img.size().width; j++) {
				//noise
				if ((int)small_img.at<uchar>(i, j) < 200) {
					small_img.at<uchar>(i, j) = (uchar)0;
				}
				else
					small_img.at<uchar>(i, j) = (uchar)255;
			}
		}
		cv::imwrite(path + "/small.png", small_img);
		cv::Mat big_img(target_big_width, target_big_height, CV_8UC1);;
		for (int i = 0; i < big_img.size().height; i++) {
			for (int j = 0; j < big_img.size().width; j++) {
				big_img.at<uchar>(i, j) = small_img.at<uchar>(i / step, j / step);
			}
		}
		cv::imwrite(path + "/big.png", big_img);
		// add padding
		int borderType = cv::BORDER_CONSTANT;
		cv::Mat img_padding;
		cv::copyMakeBorder(big_img, img_padding, padding_size, padding_size, padding_size, padding_size, borderType, cv::Scalar(0, 0, 0));
		cv::imwrite(path + "/final.png", img_padding);
	}
}