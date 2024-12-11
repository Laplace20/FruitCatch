#include "FruitCatch.h"

Engine::FruitCatch::FruitCatch()
{
}

Engine::FruitCatch::~FruitCatch()
{
	// Clean up
	delete texture;
	delete textureFruit;
	delete sprite;
	for (auto fruit : fruits) {
		delete fruit;

	}
}

void Engine::FruitCatch::Init()
{
	// Create Text
	gameOverText = (new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader()))
		->SetText("GAME OVER")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 220, game->GetSettings()->screenHeight - 200.0f)->SetColor(255, 0, 0);

	// Create Text
	finishText = (new Text("Cyberpunks Italic.ttf", 98, game->GetDefaultTextShader()))
		->SetText("FINISHED")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 220, game->GetSettings()->screenHeight - 200.0f)
		->SetColor(0, 255, 0);

	totalScore = (new Text("Cyberpunks Italic.ttf", 98, game->GetDefaultTextShader()))
		->SetText("FINISHED")->SetPosition((game->GetSettings()->screenWidth)/3 - 100, (game->GetSettings()->screenHeight)/2)
		->SetColor(255, 255, 255);


	// Initialize random seed
	std::srand(std::time(0));

	// Character
	wallpapertt = new Texture("ForLappy.png");
	wallpaperSprite = new Sprite(wallpapertt, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	wallpaperSprite->SetScale(1)
		->SetPosition(0.0f, 0.0f);
	texture = new Texture("Yuzu.png");
	sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	sprite->SetNumXFrames(3)->SetNumYFrames(1)
		->AddAnimation("idle", 0, 0)
		->AddAnimation("yes", 1, 1)
		->AddAnimation("miss", 2, 2)
		->PlayAnim("idle")
		->SetScale(0.5)
		->SetPosition(1420 / 2.0f, -120) // Center the sprite horizontally
		->SetAnimationDuration(90);




	// Fruit initiation
	textureFruit = new Texture("Apple_Green.png");
	textureFruit1 = new Texture("Apple_Yellow.png");
	textureFruit2 = new Texture("Banana.png");
	textureFruit3 = new Texture("Berry.png");
	textureFruit4 = new Texture("Cherry.png");
	textureFruit5 = new Texture("Lemon.png");
	textureFruit6 = new Texture("Lime.png");
	textureFruit7 = new Texture("Orange.png");
	textureFruit8 = new Texture("Pear.png");
	textureFruit9 = new Texture("Plum.png");
	textureFruit10 = new Texture("Watermelon.png");

	//Score
	scoreLappy = 0;
	fruitCounter = 0;
	scoreText = new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader());
	scoreText->SetPosition(game->GetSettings()->screenWidth - 1820.0f, game->GetSettings()->screenHeight - 120.0f)->SetColor(235, 229, 52)->SetScale(0.85f);
	scoreText2 = new Text("Cyberpunks Italic.ttf", 100, game->GetDefaultTextShader());
	scoreText2->SetPosition(game->GetSettings()->screenWidth - 1816.0f, game->GetSettings()->screenHeight - 122.0f)->SetColor(18, 18, 74)->SetScale(0.81f);

	//Inisiasi Music n SFX
	lappySong = (new Music("lappy.ogg"))->SetVolume(70);


	// Add input mapping 
	game->GetInputManager()->AddInputMapping("Walk Right", SDLK_RIGHT)
		->AddInputMapping("Walk Left", SDLK_LEFT)
		->AddInputMapping("Run", SDLK_LSHIFT)
		->AddInputMapping("pinish", SDLK_g)
		->AddInputMapping("restart", SDLK_r)
		->AddInputMapping("goToSong", SDLK_BACKSPACE)
		->AddInputMapping("Quit", SDLK_ESCAPE);

	game->SetBackgroundColor(255, 255, 255);

	// Set bounding box dimensions
	boundingBoxLeft = 250;
	boundingBoxRight = 1920 - 250; // Screen width - 40px margin

	// Character bounding boxes
	UpdateBoundingBoxes();

	// Spawn an initial fruit
	SpawnFruit();
}


void Engine::FruitCatch::Update()
{

	game->selectedScreen = 1;

	if (gstate == GameState::RUNNING) {

		if (game->GetInputManager()->IsKeyPressed("pinish")) {
			gstate = GameState::FINISH;
		}
		if (duration / 1000 >= 0.62f) {
			if (lappySong->IsPlaying() == false)
			{
				lappySong->Play(false);
				lappySong->IsPlaying() == true;

			}
		}
		if (consecutiveMisses > 5) {
			std::cout << "Game Over!" << std::endl;
			gstate = GameState::GAME_OVER;
			lappySong->Stop();
		}

		timeInterval += game->GetGameTime();
		duration += game->GetGameTime();
		//Score
		scoreText->SetText("Score: " + std::to_string(game->scoreLappy));
		scoreText2->SetText("Score: " + std::to_string(game->scoreLappy));


		//1 beat = 1 / 2.6 of a second
		bps = (duration / 1000) * 3.89f;

		// Obstacle pattern every phase of the song based on seconds
		if (duration / 1000 < 44)
		{
			if (floor(bps) > previousBps)
			{
				previousBps = floor(bps);  // Update the previous BPS value

				if (previousBps % 2 == 0)
				{
					SpawnFruit();
					fruitCounter++;
				}

			}
		}

		else if (duration / 1000 > 45 && duration / 1000 < 59)
		{
			if (floor(bps) > previousBps)
			{
				previousBps = floor(bps);  // Update the previous BPS value

				if (previousBps % 1 == 0)
				{
					SpawnFruit();
					fruitCounter++;
				}

			}
		}

		else if (duration / 1000 > 59 && duration / 1000 < 88)
		{
			if (floor(bps) > previousBps)
			{
				previousBps = floor(bps);  // Update the previous BPS value

				if (previousBps % 3 == 0)
				{
					SpawnFruit();
					fruitCounter++;
				}

			}
		}

		else if (duration / 1000 > 88 && duration / 1000 < 120)
		{
			if (floor(bps) > previousBps)
			{
				previousBps = floor(bps);  // Update the previous BPS value

				if (previousBps % 2 == 0)
				{
					SpawnFruit();
					fruitCounter++;
				}

			}
		}
		else if (duration / 1000 > 121) {
			gstate = GameState::FINISH;
			lappySong->Stop();
		}


		// If user presses "Quit" key, exit
		if (game->GetInputManager()->IsKeyReleased("Quit")) {
			game->SetState(Engine::State::EXIT);
			return;
		}

		//Character movement and animation
		vec2 oldMonsterPos = sprite->GetPosition();
		float x = oldMonsterPos.x, y = oldMonsterPos.y;

		float speedMultiplier = 1.0f; // Base movement speed
		bool isMoving = false; // Track if the player is moving
		if (game->GetInputManager()->IsKeyPressed("Run")) {
			speedMultiplier = 1.8f; // Increase speed when "Run" is pressed
		}

		if (game->GetInputManager()->IsKeyPressed("Walk Right")) {
			x += 1.0f * game->GetGameTime() * speedMultiplier;
			sprite->PlayAnim("run")->SetFlipHorizontal(false);
			toRight = true;
		}

		if (game->GetInputManager()->IsKeyPressed("Walk Left")) {
			x -= 1.0f * game->GetGameTime() * speedMultiplier;
			sprite->PlayAnim("run")->SetFlipHorizontal(true);
			toRight = false;
		}


		// Clamp character
		if (x < boundingBoxLeft) {
			x = boundingBoxLeft;
		}
		if (x > boundingBoxRight - sprite->GetScaleWidth()) {
			x = boundingBoxRight - sprite->GetScaleWidth();
		}

		// Update monster sprite's position and animation
		sprite->SetPosition(x, y)->Update(game->GetGameTime());

		UpdateBoundingBoxes();



		// Update fruits
		for (auto& fruit : fruits) {
			vec2 fruitPos = fruit->GetPosition();
			fruitPos.y -= 1.0f * game->GetGameTime(); // Move fruit down
			fruit->SetPosition(fruitPos.x, fruitPos.y)->Update(game->GetGameTime());
		}



		// Check for collisions
		CheckCollision();

	}else if (gstate == GameState::FINISH) {
		totalScore->SetText("Your Score : " + std::to_string(game->scoreLappy));
		if (game->GetInputManager()->IsKeyPressed("goToSong")) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("FruitSongMenu");
			game->scoreLappy = 0;
			gstate = GameState::RUNNING;
			fruits.clear();
			ResetVariabel();

		}
	}
	else if (gstate == GameState::GAME_OVER) {
		if (game->GetInputManager()->IsKeyPressed("restart")) {
			gstate = GameState::RUNNING;
			game->scoreLappy = 0;
			fruits.clear();
			ResetVariabel();
		}

	}
}


void Engine::FruitCatch::Draw()
{
	wallpaperSprite->Draw();

	
	
	if (gstate == GameState::GAME_OVER) {
		gameOverText->Draw();
	}
	if (gstate == GameState::FINISH) {
		finishText->Draw();
		totalScore->Draw();
	}
	if (gstate == GameState::RUNNING) {
		sprite->Draw();
		// Draw fruits
		for (auto fruit : fruits) {
			fruit->Draw();
		}

		// Debugging bounding boxes (optional)
		std::cout << "Bounding Boxes: ";
		std::cout << "Left: (" << leftBox.x << ", " << leftBox.y << ") ";
		std::cout << "Middle: (" << middleBox.x << ", " << middleBox.y << ") ";
		std::cout << "Right: (" << rightBox.x << ", " << rightBox.y << ")" << std::endl;
		scoreText->Draw();
		scoreText2->Draw();
	}
}
void Engine::FruitCatch::ResetVariabel() {




	duration = 0;
	bps = 0;
	previousBps = 0;
	consecutiveMisses = 0;





	// Timing and movement
	timeInterval = 0;
	jump = false;
	toRight = true;


	// Animation management
	animTimer = 0; // Timer for animations
	isAnimating = false; // Prevent animation interruption


	maxFruits = 1; // Maximum number of fruits allowed to be on screen
	currentFruitCount = 0; // Counter for the current number of fruits on screen

	animStartTime = 0.0f; // Records when the animation starts
	isAnimationPlaying = false; // Tracks if an animation is active

}

void Engine::FruitCatch::UpdateBoundingBoxes() {
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float width = sprite->GetScaleWidth();
	float height = sprite->GetScaleHeight();

	// Set up bounding boxes for scoring
	leftBox = { x, y, width * 0.325f, 280.0f };
	middleBox = { x + width * 0.325f, y, width * 0.35f, 280.0f };
	rightBox = { x + width * 0.675f, y, width * 0.325f, 280.0f };
	miss = { 0, -55, 1920, 1 };
}

void Engine::FruitCatch::SpawnFruit() {
	// Get the character's position and width
	float characterX = sprite->GetPosition().x;
	float characterWidth = sprite->GetScaleWidth();

	// Generate a random X position within the character's clamp range
	// Define fixed pixel range for X position
	float minX = 540;
	float maxX = 1280;

	// Generate a random X position within the defined range
	float spawnX = minX + (std::rand() % static_cast<int>(maxX - minX + 1));

	// Spawn fruits from the uppermost screen boundary (Y position = screen height)
	float spawnY = 1080;

	// Create an array of fruit textures
	Texture* fruitTextures[] = {
		textureFruit,
		textureFruit1,
		textureFruit2,
		textureFruit3,
		textureFruit4,
		textureFruit5,
		textureFruit6,
		textureFruit7,
		textureFruit8,
		textureFruit9,
		textureFruit10
	};

	// Select a random fruit texture
	int fruitIndex = std::rand() % 11;
	Texture* fruitTexture = fruitTextures[fruitIndex];

	// Create a new fruit
	Sprite* fruit = new Sprite(fruitTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	fruit->SetScale(2.5)
		->SetPosition(spawnX, spawnY);
	fruits.push_back(fruit);

	currentFruitCount++;
}

void Engine::FruitCatch::CheckCollision() {
	for (size_t i = 0; i < fruits.size(); ++i) {
		auto pos = fruits[i]->GetPosition();
		float fruitWidth = fruits[i]->GetScaleWidth();
		float fruitHeight = fruits[i]->GetScaleHeight();

		bool caught = false; // To track if a fruit was caught

		// Check collisions with bounding boxes
		if (pos.x < leftBox.x + leftBox.width && pos.x + fruitWidth > leftBox.x &&
			pos.y < leftBox.y + leftBox.height && pos.y + fruitHeight > leftBox.y) {
			int goodPoint = 50;
			game->scoreLappy += goodPoint;
			std::cout << "Good Catch (Left)!" << std::endl;
			sprite->PlayAnim("idle");  // Play "yes" animation when caught
			consecutiveMisses = 0;
			caught = true;
		}
		else if (pos.x < middleBox.x + middleBox.width && pos.x + fruitWidth > middleBox.x &&
			pos.y < middleBox.y + middleBox.height && pos.y + fruitHeight > middleBox.y) {
			int perfectPoint = 100;
			game->scoreLappy += perfectPoint;
			std::cout << "Perfect Catch (Middle)!" << std::endl;
			sprite->PlayAnim("yes");  // Play "yes" animation when caught
			consecutiveMisses = 0;
			caught = true;
		}
		else if (pos.x < rightBox.x + rightBox.width && pos.x + fruitWidth > rightBox.x &&
			pos.y < rightBox.y + rightBox.height && pos.y + fruitHeight > rightBox.y) {
			int goodPoint = 50;
			game->scoreLappy += goodPoint;
			std::cout << "Good Catch (Right)!" << std::endl;
			sprite->PlayAnim("idle");  // Play "yes" animation when caught
			consecutiveMisses = 0;
			caught = true;
		}

		else if (pos.y + fruitHeight > miss.y && pos.y < miss.y + miss.height) {
			sprite->PlayAnim("miss"); // Play "miss" animation when a fruit is missed
			consecutiveMisses++;
			delete fruits[i];
			fruits.erase(fruits.begin() + i);
			currentFruitCount--;

		}

		if (caught) {
			delete fruits[i];
			fruits.erase(fruits.begin() + i);
			currentFruitCount--;
			return; // Exit early to avoid accessing deleted fruit
		}

		if (consecutiveMisses > 5) {
			std::cout << "Game Over!" << std::endl;
			gstate = GameState::GAME_OVER;
			lappySong->Stop();
		}
	}
}