#include "FruitScoringPage.h"
#include "FruitCatch.h"

Engine::FruitScoringPage::FruitScoringPage() {

}

void Engine::FruitScoringPage::Init() {

	//set Background Sprite
	Texture* bgTextureScore = new Texture("b0.png");//
	backgroundSprite = (new Sprite(bgTextureScore, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
#pragma region char sprite
	Texture* calico = new Texture("calicoSleep.png");
	calicoSprite = new Sprite(calico, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	calicoSprite->SetNumXFrames(5)->SetNumYFrames(3)
		->AddAnimation("idleCalico", 0, 11)
		->SetPosition(110, -110)
		->SetScale(10.0f)
		->SetAnimationDuration(100);

#pragma endregion

#pragma region input
	game->GetInputManager()->AddInputMapping("goToSongMenu", SDLK_SPACE);
#pragma endregion
#pragma region Background Stuff
	//set Background Sprite
	Texture* bgTexture = new Texture("b0.png");//
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	AddToLayer(backgrounds, "bg0.png");
	AddToLayer(middlegrounds, "bg1.png");
	AddToLayer(middlegrounds2, "bg2.png");
	AddToLayer(foregrounds, "bg3.png");
	AddToLayer(front, "bg4.png");

	//teks = new Text("RETROTECH.ttf", 100, game->GetDefaultSpriteShader());
	//teks->SetPosition(game->GetSettings()->screenWidth * 0.5f - 650, game->GetSettings()->screenHeight - 290.0f)->SetColor(235, 229, 52);
	teks = (new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader()))
		->SetPosition(game->GetSettings()->screenWidth * 0.5f - 650, game->GetSettings()->screenHeight - 290.0f)->SetColor(235, 229, 52);
	teks2 = (new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader()))
		->SetPosition(game->GetSettings()->screenWidth * 0.5f - 650, game->GetSettings()->screenHeight - 290.0f)->SetColor(235, 229, 52);


	offset = 2;
#pragma endregion
	

}

void Engine::FruitScoringPage::Update() {

	calicoSprite->PlayAnim("idleCalico");
	if (game->GetInputManager()->IsKeyReleased("goToSongMenu")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("FruitSongMenu");
		game->scoreLappy = 0;
		game->scoreMegalovania = 0;
	}

	if (game->selectedScreen == 1) {
		teks->SetText("Score Lappy : " + std::to_string(game->scoreLappy));
		teks2->SetText("");


	}
	else if (game->selectedScreen == 2) {
		teks2->SetText("Score Megalovania : " + std::to_string(game->scoreMegalovania));
		teks->SetText("");
		

	}
	

#pragma region Move Backgrounds
	MoveLayer(backgrounds, 0.005f);
	MoveLayer(middlegrounds, 0.03f);
	MoveLayer(middlegrounds2, 0.05f);
	MoveLayer(foregrounds, 0.2f);
	MoveLayer(front, 0.4f);
#pragma endregion

}

void Engine::FruitScoringPage::Draw() {
	
	backgroundSprite->Draw();
	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
	DrawLayer(front);
	calicoSprite->Draw();
	teks->Draw();
	teks2->Draw();
	
	/*if (game->scoreLappy > 0) {
		teks->Draw();
	}
	else if (game->scoreMegalovania > 0) {
		teks2->Draw();
	}*/
	
}
#pragma region Parallax Functions

void Engine::FruitScoringPage::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s5 : bg) {
		if (s5->GetPosition().x < -game->GetSettings()->screenWidth + offset) {
			s5->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
		}
		s5->SetPosition(s5->GetPosition().x - speed * game->GetGameTime(), s5->GetPosition().y);
		s5->Update(game->GetGameTime());
	}
}

void Engine::FruitScoringPage::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s5 : bg) {
		s5->Draw();
	}
}

void Engine::FruitScoringPage::AddToLayer(vector<Sprite*>& bg, string name)
{
	Texture* Ptexture = new Texture(name);

	Sprite* s5 = new Sprite(Ptexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s5->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight);
	bg.push_back(s5);

	Sprite* s2 = new Sprite(Ptexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s2->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight)->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
	bg.push_back(s2);
}

#pragma endregion

