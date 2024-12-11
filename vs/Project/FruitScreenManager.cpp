#include "FruitScreenManager.h"


Engine::FruitScreenManager::FruitScreenManager(Setting* setting) :Engine::Game(setting) {
	setting->windowTitle = "FruitCatch";
}

Engine::FruitScreenManager::~FruitScreenManager() {
	

}
void Engine::FruitScreenManager::Init() {
	//music = (new Music("Rosolanc.ogg"))->SetVolume(70)->Play(true);

	inputManager/*->AddInputMapping("next", SDLK_s)
		->AddInputMapping("prev", SDLK_w)*/
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("press", SDLK_RETURN);
	/*->AddInputMapping("press", SDLK_k);*/ //remove input mapping
	//Engine::ScreenManager::GetInstance(this)->AddScreen("Fruit", new FruitCatch());
	Engine::ScreenManager::GetInstance(this)->AddScreen("FruitCatch", new FruitCatch())
		->AddScreen("FruitSongMenu", new FruitSongMenu())
		->AddScreen("FruitCatch2", new FruitCatch2())
		->AddScreen("FruitScoringPage", new FruitScoringPage())
		->AddScreen("FruitMainMenu", new FruitMainMenu())
		->SetCurrentScreen("FruitMainMenu");
	/*Engine:ScreenManager::GetInstance(this)->AddScreen("FruitCatch", new FruitCatch())
		->SetCurrentScreen("FruitCatch");*/

}

void Engine::FruitScreenManager::Update() {
	Engine::ScreenManager::GetInstance(this)->Update();

}

void Engine::FruitScreenManager::Render() {
	Engine::ScreenManager::GetInstance(this)->Draw();
}
