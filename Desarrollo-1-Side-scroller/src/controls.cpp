#include "include/raylib.h"

#include "controls.h"
#include "game.h"



namespace Juego
{
	static Vector2 mousePoint;
	static Rectangle rec1;

	void ControlsUpdate()
	{
		ControlsDraw();
		mousePoint = GetMousePosition();

		rec1.x = 25;
		rec1.y = 25;
		rec1.height = 50;
		rec1.width = 100;

		if (CheckCollisionPointRec(mousePoint, rec1))
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

		DrawRectangle(rec1.x, rec1.y, rec1.width, rec1.height, BLACK);

		ClearBackground(RAYWHITE);
		DrawText("Espacio para hacer que el jugador suba", 20, 200, 20, BLACK);
		DrawText("P para pausar", 20, 220, 20, BLACK);
		DrawText("M para mutear", 20, 220, 20, BLACK);

		DrawText("atras", rec1.x + 18, rec1.y + 10, 20, WHITE);

		
		EndDrawing();
	}
}