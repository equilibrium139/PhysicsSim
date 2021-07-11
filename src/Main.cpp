#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <optional>

bool InitSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL.\n";
		return false;
	}

	if (int flags = IMG_INIT_PNG; (IMG_Init(flags) & flags) != flags) {
		std::cerr << "Error initializing SDL_image.\n";
		std::cerr << IMG_GetError() << '\n';
		return false;
	}

	return true;
}

void QuitSDL() {
	IMG_Quit();
	SDL_Quit();
}

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float v[3];
	};
};

int main(int argc, char *argv[])
{	
	Vec3 vec;
	vec.x = 1;
	std::cout << vec.x << '\n';
	
	if (!InitSDL()) {
        std::cerr << "Failed to initialize SDL\n";
		return -1;
	}

	constexpr int width = 1280;
	constexpr int height = 720;

	auto sdlWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
	if (!sdlWindow) {
		std::cerr << "Error creating SDL window.\n";
		return -1;
	}

	auto renderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer.\n";
		return -1;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

    std::cout << "Hello, CMake\n"; 

    return EXIT_SUCCESS;
}