#include <iostream>
#include <SDL2/SDL.h>

const int screen_width = 900;
const int screen_height = 700;

// Player class
class player {
	public:
		int x = screen_width/2;
		int y = screen_height-40;

		static const int width = 100;
		static const int height = 20;

		int vx;
		static const int vel = 2;

		void handleEvents(SDL_Event& e);
		void move();
		void render(SDL_Renderer* renderer);
};

void player::handleEvents(SDL_Event& e) {
	vx = 0;
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				vx -= vel;
				break;

			case SDLK_RIGHT:
				vx += vel;
				break;
		}
	}
}

void player::move() {
	x += vx;

	if (x <= 0 || x >= screen_width-width)
		x -= vx;
}

void player::render(SDL_Renderer* renderer) {
	SDL_Rect rect = {x,y,width,height};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

// Ball class
class ball {
	public:
		ball();

		void move(player player);
		void collision(player player);
		void render(SDL_Renderer* renderer);

		bool lost = false;

	private:
		int x = screen_width/2;
		int y = 60;
		static const int dim = 30;

		int vx;
		int vy;
		static const int vel = 1;
};

ball::ball() {
	vx = vel;
	vy = vel;
}

void ball::move(player player) {
	bool update_score = false;

	x += vx;
	y += vy;

	if (x <= 0 || x >= screen_width-dim)
		vx *= -1;

	if (y <= 0)
		vy *= -1;

	if (y >= screen_height-dim)
		lost = true;

	if (x + dim > player.x && x < player.x + player.width && y + dim > player.y)
		vy *= -1;
}

void ball::render(SDL_Renderer* renderer) {
	SDL_Rect rect = {x,y,dim,dim};
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
			screen_width,
			screen_height,
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
	player player;
	ball ball;

	SDL_Event e;
	bool run = true;
	while (run) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				run = false;
			}
			player.handleEvents(e);
		}
		player.move();
		ball.move(player);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		player.render(renderer);
		ball.render(renderer);

		SDL_RenderPresent(renderer);

		if (ball.lost) {
			run = false;
			printf("YOU LOST !!");

			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}

	// Destroy window and quit
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
