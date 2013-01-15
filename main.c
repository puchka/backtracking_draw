#include <SDL/SDL.h>
#include <math.h>
#include "file.h"

#define WIDTH 640
#define HEIGHT 480

#define DEPTH 3

SDL_Surface *screen;

void stop();
void create_line(int x, int y, int x2, int y2);
void draw();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Backtracking Draw", NULL);
    atexit(stop);
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            exit(0);
                            break;
                    }
                    break;
            }
        }
        SDL_FillRect(screen, NULL, white);
        draw();
        SDL_Flip(screen);
        SDL_Delay(200);
    }
    return 0;
}

void create_line(int x, int y, int x2, int y2)
{
    SDL_Surface *line;
    SDL_Rect position;
    position.x = x;
    position.y = y;
    if (x!=x2)
    // horizontal line
    {
        line = SDL_CreateRGBSurface(SDL_HWSURFACE, abs(x2-x), 1, 32,
                                    0, 0, 0, 0);
    }
    else
    // vertical line
    {
        line = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, abs(y2-y), 32,
                                    0, 0, 0, 0);
    }
    Uint32 red = SDL_MapRGB(screen->format, 142, 46, 58);
    SDL_FillRect(line, NULL, red);
    SDL_BlitSurface(line, NULL, screen, &position);
}

void draw()
{
    File *file = NULL;
    file = malloc(sizeof(*file));
    file->head = NULL;

    Point point, actualPoint;
    point.x = WIDTH/2;
    point.y = HEIGHT/2;

    string(file, point);
    int i=1, j, n=1, n_temp;
    while (i<=DEPTH)
    {
        for (j=0;j<i-1;j++)
            n=n_temp*4;
        n_temp = n;
        while(n!=0)
        {
            actualPoint = march(file);
            create_line(actualPoint.x-256/(2*i),
                        actualPoint.y,
                        actualPoint.x+256/(2*i),
                        actualPoint.y);
            create_line(actualPoint.x-256/(2*i),
                        actualPoint.y-256/(4*i),
                        actualPoint.x-256/(2*i),
                        actualPoint.y+256/(4*i));
            create_line(actualPoint.x+256/(2*i),
                        actualPoint.y-256/(4*i),
                        actualPoint.x+256/(2*i),
                        actualPoint.y+256/(4*i));

            point.x = actualPoint.x-256/(2*i);
            point.y = actualPoint.y-256/(4*i);
            string(file, point);
            point.x = actualPoint.x-256/(2*i);
            point.y = actualPoint.y+256/(4*i);
            string(file, point);
            point.x = actualPoint.x+256/(2*i);
            point.y = actualPoint.y-256/(4*i);
            string(file, point);
            point.x = actualPoint.x+256/(2*i);
            point.y = actualPoint.y+256/(4*i);
            string(file, point);

            n--;
        }
        i++;
    }
}

void stop()
{
    SDL_FreeSurface(screen);
    SDL_Quit();
}
