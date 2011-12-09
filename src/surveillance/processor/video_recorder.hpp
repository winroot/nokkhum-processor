/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_HPP_
#define NOKKHUM_VIDEO_RECORDER_HPP_

#include <string>
#include <thread>
#include <boost/thread.hpp>
#include <mutex>

#include <opencv2/core/core.hpp>

#include "image_processor.hpp"
#include "../../video/video_writer.hpp"
#include "../../util/cv_mat_queue.hpp"
#include "../../config/video_recorder_attribute.hpp"

namespace nokkhum {

class VideoRecorder;

class RecordTimer {
public:
	RecordTimer();
	RecordTimer(VideoRecorder *video_recorder, int period);
	RecordTimer(const RecordTimer&);

	~RecordTimer();

	RecordTimer& operator = (const RecordTimer&);

	void start();
	void stop();
	void clock();

private:
	bool running;
	VideoRecorder *video_recorder;
	int period;
	boost::thread timer_thred;
};

class VideoRecorder : public nokkhum::ImageProcessor {
public:
	VideoRecorder(CvMatQueue& input_image_queue);
	VideoRecorder(CvMatQueue& input_image_queue, VideoRecorderAttribute* vrp);
	virtual ~VideoRecorder();

	void start();
	void stop();

	bool is_writer_available();

	friend class RecordTimer;
protected:
	nokkhum::VideoWriter *writer;
	std::string filename;
	std::string directory;
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	unsigned int period;

	RecordTimer *timer;
	std::mutex writer_mutex;

	virtual void getNewVideoWriter();
	virtual void startRecord();
	virtual void startTimer();
	virtual void stopTimer();

};

}

#endif /* NOKKHUM_VIDEO_RECORDER_HPP_ */