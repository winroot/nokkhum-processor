/*
 * video_writer.h
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_WRITER_HPP_
#define NOKKHUM_VIDEO_WRITER_HPP_

#include <string>
using std::string;

#include <opencv/highgui.h>
using cv::Mat;

namespace nokkhum {

class VideoWriter {
public:
	VideoWriter(string filename, string directory, int width, int height, int frame_rate);
	virtual ~VideoWriter();

	virtual void write_frame(Mat &frame) = 0;

private:
	string filename;
	string directory;
	int width;
	int height;
	int frame_rate;
};

}

#endif /* NOKKHUM_VIDEO_WRITER_H_ */
