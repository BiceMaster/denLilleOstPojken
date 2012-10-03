
//#define USE_DIRECTX

#include <IOContext.h>
#include <Game.h>

#ifdef _WIN32

#ifdef USE_DIRECTX

// DirectX Windows
#include <DxContext.h>
#include <WinTimer.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context = new DxContext(hInstance, 400, 400);
	
	context->setWindowSize(800, 600);

	context->setWindowPosition(50, 250);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new WinTimer();

	Game* game = new Game(timer, context);

	game->run();
	
	delete timer;
	delete context;
	delete game;
	return 0;
}
#else

// OpenGl Windows
#include <GlContext.h>
#include <WinTimer.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	IOContext* context = new GlContext(400, 400);

	context->setWindowSize(800, 600);

	context->setWindowPosition(50, 250);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Timer* timer = new WinTimer();

	Game* game = new Game(timer, context);

	game->run();


	delete timer;
	delete context;
	delete game;
	return 0;
}
	#endif
#else

// OpenGl Linux
#include <GlContext.h>
#include <LinTimer.h>

int main(int argc, char** argv)
{
	cout<<"Running Linux Build..."<<endl;
	Timer* timer = new LinTimer();
	/*
	timer->start();
	for (int i=0;i<100000;i++)
	{
		timer->tick();
		cout<<"dt: "<<timer->getDeltaTime()<<endl;
		cout<<"elapsed: "<<timer->getElapsedTime()<<endl;
	}
	timer->stop();*/
	
	
	IOContext* context = new GlContext(400, 400);

	context->setWindowSize(800, 600);

	context->setWindowPosition(50, 250);

	if (!context->isInitialized())
	{
		delete context;
		return 1;
	}

	Game* game = new Game(timer, context);

	game->run();


	delete timer;
	delete context;
	delete game;
	return 0;
}

#endif
