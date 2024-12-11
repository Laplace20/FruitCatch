#ifndef FRUITSCREENMANAGER_H
#define FRUITSCREENMANAGER_H
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include "Input.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <SDL/SDL.h>
#include "Screen.h"
#include "ScreenManager.h"
#include "FruitCatch.h"
#include "FruitMainMenu.h"
#include "FruitSongMenu.h"
#include "FruitScoringPage.h"
#include "FruitCatch2.h"
#include "Turtle.h"
#include <vector>
#include "FruitScreenManager.h"
#include <stdio.h>
#include "Button.h"
namespace Engine {
	class FruitScreenManager :
		public Engine::Game
	{
	public:
		enum class GameState {
			RUNNING,
			RESET,
			GAME_OVER
		};
		GameState gstate;

		FruitScreenManager(Setting* setting);
		~FruitScreenManager();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		//virtual void restartGame();
		// void GenerateNewSprite();
	private:

		vector<Button*> buttons;
		int currentButtonIndex = 0;

		int score;
		int lastTime;
		int lastSpriteTime;

		Texture* dotTexture = NULL;
		vector<Sprite*> platforms;

		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		Text* text = NULL;
		Text* text2 = NULL;
		std::string died;

		Engine::Sprite* backgroundSprite = NULL;
		Engine::Texture* Ptexture = NULL;
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		Engine::Texture* texture2 = NULL;
		Engine::Sprite* sprite2 = NULL;

		Engine::Texture* tx_obstacle = NULL;
		Engine::Sprite* sp_obstacle = NULL;
		Engine::Sprite* sp_obstacle2 = NULL;



		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;

		Music* music = NULL;
		Sound* sound = NULL;
		Sound* deathSound = NULL;

		vector<Sprite*> backgrounds, middlegrounds, foregrounds, front;

		float offset = 4;

		bool gameOver = false;


	};
}



#endif 




