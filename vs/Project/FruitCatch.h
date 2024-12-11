#ifndef FRUITCATCH_H
#define FRUITCATCH_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "Sound.h"
#include "Screen.h"
#include "Lesson09_Bullet.h"
#include "Lesson10_Platform.h"
#include "FruitScreenManager.h"

namespace Engine {
    class FruitCatch : public Engine::Screen {
    public:
        enum class GameState
        {
            RUNNING,
            RESET,
            GAME_OVER,
            FINISH,
            PAUSED
        };
        GameState gstate;
        FruitCatch();
        ~FruitCatch();
        void Init();
        void Update();
        void Draw();

    private:
        Engine::Sprite* calicoSprite = NULL;

        void ResetVariabel();
        // Character sprite
        Engine::Texture* texture = NULL;
        Engine::Sprite* sprite = NULL;
        Engine::Texture* wallpapertt = NULL;
        Engine::Sprite* wallpaperSprite = NULL;
        Text* gameOverText;
        Text* finishText;
        Text* totalScore;

        int scoreLappy;
        int fruitCounter;
        Text* scoreText = NULL;
        Text* scoreText2 = NULL;
        Text* FC = NULL;

        float duration;
        int bps;
        int previousBps;
        int consecutiveMisses;

        //Music n SFX
        Music* lappySong = NULL;
        Sound* fruitCaught = NULL;
        Sound* fruitMissed = NULL;

        // Fruits
        Engine::Texture* textureFruit = NULL;
        Engine::Texture* textureFruit1 = NULL;
        Engine::Texture* textureFruit2 = NULL;
        Engine::Texture* textureFruit3 = NULL;
        Engine::Texture* textureFruit4 = NULL;
        Engine::Texture* textureFruit5 = NULL;
        Engine::Texture* textureFruit6 = NULL;
        Engine::Texture* textureFruit7 = NULL;
        Engine::Texture* textureFruit8 = NULL;
        Engine::Texture* textureFruit9 = NULL;
        Engine::Texture* textureFruit10 = NULL;
        Engine::Texture* textureFruit11 = NULL;
        std::vector<Engine::Sprite*> fruits; // List of fruits

        // Timing and movement
        float timeInterval = 0.0f;
        bool jump = false, toRight = true;

        // Bounding box for movement limits
        float boundingBoxLeft;
        float boundingBoxRight;

        // Bounding boxes
        struct BoundingBox {
            float x, y, width, height;
        };
        BoundingBox leftBox;
        BoundingBox middleBox;
        BoundingBox rightBox;
        BoundingBox miss;

        // Utility
        bool debug = false;

        // Animation management
        float animTimer = 0.2f; // Timer for animations
        bool isAnimating = false; // Prevent animation interruption

        void UpdateBoundingBoxes(); // Updates the bounding boxes
        void SpawnFruit();          // Spawns new fruits
        void CheckCollision();      // Checks collision with fruits

        int maxFruits = 1; // Maximum number of fruits allowed to be on screen
        int currentFruitCount = 0; // Counter for the current number of fruits on screen

        float animStartTime = 0.0f; // Records when the animation starts
        bool isAnimationPlaying = false; // Tracks if an animation is active

    };
}

#endif