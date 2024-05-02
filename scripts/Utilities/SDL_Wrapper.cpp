//
// Created by Logan on 02/05/2024.
//

#include "SDL_Wrapper.hpp"

SDL_Wrapper::SDL_Wrapper(const int width, const int height, const std::string &name) :
        _width(width), _heigth(height) {
    _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
}

SDL_Wrapper::~SDL_Wrapper() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void SDL_Wrapper::SetFullscreen() {
    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(_window, &_width, &_heigth);
}

void SDL_Wrapper::SetWindowed(const int height, const int width) {
    SDL_SetWindowFullscreen(_window, 0);
    SDL_SetWindowSize(_window, width, height);
    _width = width;
    _heigth = height;
}

SDL_Renderer* SDL_Wrapper::getRenderer() const {
    return _renderer;
}


int SDL_Wrapper::getHeigth() const {
    return _heigth;
}

int SDL_Wrapper::getWidth() const {
    return _width;
}