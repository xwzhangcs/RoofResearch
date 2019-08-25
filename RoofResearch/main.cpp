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

int main(int argc, char** argv)
{
	cv::Mat src = cv::imread("../data/rotate.png", CV_LOAD_IMAGE_UNCHANGED);
	//cv::Mat dst;
	//cv::Point2f pt(src.cols / 2., src.rows / 2.);
	//cv::Mat r = cv::getRotationMatrix2D(pt, 15, 1.0);
	//warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
	//cv::imwrite("../data/rotate.png", dst);
	std::vector<int> boundaries = adjust_chip(src);
	cv::Mat adjust_img = src(cv::Rect(boundaries[2], boundaries[0], boundaries[3] - boundaries[2] + 1, boundaries[1] - boundaries[0] + 1));
	// resize to 200 by 200
	cv::resize(adjust_img, adjust_img, cv::Size(200, 200));
	// add padding
	int padding_size = 12;
	int borderType = cv::BORDER_CONSTANT;
	cv::Mat img_padding;
	cv::copyMakeBorder(adjust_img, img_padding, padding_size, padding_size, padding_size, padding_size, borderType, cv::Scalar(0, 0, 0));
	cv::imwrite("../data/resize.png", img_padding);
	system("pause");
	return 0;
}

std::vector<int> adjust_chip(cv::Mat chip) {
	std::vector<int> boundaries;
	boundaries.resize(4); // top, bottom, left and right
	if (chip.channels() != 1) {
		boundaries[0] = 0;
		boundaries[1] = chip.size().height - 1;
		boundaries[2] = 0;
		boundaries[3] = chip.size().width - 1;
		return boundaries;
	}
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