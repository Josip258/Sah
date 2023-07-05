#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

SDL_Texture* loadTexture( std::string path , SDL_Renderer* gRenderer);