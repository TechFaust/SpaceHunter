//
// Created by Logan on 03/05/2024.
//

#include "Meteor.hpp"

void Meteor::Move_Enemy() {

        SetNewPositionY(30);
        switch (rand() % 2) {
            case 0:
                SetNewPositionX(10);
                break;
            case 1:
                SetNewPositionX(-10);
                break;

    }
}

void Meteor::Shoot_Enemy(SDL_Renderer *renderer) {

}
