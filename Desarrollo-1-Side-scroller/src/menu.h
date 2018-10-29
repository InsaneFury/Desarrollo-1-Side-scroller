#ifndef menu_H
#define menu_H
#include "game.h"

namespace Juego
{

	extern int screenHeight;
	extern int screenWidth; 
	extern 	Vector2 mousePoint;

	void MenuUpdate();
	static void  MenuDraw();
}
#endif // !menu_H
