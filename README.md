# Glade Engine
- A simple game engine written in C++ using SDL2
# Features
- Basic FPS management
- Open a SDL2 window with a window title
- The ability to create rectangles that can be textured and animated
# Basic Documentation
- Most functions can be found in gameUtils.h

# SDL Holder

## Properties
`SDL_Window* window`
Pointer to the window object.

` SDL_Renderer* renderer `
Pointer to the renderer.

` std::vector<makeRectangle*> drawList `
List that contains all objects to be drawn.

` std::vector<makeRectangle*> collisionList `
List that contains all objects to calculate collisions for.

`const int FPS = 60`
The FPS the window will use. Default is 60.

## Functions

## Constructor
`sdlHolder(int xResolution, int yResolution, std::string title)`
Takes in the desired resolution of the window and the title of the window.
## Update Screen
`void updateScreen()`
Draws the current draw list to the screen.

# Make Rectangle

## Properties

`SDL_Rect rect`
Contains the information for the dimensions and size of the rectangle.

`SDL_Rect spriteRect`
Contains the same things as the property above this one.

`SDL_Rect spriteSheetLocation`
Contains the information for the position and size of the rectangle`s texture on a texture atlas.

`SDL_RendererFlip flip = SDL_FLIP_NONE`
Flip the sprite if you need.

`bool playAnimation = false`
Start looping the animation frames stored in animation list. Default to false.

`bool active = true`
Determines if the rectangle will be drawn to the screen. Default to true.

`float angle = 0`
Change the angle to alter the rotation of the rectangle.

`std::vector<SDL_Rect> animationList`
A list of texture atlas location for animation purposes.

`std::vector<makeRectangle*>* topDrawList`
A pointer to the draw list located in the SDLHolder instance.

## Functions

## Constructor
`makeRectangle(int x, int y, int w, int h, SDL_Renderer* r, SDL_Window* win, std::vector<makeRectangle*>* drawList)`
Creates an instance of rectangle. The origin point on rectangles is the top left corner. It needs a pointer to the renderer, window, and draw list.
## Set Texture
`void setTexture(std::string path, SDL_Rect sheetLocation)`
Assigns a texture to the rectangle using a string filepath and a SDL_Rect to locate the position of the texture on the texture atlas. The SDL_Rect should be in the form of:
`{TopLeftXPosition, TopLeftYPosition, TextureWidth, TextureHeight}`
## Add Animation Frame
`void addAnimationFrame(SDL_Rect frame)`
Adds a new frame to the animation list. Refer to the setTexture section for getting the position of your position on your texture atlas. To play your animation, you have to set the play animation property to true:
`makeRectangleInstance.playAnimation = true;`
## Remove From Draw List
`void removeFromDrawlist()`
Removes the object from the draw list. This will lead to a hanging pointer, so I would advise against using it for now.
## Remove From List
`void removeFromList(std::vector<makeRectangle*>* rectList)`
Takes in a pointer to a list of makeRectangles objects and removes the current object from the list, assuming that the object is present in the list. May lead to memory leaks.
## Set Color
`void setColor(int r, int g, int b, int a)`
Takes in four values: red, green, blue, and alpha. 
## Draw 
`void draw(int animationFrame)`
You will not have to manually call this function.
## Check Collision
`bool checkCollision(SDL_Rect rectB)`
Takes in a SDL_Rect and compares it with the current object`s rect to check for intersections. Returns a boolean.
## Check Collision with Mouse
`bool checkCollisionWithMouse(int x, int y)`
Takes in the position of the mouse and determines if the current object intersects with it. Returns a boolean.
