#include <emscripten.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <stdbool.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static double lastNow;
static int iterationCount;
static int keyState;

void testLoop() {
	union SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			emscripten_log(EM_LOG_CONSOLE, "Key pressed in sdl polling loop: %c", event.key.keysym.sym);
			break;
		};
	}

	// do some small busy work
    double now = emscripten_get_now();
    double elapsedNow = now - (lastNow > 0.0 ? lastNow : now);
    double nowFrames = elapsedNow / (1000.0 / 60.0); // example frame count for info
	lastNow = now;
	iterationCount += 1;

	// emscripten_log(EM_LOG_CONSOLE, "elapsed frames: %f, iterationCount: %d, keyState enabled: %s", nowFrames, iterationCount, keyState ? "true" : "false");
}

EMSCRIPTEN_KEEPALIVE void setEventEnable(bool toggle) {
    keyState = toggle ? SDL_ENABLE : SDL_DISABLE;

    emscripten_log(EM_LOG_CONSOLE, "setting event enable keyState: %s", keyState ? "true" : "false");

    SDL_EventState(SDL_TEXTINPUT, keyState);
    SDL_EventState(SDL_KEYDOWN, keyState);
    SDL_EventState(SDL_KEYUP, keyState);
    SDL_EventState(SDL_MOUSEMOTION, keyState);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, keyState);
    SDL_EventState(SDL_MOUSEBUTTONUP, keyState);
}

int main() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO| SDL_INIT_TIMER | SDL_INIT_EVENTS);
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 240, 160, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	emscripten_set_main_loop(testLoop, 0, 0);
	return 0;
}
