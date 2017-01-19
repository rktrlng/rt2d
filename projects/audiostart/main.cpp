#include <rt2d/core.h>

#include "myscene.h"

int main( void )
{
	Core core;

	MyScene* myscene = new MyScene();
	while(myscene->isRunning()) {
		core.run(myscene);
		core.showFrameRate(5);
	}
	//core.cleanup();
	delete myscene;

	return 0;
}
