#ifndef gameUtils
#define gameUtils

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <time.h>
#include <vector>
#include "primitiveUtils.h"
#include <iostream>
#include <algorithm>

Uint32 getMousePosition(int &mouseX, int &mouseY){
	SDL_GetMouseState(&mouseX, &mouseY);
}

class makeRectangle{

public:

	SDL_Rect rect;
		
	int red, green, blue = 0;
	
	int alpha = 255;
	
	SDL_Renderer* renderer;
	
	SDL_Window* window;
	
	SDL_Surface* spriteSurface = nullptr;
	
	SDL_Texture* spriteTexture = nullptr;
	
	SDL_Rect spriteRect;
	
	SDL_Rect spriteSheetLocation;

	SDL_Point center;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	
	bool playAnimation = false;

	bool isMoving = false;

	bool active = true;

	bool isBullet = false;

	float velocityX, velocityY = 0;

	int drawIndex = 0;

	int lifetime = -1;

	int collisionIndex = 0;

	int acceleration = 0;

	float angle = 0; 

	std::vector<SDL_Rect> animationList;

	std::vector<makeRectangle*>* topDrawList;
	
	makeRectangle(int x, int y, int w, int h, SDL_Renderer* r, SDL_Window* win, std::vector<makeRectangle*>* drawList){
	
		renderer = r;
	
		window = win;
	
		rect.x = x;
	
		rect.y = y;
	
		rect.w = w;
	
		rect.h = h;

		center = {w/2, h/2};

		drawList->push_back(this);

		drawIndex = drawList->size()-1;

		topDrawList = drawList;
		
	}
	
	~makeRectangle(){

		cleanUp();

	}

	void setVelocity(float x, float y){

		isMoving = true;

		isBullet = true;

		velocityX = x;

		velocityY = y;

	}

	void setTexture(std::string path, SDL_Rect sheetLocation){
	
		spriteSheetLocation = sheetLocation;
	
		spriteSurface = IMG_Load(path.c_str());
		
		//spriteSurface = SDL_ConvertSurfaceFormat(spriteSurface, SDL_GetWindowPixelFormat(window), 0);
		
		spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
		
		SDL_FreeSurface(spriteSurface);
		
		spriteRect = {rect.x, rect.y, rect.w, rect.h};
		
	}
	
	void addAnimationFrame(SDL_Rect frame){
	
		animationList.push_back(frame);
	
	}

	void removeFromDrawlist(){

		auto it = std::find(topDrawList->begin(), topDrawList->end(), this);

		if (it != topDrawList->end()) {
			topDrawList->erase(it);
		}

		/*if(this == nullptr){

			return;

		}

		for(int i = 0; i < topDrawList->size(); i++){

			if((*topDrawList)[i] == this){

				topDrawList->erase(topDrawList->begin() + i);

				delete this;

				break;

			}

		}*/

	}

	void removeFromList(std::vector<makeRectangle*>* rectList){

		auto it = std::find(rectList->begin(), rectList->end(), this);

		if (it != rectList->end()) {
			rectList->erase(it);
		}

		/*for(int i = 0; i < rectList->size(); i++){

			if((*rectList)[i] == this){

				rectList->erase(rectList->begin() + i);

			}

		}*/



	}
	
	void moveVelocity(){

		if (isMoving){

			rect.x += velocityX;

			rect.y += velocityY;
/*
			if (!isInBounds(640, 480, rect.x, rect.y) && active){

				removeFromDrawlist();

				active = false;

			}
*/
		}

	}

	void setColor(int r, int g, int b, int a){
	
		red = r;
		
		green = g;
		
		blue = b;
		
		alpha = a;
	
	}
	
	void draw(int animationFrame){
	
		if(!active){return;}

		if(this == nullptr){

			return;

		}

		if(this->lifetime != -1){

			this->lifetime--;

			if(this->lifetime == 0){

				this->removeFromDrawlist();

			}

		}

		if (spriteTexture != nullptr){
		
			spriteRect = rect;
		
			if (animationList.size() < 2 || !playAnimation) {
			
				SDL_RenderCopyEx(renderer, spriteTexture, &spriteSheetLocation, &spriteRect, angle, &center, flip);
			
			} else{
			
				int adjustedAnimationFrame = (animationFrame / 200) % animationList.size();
			
				SDL_RenderCopyEx(renderer, spriteTexture, &animationList[adjustedAnimationFrame], &spriteRect, angle, &center, flip);
			
			}
		
		} else{
		
			SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);

			SDL_RenderFillRect(renderer, &rect);
		
		}
	
	}
	
	bool checkCollision(SDL_Rect rectB){
	
		bool isCollision = (rect.x < rectB.x + rectB.w &&
				rect.x + rect.w > rectB.x &&
				rect.y < rectB.y + rectB.h &&
				rect.y + rect.h > rectB.y);
				
		return isCollision;
	
	}
	
	bool checkCollisionWithMouse(int x, int y){
	
		bool isCollision = (rect.x < x &&
							rect.x + rect.w > x &&
							rect.y < y &&
							rect.y + rect.h > y
		);
	
		if (isCollision){
		
			SDL_Log("Collision");
		
		}
	
		return isCollision;
	
	}
	
	void cleanUp(){
	
		SDL_DestroyTexture(spriteTexture);

	}
	
};

class makeText{

public:

	SDL_Texture* textTexture = nullptr;
	
	SDL_Surface* textSurface = nullptr;
	
	SDL_Renderer* renderer;

	SDL_Color textColor;
	
	SDL_Rect textRect;
	
	TTF_Font* font;

	int xPosition, yPosition, width, height;

	makeText(int x, int y, int w, int h, std::string text, SDL_Color color, TTF_Font* newFont, SDL_Renderer* r){
	
		xPosition = x; yPosition = y; width = w; height = h;
		
		renderer = r;
		
		font = newFont;
		
		textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	
		SDL_Log(TTF_GetError());
		
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		
		SDL_FreeSurface(textSurface);
		
		textRect = {x, y, w, h};
		
		if (textSurface == nullptr){
		
			SDL_Log(TTF_GetError());
		
		}
		
	}
	
	void updateText(std::string newText) {
	
		textSurface = TTF_RenderText_Blended(font, newText.c_str(), textColor);
	
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		
		SDL_FreeSurface(textSurface);
	
	}
	
	void draw(){
	
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	
	}
	
	void cleanUp(){
	
		SDL_DestroyTexture(textTexture);
	
	}

};

class sdlHolder{

public:

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	std::vector<makeRectangle*> drawList;

	std::vector<makeRectangle*> collisionList;

	const int FPS = 60;
	
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart, frameTime;
	
	Uint32 lastFrameTime;
	
	TTF_Font* font;
	
	sdlHolder(int xResolution, int yResolution, std::string title){
	
		srand(time(0));

		TTF_Init();
		
		font = TTF_OpenFont("Arial.ttf", 56);
		
		IMG_Init(IMG_INIT_PNG);
	
		if (SDL_Init(SDL_INIT_VIDEO) != 0){

			SDL_Log("SDL initialization failed");
	
		}
	
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xResolution, yResolution, SDL_WINDOW_SHOWN);

		if (!window){
	
			SDL_Log("Window Creation Failed");
	
			SDL_Quit();
	
			exit(0);
	
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	
	}
	
	~sdlHolder(){

		cleanUp();

	}

	void updateScreen(){

		frameStart = SDL_GetTicks();
	
		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameTime < frameDelay) {
		
			SDL_Delay(frameDelay - frameTime);
			
		}

		int totalDrawList = drawList.size();
		
		for(int i = 0; i<totalDrawList; i++){
		
			drawList[i]->draw(frameStart);

			drawList[i]->moveVelocity();
		
		}
		
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

		SDL_RenderPresent(renderer);

	
	}
	
	void cleanUp(){
	
		TTF_CloseFont(font);

		SDL_DestroyRenderer(renderer);

		SDL_DestroyWindow(window);
	
		SDL_Quit();
	
	}

};

#endif
