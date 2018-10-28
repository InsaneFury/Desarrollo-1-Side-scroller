#include "include/raylib.h"

#include "controls.h"
#include "game.h"

Vector2 Point;
Rectangle back;

namespace Juego
{

	void ControlsUpdate()
	{
		ControlsDraw();
		Point = GetMousePosition();

		back.x = 25;
		back.y = 25;
		back.height = 50;
		back.width = 100;

		if (CheckCollisionPointRec(Point, back))
		{

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Screens = menu;
			}
		}
	}


	void ControlsDraw()
	{
		BeginDrawing();

		DrawRectangle(back.x, back.y, back.width, back.height, BLACK);

		ClearBackground(RAYWHITE);
		DrawText("Espacio para hacer que el jugador suba", 20, 200, 20, BLACK);
		DrawText("P para pausar", 20, 220, 20, BLACK);
		DrawText("M para mutear", 20, 220, 20, BLACK);

		DrawText("atras", back.x + 18, back.y + 10, 20, WHITE);

		
		EndDrawing();
	}
}