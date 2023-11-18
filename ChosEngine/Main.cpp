#include "ChosEngine.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
#define ROTATE_SPEED 3.0f * 0.016f
#define MOVE_SPEED 3.0f * 0.016f

int main(int argc, char* args[])
{
	ChosEngine::Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, ROTATE_SPEED, MOVE_SPEED);
	return engine.Run();
}