#include "Viewport/InitViewport.h"

void InitViewport::init()
{
	//Create Viewport Singleton
	GestViewport::createSingleton();
}

void InitViewport::destroy()
{
	GestViewport::destroySingleton();
}
