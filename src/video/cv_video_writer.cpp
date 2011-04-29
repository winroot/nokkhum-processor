/*
 * cv_video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "cv_video_writer.hpp"

namespace nokkhum {

CvVideoWriter::CvVideoWriter(string directory, string filename, int width,
		int height, int frame_rate) :
	VideoWriter(directory, filename, width, height, frame_rate) {
	string record_name = directory + filename;
	record = new cv::VideoWriter(record_name.c_str(), CV_FOURCC('D','I','V','X'),
			frame_rate, cv::Size(width, height), true);
}

CvVideoWriter::~CvVideoWriter() {
	delete record;
	record = NULL;
}

void CvVideoWriter::write_frame(Mat & frame) {
}

}
