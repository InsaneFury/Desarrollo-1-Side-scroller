#include "include/raylib.h"

#include "over.h"
#include "game.h"

namespace Juego
{

	static Rectangle menu_btn;
	static Rectangle retry_btn;

	void OverUpdate()
	{
		OverDraw();
		mousePoint = GetMousePosition();
		menu_btn.x = screenWidth / 2 - menu_btn.width/2;
		menu_btn.y = screenHeight / 2 + 50;
		menu_btn.height = 50;
		menu_btn.width = 100;

		retry_btn.x = screenWidth / 2 - menu_btn.width / 2;
		retry_btn.y = screenHeight / 2 + 110;
		retry_btn.height = 50;
		retry_btn.width = 100;

		if (CheckCollisionPointRec(mousePoint, menu_btn))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				InitGame();
				isMultiplayerEnabled = false;
				Screens = menu;
			}
		}
		if (CheckCollisionPointRec(mousePoint, retry_btn))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (isMultiplayerEnabled) {
					InitGame();
					isMultiplayerEnabled = true;
					Screens = game;
				}
				else {
					InitGame();
					Screens = game;
				}
			}
		}
	}

	void OverDraw()
	{
		BeginDrawing();

		ClearBackground(DARKGRAY);

		DrawRectangle(menu_btn.x, menu_btn.y, menu_btn.width, menu_btn.height, MAROON);
		DrawRectangle(retry_btn.x, retry_btn.y, retry_btn.width, retry_btn.height, MAROON);

		DrawText("SHARDS", screenWidth/ 2 - MeasureText("SHARDS",50)/2, screenHeight / 2 - 100, 50, MAROON);
		DrawText("PERDISTE", screenWidth / 2 - MeasureText("PERDISTE", 20) / 2, screenHeight / 2 - 50, 20, WHITE);
		DrawText("MENU", menu_btn.x + menu_btn.width / 2 - MeasureText("MENU", 18) / 2, menu_btn.y + 18, 18, WHITE);
		DrawText("RETRY", retry_btn.x + retry_btn.width / 2 - MeasureText("RETRY", 18) / 2, retry_btn.y + 18, 18, WHITE);
		DrawText(FormatText("%04i", score), GetScreenWidth()/2 - MeasureText("0000", 30) / 2, menu_btn.y - 50, 30, WHITE);
		DrawText("v1.1", 10, screenHeight - 10, 10, MAROON);

		EndDrawing();
	}

}