/*
 * configuration.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */
//#include <glog/logging.h>
#include "configuration.hpp"
#include "json_parser.hpp"

namespace nokkhum {

Configuration::Configuration() {
	this->camera_attribute = nullptr;
	this->image_processor_attribute = nullptr;
	this->attributes = "Unknown";
}

Configuration::Configuration(std::string json) {
//	LOG(INFO) << "Start JSON Parser";
	this->attributes = json;
	JsonParser jp;
//	LOG(INFO) << "Start JSON Parser 2";
	std::shared_ptr<AttributeMap> property_map = jp.parse(json);
//	LOG(INFO) << "end JSON Parser";
	this->camera_attribute =  std::static_pointer_cast<CameraAttribute>( (*property_map)["camera"] );
	this->image_processor_attribute = std::static_pointer_cast<ImageProcessorAttribute>( (*property_map)["image_processors"] );

	//	std::cout<<"============== configuration =============="<<std::endl;
	//	std::cout<<"camera name:"<< this->camera_attribute->getName() <<std::endl;
	//	std::cout<<"Image Processor name:"<<this->image_processor_attribute->getName()<<std::endl;
	//	std::cout<<"Image Processor size:"<<this->image_processor_attribute->getImageProcessorAttributeVector().size()<<std::endl;
	std::vector< std::shared_ptr<ImageProcessorAttribute> > ipp =
			this->image_processor_attribute->getImageProcessorAttributeVector();
	//	for (std::vector<ImageProcessorAttribute*>::size_type i = 0; i < ipp.size(); ++i){
	//		std::cout << "processor name: " << ipp[i]->getName() << std::endl;
	//	}
}

Configuration::~Configuration() {

}

std::shared_ptr<CameraAttribute> Configuration::getCameraAttribute() const {
	return camera_attribute;
}

std::shared_ptr<ImageProcessorAttribute> Configuration::getImageProcessorAttribute() const {
	return image_processor_attribute;
}

std::string Configuration::getAttributes() const {
	return attributes;
}

} /* namespace nokkhum */
