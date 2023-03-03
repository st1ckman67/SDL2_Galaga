#include "GameManager.h"

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;

	//Initialize Graphics
	mGraphics = Graphics::Instance();

	/*if (Graphics::Initialised())
		mQuit = true;*/

	mAssetMgr = AssetManager::Instance();


	//Initialize Timer
	mTimer = Timer::Instance();

	mTex = new Texture("SpriteSheet.png");
}

GameManager::~GameManager()
{
	Graphics::Release();		// Release the Graphics instance
	mGraphics = NULL;			// and set mGraphics to NULL

	AssetManager::Release();
	mAssetMgr = NULL;

	Timer::Release();
	mTimer = NULL;

	delete mTex;
	mTex = NULL;
}

void GameManager::Run()
{
	std::cout << mQuit << std::endl;
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
		{
			//std::cout << mTimer->DeltaTime() << std::endl;

			mGraphics->ClearBackBuffer();

			mTex->Render();

			mGraphics->Render();

			mTimer->Reset();
		}
	}
}


