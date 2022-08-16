#include <iostream>
#include <SDL2/SDL.h>

const int screen_width = 900;
const int screen_height = 700;

class rect_a {
	public:
		SDL_Rect rect;
		Uint8 color = 0x00;

		rect_a();
		void move();
		void render(SDL_Renderer* renderer);

	private:
		int x = screen_width/2-100;
		int y = screen_height/2-40;

		static const int width = 70;
		static const int height = 150;

		static const int vel = 1;
};

rect_a::rect_a() {
	rect = {x,y,width,height};
}

void rect_a::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
	color = 0x00;
}


class rect_b {
	public:
		SDL_Rect rect;
		int vx, vy;

		rect_b();
		void move();
		void render(SDL_Renderer* renderer);

	private:
		int x = 600;
		int y = 200;

		static const int width = 50;
		static const int height = 70;

		static const int vel = 1;
};

rect_b::rect_b() {
	rect = {x,y,width,height};
	vx = vel;
	vy = vel;
}

void rect_b::move() {
	rect.x += vx;
	rect.y += vy;

	if (rect.x <= 0 || rect.x >= screen_width-rect.w) {
		vx *= -1;
	}

	if (rect.y <= 0 || rect.y >= screen_height-rect.h) {
		vy *= -1;
	}
}

void rect_b::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

bool check_collision(SDL_Rect a, SDL_Rect b) {
	if (a.x + a.w >= b.x && a.x <= b.x + b.w && a.y + a.h >= b.y && a.y <= b.y + b.h)
		return true;
	return false;
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
	rect_a rect_a;
	rect_b rect_b;

	SDL_Event e;
	bool run = true;
	while (run) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				run = false;
			}
		}
		rect_b.move();

		if (check_collision(rect_a.rect, rect_b.rect)) {
			rect_a.color = 0xFF;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		rect_a.render(renderer);
		rect_b.render(renderer);

		SDL_RenderPresent(renderer);
	}

	// Destroy window and quit
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
