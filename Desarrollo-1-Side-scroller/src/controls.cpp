#include "include/raylib.h"

#include "controls.h"
#include "game.h"

namespace Juego
{
	static Rectangle atras;

	void ControlsUpdate()
	{
		ControlsDraw();
		mousePoint = GetMousePosition();

		atras.x = 20;
		atras.y = GetScreenHeight() - atras.height - 25;
		atras.height = 50;
		atras.width = 200;

		if (CheckCollisionPointRec(mousePoint, atras))
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
		ClearBackground(RAYWHITE);

		DrawRectangle(atras.x, atras.y, atras.width, atras.height, MAROON);

		DrawText("ATRAS", atras.x + atras.width / 2 - MeasureText("ATRAS", 20) / 2, atras.y + 18, 20, WHITE);

		DrawText("CONTROLES", 20, 80, 40, MAROON);

		DrawText("Player 1", 20, 140, 20, MAROON);
		DrawText("Espacio para hacer que el jugador suba", 20, 160, 20, LIGHTGRAY);

		DrawText("Player 2", 20, 200, 20, MAROON);
		DrawText("W para hacer que el jugador suba", 20, 220, 20, LIGHTGRAY);
		
		DrawText("P para pausar", 20, 260, 20, LIGHTGRAY);
		DrawText("M para mutear", 20, 280, 20, LIGHTGRAY);
	
		EndDrawing();
	}
}