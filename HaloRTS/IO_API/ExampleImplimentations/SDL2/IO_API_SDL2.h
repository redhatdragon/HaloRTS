#pragma once

#pragma comment(lib, "x86/SDL2.lib");
#pragma comment(lib, "x86/SDL2main.lib");
#pragma comment(lib, "x86/SDL2_image.lib");


#include "../../IO_API.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <time.h>
#include <stdio.h>
#include <Windows.h>

struct SDL_Window *window;
struct SDL_Renderer *renderer;
const Uint8* keys;

float FPS;

void drawTexture(const void* texture, int x, int y, int w, int h) {
	struct SDL_Texture* t = texture;
	struct SDL_Rect r = { x, y, w, h };
	SDL_RenderCopy(renderer, t, NULL, &r);
}
void* getTexture(const char* fileName) {
	//struct *t = IMG_LoadTexture(renderer, fileName);  //This should be more optimized but fails in debug mode with magic number issue.
	struct SDL_Surface* s = IMG_Load(fileName);
	return SDL_CreateTextureFromSurface(renderer, s);
}
void releaseTexture(void* texture) {
	SDL_DestroyTexture(texture);
}

bool getKeyState(char k) {
	return keys[k+(SDL_SCANCODE_A - 'a')];
}

float getFPS() {
	return FPS;
}
void setFPS(uint32_t fps) {

}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Some window title", 60, 40, 1024, 768, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (IMG_Init(IMG_INIT_PNG) == 0)
		printf("Failed to initialize SDL_Image");
	printf("CPU cache line size: %d", SDL_GetCPUCacheLineSize());
	printf("\n");
	printf("CPU core count: %d", SDL_GetCPUCount());
	printf("\n");
	printf("System RAM: %d", SDL_GetSystemRAM());
	printf("\n");
	appStart();



	gameLoop:
	{
		clock_t startTime = clock();
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				goto quit;
		keys = SDL_GetKeyboardState(NULL);
		SDL_RenderClear(renderer);
		appLoop();

		SDL_RenderPresent(renderer);
		clock_t endTime = clock();
		clock_t differentialTime = endTime - startTime;
		if (differentialTime < 16) {
			SDL_Delay(16 - differentialTime);
			differentialTime = clock() - startTime;
		}
		FPS = (double)1000/((double)differentialTime);
	} goto gameLoop;

quit:
	appEnd();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}