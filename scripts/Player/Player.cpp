//
// Created by Logan on 30/04/2024.
//

#include "Player.hpp"

void Player::Action(SDL_Event &event, SDL_Renderer* renderer){
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                SetNewPositionY(-8);
                break;
            case SDLK_DOWN:
                SetNewPositionY(8);
                break;
            case SDLK_LEFT:
                SetNewPositionX(-8);
                break;
            case SDLK_RIGHT:
                SetNewPositionX(8);
                break;
            case SDLK_SPACE:
                Shoot(renderer);
                break;
            default:
                break;
        }
    }
}

void Player::Shoot(SDL_Renderer *renderer) {
   // bullets.emplace_back(5,10,GetPosition().x+20,GetPosition().y-5,renderer,"Laser");
   if(GetDelay() <= 0) {
       bullets.emplace_back(5, 10, GetPosition().x + 10, GetPosition().y - 5, renderer, "Laser");
       bullets.emplace_back(5, 10, GetPosition().x + 30, GetPosition().y - 5, renderer, "Laser");
       SetDelay(10);
   }

   }

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}

void Player::Add_Score(int _score) {
    score += _score;
}

int Player::GetScore() {
    return score;
}

void Player::SetUpgrade(bool _upgrade) {
    upgrade = _upgrade;
}

void Player::SetScore(int _score) {
    score = _score;
}

void Player::RenderHealthBar(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // White color for background
    SDL_RenderFillRect(renderer, &healthBarBackground);
    healthBar.w = (GetHealth() / 100.0) * healthBarBackground.w;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color for health
    SDL_RenderFillRect(renderer, &healthBar);
}

void Player::RenderScore(SDL_Renderer *renderer, TTF_Font *font) {

    SDL_Rect scoreRect;
    scoreRect.x = 0;  //controls the rect's x coordinate
    scoreRect.y = 480; // controls the rect's y coordinte
    scoreRect.w = 100; // controls the width of the rect
    scoreRect.h = 50; // controls the height of the rect

    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Fill the rectangle with the current drawing color (black)
    SDL_RenderFillRect(renderer, &scoreRect);

    SDL_Color white = {255, 255, 255, 255}; // RGB color for white
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, scoreText.c_str(), white);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 480; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 50; // controls the height of the rect

    // Render the message to the screen
    SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);

    // Free the resources
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);


}


