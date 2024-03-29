
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <SDL_ttf.h>


#define FONT_PATH   "assets/pacifico/Pacifico.ttf"






const int SCREEN_WIDTH = 656;
const int SCREEN_HEIGHT = 400;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;



int walls[25][41]={
   //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};





// Load an image and return an SDL_Texture
SDL_Texture* load_texture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Draw a texture at the specified location
void draw_texture(SDL_Texture* texture, int x, int y) {
    SDL_Rect rect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// Check if two rectangles intersect
int wallCollision(int x, int y, int direction) {
    x /= 16;
    y /= 16;
    if(walls[y-1][x] == 1 && direction == 0){
       return 0;
    }else if(walls[y][x-1] == 1 && direction == 1){
        return 0;
    }else if(walls[y+1][x] == 1 && direction == 2){
        return 0;
    }else if(walls[y][x+1] == 1 && direction == 3){
        return 0;
    }
    return 1;
}
int main(int argc, char* argv[]) {

    (void) argc;
    (void) argv;

    // Initialize SDL2 and create a window and renderer
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    window = SDL_CreateWindow("The Big 3: Level 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load background, character, and obstacle images
    SDL_Texture* bugUp_texture = load_texture("C:/Users/htrik/OneDrive/Desktop/sdl_workshop-main/assets/walls/bugUp.png");
    SDL_Texture* bugLeft_texture = load_texture("C:/Users/htrik/OneDrive/Desktop/sdl_workshop-main/assets/walls/bugLeft.png");
    SDL_Texture* bugDown_texture = load_texture("C:/Users/htrik/OneDrive/Desktop/sdl_workshop-main/assets/walls/bugDown.png");
    SDL_Texture* bugRight_texture = load_texture("C:/Users/htrik/OneDrive/Desktop/sdl_workshop-main/assets/walls/bugRight.png");
    SDL_Texture* maze_texture = load_texture("C:/Users/htrik/OneDrive/Desktop/sdl_workshop-main/assets/walls/maze.png");


    int bugAbs = 0;
    int bugOrd = 48;

    //Drawing the walls

    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 1);
    SDL_RenderClear(renderer);
    draw_texture(maze_texture, 0, 0);
    draw_texture(bugRight_texture,bugAbs,bugOrd);

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);



    // Load a font
    TTF_Font* font1 = TTF_OpenFont("C:/Users/htrik/Downloads/sdl_workshop-main/sdl_workshop-main/assets/pacifico/Anonymous_Pro/AnonymousPro-Bold.ttf", 14);
    TTF_Font* font2 = TTF_OpenFont("C:/Users/htrik/Downloads/sdl_workshop-main/sdl_workshop-main/assets/pacifico/Anonymous_Pro/AnonymousPro-Bold.ttf", 64);

    // Create a surface for the text
    SDL_Color textColor = { 0x80, 0x00, 0x00, 0xFF };

    SDL_Surface* welcomeSurface = TTF_RenderText_Solid(font1, "WELCOME!!!", textColor);

    // Convert the surface to a texture
    SDL_Texture* welcomeTexture = SDL_CreateTextureFromSurface(renderer, welcomeSurface);

    // Free the surface
    SDL_FreeSurface(welcomeSurface);

    // Get the dimensions of the texture
    int textWidth1, textHeight1;
    SDL_QueryTexture(welcomeTexture, NULL, NULL, &textWidth1, &textHeight1);

    // Set the position of the text
    SDL_Rect text1Rect = { (SCREEN_WIDTH - textWidth1) / 2, (SCREEN_HEIGHT - textHeight1) / 2, textWidth1, textHeight1 };


    // Render the texture to the screen
    SDL_RenderCopy(renderer, welcomeTexture, NULL, &text1Rect);
    SDL_RenderPresent(renderer);


        Uint32 startTime = SDL_GetTicks();
        Uint32 elapsedTime = 0;
        SDL_Event event;
        int quit = 0;
        int direction = -1;
        while (!quit && elapsedTime <= 40000) {

            switch(direction){
                case 0:
                    draw_texture(bugUp_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 1:
                    draw_texture(bugLeft_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 2:
                    draw_texture(bugDown_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
                case 3:
                    draw_texture(bugRight_texture,bugAbs,bugOrd);
                    SDL_RenderPresent(renderer);
                    break;
            }

            int auxOrd = 0, auxAbs = 0;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = 1;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            auxOrd = -16;
                            direction = 0;
                            break;
                        case SDLK_DOWN:
                            auxOrd = 16;
                            direction = 2;
                            break;
                        case SDLK_LEFT:
                            auxAbs = -16;
                            direction = 1;
                            break;
                        case SDLK_RIGHT:
                            auxAbs = 16;
                            direction = 3;
                            break;
                    }

                }
                if(wallCollision(bugAbs,bugOrd,direction) == 1 && !(bugAbs == 0 && bugOrd == 48 && direction == 1)){

                    bugAbs += auxAbs;
                    bugOrd += auxOrd;
                    SDL_RenderClear(renderer);
                    draw_texture(maze_texture,0,0);
                    switch(direction){
                        case 0:
                            draw_texture(bugUp_texture,bugAbs,bugOrd);
                            SDL_RenderPresent(renderer);
                            break;
                        case 1:
                            draw_texture(bugLeft_texture,bugAbs,bugOrd);
                            SDL_RenderPresent(renderer);
                            break;
                        case 2:
                            draw_texture(bugDown_texture,bugAbs,bugOrd);
                            SDL_RenderPresent(renderer);
                            break;
                        case 3:
                            draw_texture(bugRight_texture,bugAbs,bugOrd);
                            SDL_RenderPresent(renderer);
                            break;
                    }
                    Uint32 currentTime = SDL_GetTicks();
                    elapsedTime = currentTime - startTime;
                    Uint32 elapsedSeconds = elapsedTime / 1000;
                    char timerText[10];
                    sprintf(timerText, "%02d:%02d", elapsedSeconds / 60, elapsedSeconds % 60);
                    int textWidth2, textHeight2;

                    SDL_QueryTexture(welcomeTexture, NULL, NULL, &textWidth2, &textHeight2);

                    SDL_Rect text2Rect = { 400, 0, textWidth2, textHeight2+20 };

                    SDL_Color textColor = { 0x80, 0x00, 0x00, 0xFF };

                    SDL_Surface* exit2Surface = TTF_RenderText_Solid(font2, timerText, textColor);
                    SDL_Texture* exit2Texture = SDL_CreateTextureFromSurface(renderer, exit2Surface);
                    SDL_RenderCopy(renderer, exit2Texture, NULL, &text2Rect);
                    SDL_RenderPresent(renderer);


                }

            }
            if(bugAbs == 640 && bugOrd== 304){
                quit = 1;


                int x = 112;
                int y = 160;

                // Load the font
                TTF_Font* font = TTF_OpenFont("C:/Users/htrik/Downloads/sdl_workshop-main/sdl_workshop-main/assets/pacifico/Anonymous_Pro/AnonymousPro-Bold.ttf", 40);

                // Create the surface for the text
                SDL_Color textColor = {0x80, 0x00, 0x00, 0xFF};
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU GOT IN THE SYSTEM.", textColor);

                // Create the texture from the surface
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

                // Set the background rectangle
                //SDL_Color rectColor = { 0, 255, 0, 128};
                //SDL_Rect rect = { x-5, y-5, textSurface->w, textSurface->h };

                //SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a); // Set the background color
                //SDL_RenderFillRect(renderer, &rect); // Render the rectangle




                // Draw the texture on the screen
                SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                SDL_RenderPresent(renderer);

                SDL_Delay(5000);

                // Clean up
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
                TTF_CloseFont(font);
            }


        }
        if(elapsedTime > 40000){


            // Load the font
            TTF_Font* font = TTF_OpenFont("C:/Users/htrik/Downloads/sdl_workshop-main/sdl_workshop-main/assets/pacifico/Anonymous_Pro/AnonymousPro-Bold.ttf", 64);

            // Create the surface for the text
            SDL_Color color = {0x80, 0x00, 0x00, 0xFF};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU FAILED!", color);

            // Create the texture from the surface
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            // Draw the texture on the screen
            SDL_Rect textRect = { 144, 160, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

            SDL_RenderPresent(renderer);

            SDL_Delay(5000);

            // Clean up
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            TTF_CloseFont(font);
        }
    // Clean up and exit
    SDL_DestroyTexture(maze_texture);
    SDL_DestroyTexture(bugUp_texture);
    SDL_DestroyTexture(bugLeft_texture);
    SDL_DestroyTexture(bugDown_texture);
    SDL_DestroyTexture(bugRight_texture);
    SDL_DestroyTexture(welcomeTexture);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    return 0;
}
