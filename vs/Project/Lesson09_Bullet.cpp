#include "Lesson09_Bullet.h"

Engine::Lesson09_Bullet::Lesson09_Bullet(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Bullets Spawn";
}

Engine::Lesson09_Bullet::~Lesson09_Bullet()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson09_Bullet::Init()
{
	// Add a monster player
	texture = new Texture("Yuzu.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(3)->SetNumYFrames(1)
		->AddAnimation("yes", 1, 1)
		->AddAnimation("idle", 0, 0)
		->AddAnimation("miss", 2, 2)
		->PlayAnim("idle")
		->SetScale(0.01)
		->SetPosition(0,0)
		->SetAnimationDuration(90);

	// Add input mapping 
	inputManager->AddInputMapping("Run Right", SDLK_RIGHT)
		->AddInputMapping("Run Left", SDLK_LEFT)
		->AddInputMapping("Jump", SDLK_UP)
		->AddInputMapping("Attack", SDLK_x)
		->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A)
		->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X)
		->AddInputMapping("Quit", SDLK_ESCAPE)
		->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);

	SetBackgroundColor(65, 180, 242);
	// Generate Center Background
	Texture* platformTexture = new Texture("CenterBack.png");
	vec2 start = vec2(200, 90);
	for (int i = 0; i < 8; i++) {
		Sprite* platformSprite = new Sprite(platformTexture, defaultSpriteShader, defaultQuad);
		platformSprite->SetSize(150, 32)->SetPosition(start.x + i * 210, start.y + i * 60);
		platformSprite->SetBoundingBoxSize(platformSprite->GetScaleWidth() - (16 * platformSprite->GetScale()), platformSprite->GetScaleHeight());
		platforms.push_back(platformSprite);
	}
}

void Engine::Lesson09_Bullet::Update()
{
	timeInterval += GetGameTime();

	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	sprite->PlayAnim("idle");

	// Move monster sprite using keyboard
	vec2 oldMonsterPos = sprite->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		x += 0.2f * GetGameTime();
		sprite->PlayAnim("run")->SetFlipHorizontal(false);
		toRight = true;
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		x -= 0.2f * GetGameTime();
		sprite->PlayAnim("run")->SetFlipHorizontal(true);
		toRight = false;
	}

	// Update monster sprite's position and animation
	sprite->SetPosition(x, y)->Update(GetGameTime());
}



void Engine::Lesson09_Bullet::Render()
{

	sprite->Draw();

}



