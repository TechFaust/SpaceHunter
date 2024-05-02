//
// Created by Logan on 02/05/2024.
//

#ifndef SPACEHUNTER_SDL_WRAPPER_HPP
#define SPACEHUNTER_SDL_WRAPPER_HPP


#include <SDL.h>
#include <string>

class SDL_Wrapper {
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    int _width, _heigth;

public:
    SDL_Wrapper(int width, int height, const std::string &name);
    ~SDL_Wrapper();

    void SetFullscreen();
    void SetWindowed(int height, int width);

    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeigth() const;
};

#endif //SPACEHUNTER_SDL_WRAPPER_HPP
