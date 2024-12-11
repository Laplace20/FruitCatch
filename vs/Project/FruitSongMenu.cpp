#include "FruitSongMenu.h"

Engine::FruitSongMenu::FruitSongMenu() {

}

void Engine::FruitSongMenu::Init() {
#pragma region Background Stuff
	//set Background Sprite
	Texture* bgTexture = new Texture("b0.png");//
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	AddToLayer(backgrounds, "bg0.png");
	AddToLayer(middlegrounds, "bg1.png");
	AddToLayer(middlegrounds2, "bg2.png");
	AddToLayer(foregrounds, "bg3.png");
	AddToLayer(front, "bg4.png");

	offset = 2;
#pragma endregion
#pragma region Inputs
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN)
		->AddInputMapping("Back", SDLK_BACKSPACE);
#pragma endregion

#pragma region lagu - lagu
	lappy = (new Music("lappy.ogg"))->SetVolume(70);
	megalovania = (new Music("megalovania.ogg"))->SetVolume(70);
#pragma endregion

#pragma region buttons & text
	Texture* texture = new Texture("songList.png");
	Texture* backText = new Texture("backButton.png");
	Sprite* song1 = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(2)->SetNumYFrames(2)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 1, 1)->SetAnimationDuration(400);
	Sprite* song2 = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(2)->SetNumYFrames(2)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 2, 3)
		->AddAnimation("press", 3, 3)->SetAnimationDuration(400);
	Sprite* backBut = (new Sprite(backText, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(2)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 0)->SetAnimationDuration(400);
	//Create Buttons
	Button* song1Button = new Button(song1, "lappyButton");
	song1Button->SetPosition((game->GetSettings()->screenWidth / 2) - (song1->GetScaleWidth() / 2),
		400);
	buttons.push_back(song1Button);

	Button* song2Button = new Button(song2, "megalovaniaButton");
	song2Button->SetPosition((game->GetSettings()->screenWidth / 2) - (song2->GetScaleWidth() / 2),
		250);
	buttons.push_back(song2Button);

	Button* backButton = new Button(backBut, "backButton");
	song2Button->SetPosition((game->GetSettings()->screenWidth / 2) - (song2->GetScaleWidth() / 2),
		250);
	buttons.push_back(backButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader()))
		->SetText("SONG LIST")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 220, game->GetSettings()->screenHeight - 200.0f)->SetColor(235, 229, 52);

	// Create Text
	text2 = (new Text("Cyberpunks Italic.ttf", 98, game->GetDefaultTextShader()))
		->SetText("SONG LIST")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 220, game->GetSettings()->screenHeight - 200.0f)
		->SetColor(18, 18, 74);
#pragma endregion


}

void Engine::FruitSongMenu::Update() {

	//State when game is running
	if (gstate == GameState::RUNNING) {

		//if (musicMain->IsPlaying() == false)
		//{
		//	musicMain->Play(true);
		//	musicMain->IsPlaying() == true;

		//}
		if (game->GetInputManager()->IsKeyReleased("next")) {
			// Set previous button to normal state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			// Next Button
			currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
			// Set current button to hover state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
			//get Button 
			Button* b = buttons[currentButtonIndex];
			if ("lappyButton" == b->GetButtonName()) {
				megalovania->Stop();
				megalovania->IsPlaying() == false;
				lappy->Play(true);
				lappy->IsPlaying() == true;

			}
			else if ("megalovaniaButton" == b->GetButtonName()) {


				lappy->Stop();
				lappy->IsPlaying() == false;
				megalovania->Play(true);
				megalovania->IsPlaying() == true;

			}

			else if ("backButton" == b->GetButtonName()) {
				lappy->Stop();
				megalovania->Stop();
			}



		}

		if (game->GetInputManager()->IsKeyReleased("prev")) {
			// Set previous button to normal state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
			// Prev Button
			currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
			// Set current button to hover state
			buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
			//get Button 
			Button* b = buttons[currentButtonIndex];
			if ("lappyButton" == b->GetButtonName()) {

				megalovania->Stop();
				megalovania->IsPlaying() == false;
				lappy->Play(true);
				lappy->IsPlaying() == true;

			}
			else if ("megalovaniaButton" == b->GetButtonName()) {
				lappy->Stop();
				lappy->IsPlaying() == false;
				megalovania->Play(true);
				megalovania->IsPlaying() == true;
			}
			else if ("backButton" == b->GetButtonName()) {
				lappy->Stop();
				megalovania->Stop();
			}
		}

		if (game->GetInputManager()->IsKeyReleased("press")) {
			// Set current button to press state
			Button* b = buttons[currentButtonIndex];
			b->SetButtonState(Engine::ButtonState::PRESS);
			// If play button then go to InGame, exit button then exit
			if ("lappyButton" == b->GetButtonName()) {
				ScreenManager::GetInstance(game)->SetCurrentScreen("FruitCatch");
				lappy->Stop();

			}
			else if ("megalovaniaButton" == b->GetButtonName()) {
				ScreenManager::GetInstance(game)->SetCurrentScreen("FruitCatch2");
				megalovania->Stop();
			}

			else if ("backButton" == b->GetButtonName()) {
				ScreenManager::GetInstance(game)->SetCurrentScreen("FruitMainMenu");
			}
		}

		// Update All buttons
		for (Button* b : buttons) {
			b->Update(game->GetGameTime());
		}


	}

#pragma region Move Backgrounds
	MoveLayer(backgrounds, 0.005f);
	MoveLayer(middlegrounds, 0.03f);
	MoveLayer(middlegrounds2, 0.05f);
	MoveLayer(foregrounds, 0.2f);
	MoveLayer(front, 0.4f);
#pragma endregion



	// If user presses "Back" key, Back to Main Menu
	/*if (game->GetInputManager()->IsKeyReleased("Back")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("FruitSongMenu");

	}*/

	//if (game->GetInputManager()->IsKeyReleased("next")) {
	//	// Set previous button to normal state
	//	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
	//	// Next Button
	//	currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
	//	// Set current button to hover state
	//	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	//}

	//if (game->GetInputManager()->IsKeyReleased("prev")) {
	//	// Set previous button to normal state
	//	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
	//	// Prev Button
	//	currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
	//	// Set current button to hover state
	//	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	//}

	//if (game->GetInputManager()->IsKeyReleased("press")) {
	//	// Set current button to press state
	//	Button* b = buttons[currentButtonIndex];
	//	b->SetButtonState(Engine::ButtonState::PRESS);
	//	// If play button then go to InGame, exit button then exit
	//	if ("lappy" == b->GetButtonName()) {
	//		ScreenManager::GetInstance(game)->SetCurrentScreen("FruitCatch");
	//	}
	//	else if ("exit" == b->GetButtonName()) {
	//		ScreenManager::GetInstance(game)->SetCurrentScreen("FruitCatch");
	//		//game->SetState(Engine::State::EXIT);
	//	}
	//}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}


}

void Engine::FruitSongMenu::Draw() {
	backgroundSprite->Draw();
	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
	DrawLayer(front);

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
	text2->Draw();

}

#pragma region Parallax Functions

void Engine::FruitSongMenu::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s5 : bg) {
		if (s5->GetPosition().x < -game->GetSettings()->screenWidth + offset) {
			s5->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
		}
		s5->SetPosition(s5->GetPosition().x - speed * game->GetGameTime(), s5->GetPosition().y);
		s5->Update(game->GetGameTime());
	}
}

void Engine::FruitSongMenu::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s5 : bg) {
		s5->Draw();
	}
}

void Engine::FruitSongMenu::AddToLayer(vector<Sprite*>& bg, string name)
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