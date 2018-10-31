#ifndef over_H
#define over_H
#include "game.h"

namespace Juego
{
	extern int screenHeight;
	extern int screenWidth;
	extern int score;
	extern 	Vector2 mousePoint;
	extern bool gameOver;

	void OverUpdate();
	static void OverDraw();
}

#endif // !over_H
