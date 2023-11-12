#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "gameUtils.h"
#include "primitiveUtils.h"
#include <time.h>
#include <vector>
#include <string>
#include "game.h"
#include <iostream>

/*
A boiler plate for future projects

This will also contain some documentation for how to use my objects

There will be a markdown file explaining all of the functions

This template will create a simple window with a flappy bird flapping, with some boilerplate code

to capture mouse position and keyboard input.

*/

int main(){

    const int HEIGHT = 480;

    const int WIDTH = 640;

    const int SCALE = 1;

    //Create and SDL window and game information holder

    sdlHolder screen = sdlHolder(WIDTH, HEIGHT, "Window");

    gameHolder gameHolder;

    //Create Sprites

    //Character

    makeRectangle character(WIDTH/2, HEIGHT/2, 190, 140, screen.renderer, screen.window, &screen.drawList);

    character.setTexture("./flappySheet.png", {2, 490, 19, 14});

    character.addAnimationFrame({2, 490, 19, 14}); character.addAnimationFrame({30, 490, 19, 14}); character.addAnimationFrame({58, 490, 19, 14});

    character.playAnimation = true;

    //Create and poll SDL Events 

    SDL_Event event;

    int cooldown = SDL_GetTicks();

    while (!gameHolder.quit){
        
        while (SDL_PollEvent(&event)){

            int mouseX, mouseY = 0;

            Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
            
            if (event.type == SDL_QUIT){
                gameHolder.quit = 1;
            }

            if (event.type == SDL_KEYDOWN){
                continue;

            } else if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                        ;
                }

            } else if (event.type == SDL_MOUSEBUTTONUP){
                if (event.button.button == SDL_BUTTON_LEFT){
                    continue;
                }
            }
        }

        SDL_RenderClear(screen.renderer);
        
        screen.updateScreen();

    }

    return 0; 

}

