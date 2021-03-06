/*
 * command_parser.cpp
 *
 *  Created on: Oct 6, 2011
 *      Author: boatkrap
 */

#include "command_parser.hpp"
#include <glog/logging.h>
namespace nokkhum {

CommandParser::CommandParser() {
	// TODO Auto-generated constructor stub

}

CommandParser::~CommandParser() {
	// TODO Auto-generated destructor stub
}

bool CommandParser::paseCommand(std::string json) {
    Json::Reader read;
	bool result = read.parse(json, value);
	//std::cout << "result = " << result << std::endl;
	return result;

}

std::string CommandParser::getCommand() {
	return value["action"].asString();
}

std::string CommandParser::getProcessorAttribute() {
	Json::FastWriter writer;
	return writer.write(value["attributes"]);
}
std::string CommandParser::getProcessorId(){
	return value["processor_id"].asString();
}
} /* namespace nokkhum */
