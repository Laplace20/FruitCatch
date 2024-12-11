#ifndef FRUITSONGMENU_H
#define FRUITSONGMENU_H
#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "FruitScreenManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class FruitSongMenu:
		public Engine::Screen
	{
	public:

		enum class GameState {
			RUNNING,
			RESET,
			GAME_OVER
		};
		GameState gstate;

		FruitSongMenu();
		void Init();
		void Update();
		void Draw();
	private:

		vector<Button*> buttons;
		Text* text;
		Text* text2;
		int currentButtonIndex = 0;

		Engine::Sprite* backgroundSprite = NULL;
		vector<Sprite*> backgrounds, middlegrounds, middlegrounds2, foregrounds, front;

		void MoveLayer(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		float offset = 4;

		Music* lappy = NULL;
		Music* megalovania = NULL;
	};

}

#endif // !FRUITSONGMENU_H
