#include <rt2d/core.h>
#include "wolfenstein.h"

int main( void )
{
	Core core;

	Wolfenstein* wolfenstein = new Wolfenstein();
	while(wolfenstein->isRunning()) {
		core.run(wolfenstein);
		core.showFrameRate(5);
	}
	//core.cleanup();
	delete wolfenstein;
	return 0;
}
