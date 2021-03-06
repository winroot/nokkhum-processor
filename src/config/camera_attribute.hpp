/*
 * camera_attribute.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_ATTRIBUTE_HPP_
#define NOKKHUM_CAMERA_ATTRIBUTE_HPP_

#include <string>

#include "attribute.hpp"

namespace nokkhum {

class CameraAttribute : public Attribute {
public:
	CameraAttribute(std::string name, std::string model,
			std::string video_uri, std::string audio_uri, std::string image_uri,
			int width, int hight, int fps, std::string username, std::string password, std::string id);
	virtual ~CameraAttribute();

    int getFps() const;
    int getHeight() const;
    int getWidth() const;
    std::string getId() const;
    std::string getModel() const;
    std::string getName() const;
    std::string getVideoUri() const;
    std::string getAudioUri() const;
    std::string getImageUri() const;
    std::string getPassword() const;
    std::string getUsername() const;

    void setFps(int fps);
    void setHeight(int height);
    void setModel(std::string model);
    void setName(std::string name);
    void setVideoUri(std::string uri);
    void setAudioUri(std::string uri);
    void setImageUri(std::string uri);
    void setWidth(int width);

private:
    std::string name;
    std::string model;
    std::string video_uri;
    std::string audio_uri;
    std::string image_uri;
	int width;
	int height;
	int fps;
	std::string id;
	std::string username;
	std::string password;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_CAMERA_ATTRIBUTE_HPP_ */
