#include "Graphics.h"

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
	if (sInstance == NULL)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = NULL;

	sInitialized = false;
}

bool Graphics::Initialised()
{
	return sInitialized;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
	{
		std::cout << "Image Load Error: " << path.c_str() << IMG_GetError() << std::endl;
		return false;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == NULL)
	{
		std::cout << "Texture Load Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex)
{
	SDL_RenderCopy(mRenderer, tex, NULL, NULL);
}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}

Graphics::Graphics()
{
	mBackBuffer = NULL;
	sInitialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Initialzation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (mWindow == NULL)
	{
		std::cout << "Window Creation Error:" << SDL_GetError() << std::endl;
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	{
		if (mRenderer == NULL)
			printf("Renderer Creation Error: %s\n", SDL_GetError());
			return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "Image Initialization Error:" << SDL_GetError() << std::endl;
		return false;
	}


	mBackBuffer = SDL_GetWindowSurface(mWindow);

	return true;
}



