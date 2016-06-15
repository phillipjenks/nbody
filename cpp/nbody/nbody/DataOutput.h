
#ifndef __DATAOUTPUT_H_
#define __DATAOUTPUT_H_

#include "SimBody.h"

class DataOutput
{
public:

	bool init() const;
	void dumpOutput(double time, const VecBody& bodies);

private:

	int dumpNumber = 0;
};

#endif

