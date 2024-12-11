#ifndef FRUITSCORINGPAGE_H
#define FRUITSCORINGPAGE_H
#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "FruitCatch.h"
#include "FruitCatch2.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class FruitScoringPage :
		public Engine::Screen
	{
	public:
		FruitScoringPage();
		void Init();
		void Update();
		void Draw();
	private:
		vector<Button*> buttons;
		Text* text;
		Text* text2;
		Text* teks;
		Text* teks2;
		int currentButtonIndex = 0;
		Engine::Sprite* calicoSprite = NULL;

		Engine::Sprite* backgroundSprite = NULL;
		vector<Sprite*> backgrounds, middlegrounds, middlegrounds2, foregrounds, front;

		void MoveLayer(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		float offset = 4;

	};

}

#endif // !FRUITSCORINGPAGE_H
