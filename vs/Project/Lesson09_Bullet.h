#ifndef LESSON09_BULLET_H
#define LESSON09_BULLET_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Bullet.h"

namespace Engine {
	class Lesson09_Bullet :public Engine::Game
	{
	public:
		Lesson09_Bullet(Setting* setting);
		~Lesson09_Bullet();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL, *bulletTexture = NULL;
		Engine::Sprite* sprite = NULL;
		float timeInterval = 0;
		bool jump = false, toRight = true;
		Texture* dotTexture = NULL;
		vector<Sprite*> platforms;
		Sprite* monsterSprite = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		float yVelocity = 0, gravity = 0;
		bool debug = false;

	};
}

#endif

