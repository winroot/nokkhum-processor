/*
 * image_processor_factory.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#include "image_processor_factory.hpp"

#include "../../config/motion_detector_attribute.hpp"
#include "../../config/face_detector_attribute.hpp"
#include "../../config/video_recorder_attribute.hpp"
#include "../../config/image_recorder_attribute.hpp"
#include "../../config/multimedia_recorder_attribute.hpp"
#include "../../config/face_recognition_attribute.hpp"
#include "../../config/face_preprocess_attribute.hpp"
#include "../../config/none_processor_attribute.hpp"

#include "face_detector.hpp"
#include "face_recognition.hpp"
#include "face_preprocess.hpp"
#include "motion_detector.hpp"
#include "image_processor.hpp"
#include "video_recorder.hpp"
#include "image_recorder.hpp"
#include "video_motion_recorder.hpp"
#include "multimedia_recorder.hpp"
#include "none_processor.hpp"
#include "motion_detector_background_sub.hpp"
#include "../notification/notification.hpp"


#include <iostream>
#include <vector>
#include <exception>

namespace nokkhum {

ImageProcessorFactory::ImageProcessorFactory(std::shared_ptr<CameraAttribute> camera_attribute) : camera_attribute(camera_attribute){
	// TODO Auto-generated constructor stub

}

ImageProcessorFactory::~ImageProcessorFactory() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ImageProcessor> ImageProcessorFactory::getImageProcessor(
		std::shared_ptr<ImageProcessorAttribute> ipp, ImageQueue &image_queue) {
	if (ipp->getName() == "Motion Detector") {
		std::shared_ptr<MotionDetector> md;
		std::shared_ptr<MotionDetectorAttribute> mdp = std::static_pointer_cast<MotionDetectorAttribute>(ipp);
		if(mdp->getMotionAnalysis() == "Optical Flow"){
			md = std::make_shared<MotionDetector>(image_queue, *mdp);
		}else{
			md = std::make_shared<BackgroundMotionDetector>(image_queue, *mdp);
		}
		return md;

	} else if (ipp->getName() == "Face Detector") {
		std::shared_ptr<FaceDetectorAttribute> fdp = std::static_pointer_cast<FaceDetectorAttribute>(ipp);
		std::shared_ptr<FaceDetector> fd = std::make_shared<FaceDetector>(image_queue, *fdp);
		return fd;

	} else if (ipp->getName() == "Video Recorder") {
		std::shared_ptr<VideoRecorderAttribute> vrp = std::static_pointer_cast<VideoRecorderAttribute>(ipp);
		std::shared_ptr<VideoRecorder> vr = std::make_shared<VideoRecorder>(image_queue, *vrp);
		return vr;

	} else if (ipp->getName() == "Video Motion Recorder") {
		std::shared_ptr<VideoRecorderAttribute> vrp = std::static_pointer_cast<VideoRecorderAttribute>(ipp);
		std::shared_ptr<VideoMotionRecorder> vmr = std::make_shared<VideoMotionRecorder>(image_queue, *vrp);
		return vmr;

	} else if (ipp->getName() == "Image Recorder") {
		std::shared_ptr<ImageRecorderAttribute> irp = std::static_pointer_cast<ImageRecorderAttribute>(ipp);
		std::shared_ptr<ImageRecorder> ir = std::make_shared<ImageRecorder>(image_queue, *irp);
		return ir;
	} else if (ipp->getName() == "Multimedia Recorder") {
		std::shared_ptr<MultimediaRecorderAttribute> mrp = std::static_pointer_cast<MultimediaRecorderAttribute>(ipp);
		mrp->setVideoUri(this->camera_attribute->getVideoUri());
		mrp->setAudioUri(this->camera_attribute->getAudioUri());
		std::shared_ptr<MultimediaRecorder> mr = std::make_shared<MultimediaRecorder>(image_queue, *mrp);
		return mr;
	} else if(ipp->getName() == "Notification"){
		//std::cout << "notification :P" << std::endl;
		std::shared_ptr<NotificationAttribute> nfp = std::static_pointer_cast<NotificationAttribute>(ipp);
		std::shared_ptr<Notification> nf = std::make_shared<Notification>(image_queue, *nfp, camera_attribute->getId());
		return nf;
	} else if(ipp->getName() == "None Processor"){
		std::shared_ptr<NoneProcessorAttribute> npp = std::static_pointer_cast<NoneProcessorAttribute>(ipp);
		std::shared_ptr<NoneProcessor> np = std::make_shared<NoneProcessor>(image_queue, *npp);
		return np;
	} else if(ipp->getName() == "Face Recognition"){
		std::shared_ptr<FaceRecognitionAttribute> frp = std::static_pointer_cast<FaceRecognitionAttribute>(ipp);
		std::shared_ptr<FaceRecognition>  fr = std::make_shared<FaceRecognition>(image_queue, *frp);
		return fr;
	} else if(ipp->getName() == "Face Preprocess"){
		std::shared_ptr<FacePreprocessAttribute> fpp = std::static_pointer_cast<FacePreprocessAttribute>(ipp);
		std::shared_ptr<FacePreprocess>  fp = std::make_shared<FacePreprocess>(image_queue, *fpp);
		return fp;
	}

	return nullptr;
}

std::vector< std::shared_ptr<ImageProcessor> > ImageProcessorFactory::getImageProcessorPool(
		std::shared_ptr<ImageProcessorAttribute> ipp, MultipleImageQueue &mmq) {
	std::shared_ptr<ImageProcessor> tmp = nullptr;

//	std::cout
//			<< "-------------------------- Start Image Processor Attribute ------------------------------------"
//			<< std::endl;
//
//	std::cout << "name: " << ipp->getName() << std::endl;
//	std::cout << "mmq size: " << mmq.getSize() << std::endl;
	std::vector< std::shared_ptr<ImageProcessor> > image_processor_pool;

	ImageQueue image_queue;
	if (ipp->getName() != "default") {

	}

	auto ippv = ipp->getImageProcessorAttributeVector();

	for (std::vector< std::shared_ptr<ImageProcessor> >::size_type i = 0; i < ippv.size();
			i++) {
//		std::cout << "Build processor name V1: " << ippv[i]->getName()
//				<< std::endl;

		std::shared_ptr<ImageQueue> image_queue = mmq.get(i);

//		std::cout << "get queue " << std::endl;

		tmp = this->getImageProcessor(ippv[i], *image_queue);
		image_processor_pool.push_back(tmp);

		int size = ippv[i]->getImageProcessorAttributeVector().size();

//		std::cout << "size: " << size << std::endl;
		if (size > 0) {
			auto imageProcessorAttributeVector =
					ippv[i]->getImageProcessorAttributeVector();
			this->getImageProcessorFromVector(image_processor_pool,
					imageProcessorAttributeVector, tmp);
		}

	}

//	std::cout
//			<< "-------------------------- Show Image Processor Attribute --------------------------------------"
//			<< std::endl;
//	for (unsigned long i = 0; i < image_processor_pool.size(); i++) {
//		if (image_processor_pool[i])
//			std::cout << "Vector, processor name: "
//					<< image_processor_pool[i]->getName() << std::endl;
//		else
//			std::cout << "Vector, processor name: nullptr" << std::endl;
//	}
//	std::cout
//			<< "-------------------------- End Image Processor Attribute --------------------------------------"
//			<< std::endl;

	return image_processor_pool;

}

void ImageProcessorFactory::getImageProcessorFromVector(
		std::vector< std::shared_ptr<ImageProcessor> > & image_processor_pool,
		std::vector< std::shared_ptr<ImageProcessorAttribute> > & ippv,
		std::shared_ptr<ImageProcessor> parent_image_processor) {

	std::shared_ptr<ImageProcessor> tmp = nullptr;
	for (std::vector< std::shared_ptr<ImageProcessorAttribute> >::size_type i = 0; i < ippv.size();
			i++) {
//		std::cout << "Build processor name recursive: " << ippv[i]->getName()
//				<< std::endl;

		std::shared_ptr<ImageQueue> image_queue =
				parent_image_processor->getNewOutputImageQueue();
		tmp = this->getImageProcessor(ippv[i], *image_queue);
		image_processor_pool.push_back(tmp);

		int size = ippv[i]->getImageProcessorAttributeVector().size();

//		std::cout << "size: " << size << std::endl;
		if (size > 0) {
			auto imageProcessorAttributeVector =
					ippv[i]->getImageProcessorAttributeVector();
			this->getImageProcessorFromVector(image_processor_pool,
					imageProcessorAttributeVector, tmp);
		}

	}

}

} /* namespace nokkhum */
