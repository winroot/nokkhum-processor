/*
 * image.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: boatkrap
 */

#include "image.hpp"

namespace nokkhum {

Image::Image() {
	// TODO Auto-generated constructor stub

}

Image::Image(cv::Mat image):image(image) {
	this->date = std::chrono::system_clock::now();
}

Image::~Image() {
	// TODO Auto-generated destructor stub
	this->date = std::chrono::system_clock::now();
}

Image& Image::operator >> (cv::Mat& image) {
	image = this->image.clone();
	return *this;
}

Image& Image::operator << (cv::Mat& image){
	this->image = image.clone();
	this->date = std::chrono::system_clock::now();
	return *this;
}

cv::Mat Image::get(){
	return this->image;
}

} /* namespace nokkhum */
