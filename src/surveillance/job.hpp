/*
 * job.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_JOB_HPP_
#define NOKKHUM_JOB_HPP_

#include <string>

namespace nokkhum {

class Job {
public:
	Job();
	Job(std::string name, bool running = false);
	virtual ~Job();

	virtual void start() = 0;
	virtual void stop();

	virtual void operator()();
    std::string getName() const;
    bool isRunning() const;

protected:
    std::string name;
	bool running;

};

}

#endif /* NOKKHUM_JOB_HPP_ */
