#include <iostream>
#include <SDL2/SDL.h>

const int width = 800;
const int height = 600;

class obj {
	public:
		obj();
		void handleEvents(SDL_Event& e);
		void move();
		void render(SDL_Renderer* renderer);

	private:
		int x;
		int y;
		int vx;
		int vy;
		static const int width = 100;
		static const int height = 100;
		static const int vel = 2;
};

obj::obj() {
	x = 100;
	y = 100;
}

void obj::handleEvents(SDL_Event& e) {
	vx = 0;
	vy = 0;
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				vy -= vel;
				break;

			case SDLK_DOWN:
				vy += vel;
				break;

			case SDLK_LEFT:
				vx -= vel;
				break;

			case SDLK_RIGHT:
				vx += vel;
				break;
		}
	}
}

void obj::move() {
	x += vx;
	y += vy;
}

void obj::render(SDL_Renderer* renderer) {
	SDL_Rect rect = {x,y,width,height};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

int main() {
	// Init video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL could not initialize: " <<  SDL_GetError() << "\n";
		return 1;
	}

	// Create window pointer
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Pong Game", 
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN);

	// Check if window is created, report error if not
	if (window == NULL) {
		std::cout << "Window could not initialize: " <<  SDL_GetError() << "\n";
		return 1;
	}

	// Create surface
	SDL_Surface* surface = NULL;
	surface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);

	// Create renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// Main loop
	SDL_Event e;
	bool run = true;
	obj obj;
	while (run) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				run = false;
			}
			obj.handleEvents(e);
		}
		obj.move();

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		obj.render(renderer);

		SDL_RenderPresent(renderer);
	}

	// Destroy window and quit
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
