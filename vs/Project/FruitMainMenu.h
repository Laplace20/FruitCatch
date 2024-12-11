#ifndef FRUITMAINMENU_H
#define FRUITMAINMENU_H
#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"
namespace Engine {
	class FruitMainMenu :
		public Engine::Screen
	{
	public:
		enum class GameState
		{
			RUNNING,
			RESET,
			GAME_OVER
		};
		GameState gstate;

		FruitMainMenu();
		void Init();
		void Update();
		void Draw();
	private:
		vector<Button*> buttons;
		Text* text;
		Text* text2;
		int currentButtonIndex = 0;
		Engine::Sprite* backgroundSprite = NULL;
		Engine::Sprite* rain = NULL;
		Engine::Texture* bgTexture1 = NULL;
		Music* musicMain = NULL;


		vector<Sprite*> backgrounds, middlegrounds, middlegrounds2, rainz, foregrounds, front;

		void MoveLayer(vector<Sprite*>& bg, float speed);
		void MoveLayerDown(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void DrawLayerDown(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		void AddToLayerDown(vector<Sprite*>& bg, string name);
		float offset = 4;
	};
}

#endif 

