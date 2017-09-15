/*
 * privateCloud.h
 *
 *  Created on: Sep 11, 2017
 *      Author: pgopanap
 */
#include "common.hpp"
#ifndef SRC_CPP_PRIVATECLOUD_H_
#define SRC_CPP_PRIVATECLOUD_H_

class privateCloud {
public:
	privateCloud();
	virtual ~privateCloud();
};

class cloud {
public:
	void print() {
		cout << "This is " << name << " class" << endl;
	}
	cloud() {
		name = __func__;
	}
private:
	const char *name;

};

class privateCloud: public cloud {
public:
	void print() {
		cout << "This is " << name << " class" << endl;
	}
	privateCloud() {
		name = __func__;
	}
private:
	const char *name;
};


#endif /* SRC_CPP_PRIVATECLOUD_H_ */
