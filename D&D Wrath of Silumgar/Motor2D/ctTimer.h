#ifndef __ctTIMER_H__
#define __ctTIMER_H__

#include "ctDefs.h"

class ctTimer
{
public:

	// Constructor
	ctTimer();

	void Start();
	void Stop();
	void Continue();
	void SetStartTime(uint32 time);
	uint32 Read() const;
	float ReadSec() const;


private:
	bool	running = true;
	uint32	started_at = 0;
	uint32	stopped_at = 0;
};

#endif //__ctTIMER_H__