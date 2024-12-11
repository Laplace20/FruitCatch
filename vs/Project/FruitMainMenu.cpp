#include "FruitMainMenu.h"
Engine::FruitMainMenu::FruitMainMenu()
{
	text = NULL;
}
void Engine::FruitMainMenu::Init()
{
	//set Background Sprite
	Texture* bgTexture = new Texture("b0.png");//
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	
	

	// Create a Texture
	Texture* texture = new Texture("buttons2.png");
	//Texture* texture2 = new Texture("pButton.png");

	// Create Sprites
	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(2)->SetNumYFrames(2)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 1)
		->SetScale(1.5f)
		->AddAnimation("press", 1, 1)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(2)->SetNumYFrames(2)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 2, 3)
		->SetScale(1.5f)
		->AddAnimation("press", 3, 3)->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2 ) - 520,
		410);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2) - 520,
		290);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Fruit Catch")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 650, game->GetSettings()->screenHeight - 290.0f)->SetColor(235, 229, 52);

	// Create Text
	text2 = (new Text("Cyberpunks Italic.ttf", 98, game->GetDefaultTextShader()))
		->SetText("Fruit Catch")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 638, game->GetSettings()->screenHeight - 290.0f)
		->SetColor(18, 18, 74);


	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

	//Add Music
	musicMain = (new Music("lofiMain.ogg"))->SetVolume(70);

	//for (int i = 1; i <= 2; i++) {
	//	AddToLayer(backgrounds, "bg0" + to_string(i) + ".png");
	//}
	//for (int i = 3; i <= 4; i++) {
	//	AddToLayer(middlegrounds, "bg0" + to_string(i) + ".png");
	//}
	//for (int i = 5; i <= 5; i++) {
	//	AddToLayer(foregrounds, "bg0" + to_string(i) + ".png");
	//}
	AddToLayer(backgrounds, "bg0.png");
	AddToLayer(middlegrounds, "bg1.png");
	AddToLayer(middlegrounds2, "bg2.png");
	AddToLayer(foregrounds, "bg3.png");
	AddToLayer(front, "bg4.png");

	offset = 2;




}


void Engine::FruitMainMenu::Update()
{

	// Set background
	//game->SetBackgroundColor(52, 155, 235);


	//State when game is running
	if (gstate == GameState::RUNNING) {

		if (musicMain->IsPlaying() == false)
		{
			musicMain->Play(true);
			musicMain->IsPlaying() == true;

		}
		if (game->GetInputManager()->IsKeyReleased("next")) {
			// Set previous button to normal state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			// Next Button
			currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
			// Set current button to hover state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}

		if (game->GetInputManager()->IsKeyReleased("prev")) {
			// Set previous button to normal state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			// Prev Button
			currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
			// Set current button to hover state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}

		if (game->GetInputManager()->IsKeyReleased("press")) {
			// Set current button to press state
			Button* b = buttons[currentButtonIndex];
			b->SetButtonState(Engine::ButtonState::PRESS);
			// If play button then go to InGame, exit button then exit
			if ("play" == b->GetButtonName()) {
				ScreenManager::GetInstance(game)->SetCurrentScreen("FruitSongMenu");
				musicMain->Stop();
			}
			else if ("exit" == b->GetButtonName()) {
				game->SetState(Engine::State::EXIT);
			}
		}

		// Update All buttons
		for (Button* b : buttons) {
			b->Update(game->GetGameTime());
		}

		
	}

	
	MoveLayer(backgrounds, 0.003f);
	MoveLayer(middlegrounds, 0.01f);
	//MoveLayerDown(rainz, 0.5f);
	MoveLayer(middlegrounds2, 0.003f);
	MoveLayer(foregrounds, 0.09f);
	MoveLayer(front, 0.2f);



}

void Engine::FruitMainMenu::Draw()
{
	backgroundSprite->Draw();
	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
	DrawLayer(front);
	//rain->Draw();
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
	text2->Draw();
}

#pragma region Parallax Functions

void Engine::FruitMainMenu::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s5 : bg) {
		if (s5->GetPosition().x < -game->GetSettings()->screenWidth + offset) {
			s5->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
		}
		s5->SetPosition(s5->GetPosition().x - speed * game->GetGameTime(), s5->GetPosition().y);
		s5->Update(game->GetGameTime());
	}
}

void Engine::FruitMainMenu::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s5 : bg) {
		s5->Draw();
	}
}

void Engine::FruitMainMenu::AddToLayer(vector<Sprite*>& bg, string name)
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
void Engine::FruitMainMenu::MoveLayerDown(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s : bg) {
		if (s->GetPosition().y < -game->GetSettings()->screenHeight + offset) {
			s->SetPosition(0, game->GetSettings()->screenHeight + offset - 1);
		}
		s->SetPosition(s->GetPosition().x, s->GetPosition().y - speed * game->GetGameTime());
		s->Update(game->GetGameTime());
	}
}

void Engine::FruitMainMenu::DrawLayerDown(vector<Sprite*>& bg)
{
	for (Sprite* s : bg) {
		s->Draw();
	}
}

void Engine::FruitMainMenu::AddToLayerDown(vector<Sprite*>& bg, string name)
{
	Texture* texture = new Texture(name);

	Sprite* s = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight + offset);
	bg.push_back(s);

	Sprite* s2 = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s2->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight + offset)->SetPosition(0, game->GetSettings()->screenHeight + offset - 1);
	bg.push_back(s2);
}


