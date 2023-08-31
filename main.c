#include "raylib.h"
#include <math.h>

#define screenWidth 800 
#define screenHeight 440
#define pixelw 20

// ???
enum {
    pixcountw = (int)screenWidth/pixelw,
    pixcounth = (int)screenHeight/pixelw
};

int grid[pixcountw][pixcounth] = { 0 };
int ngrid[pixcountw][pixcounth] = { 0 };

void gridcpy(int dest[pixcountw][pixcounth], int src[pixcountw][pixcounth]) {
    for (int i = 0; i<pixcountw; i++) {
        for (int j = 0; j<pixcounth; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int neighbours(int x, int y) {
    int total = 0;
    for (int i = x-1; i<x+2; i++) {
        for (int j = y-1; j<y+2; j++) {
            if (i == x && j == y) 
                continue;

            int ri, rj;
            ri = i; rj = j;
            if (i < 0) ri = pixcountw-1;
            if (i >= pixcountw) ri = 0;
            if (j < 0) rj = pixcounth-1;
            if (j >= pixcounth) rj = 0;
            // if (i < 0 || i >= pixcountw)
            //     continue;
            // if (j < 0 || j >= pixcounth)
            //     continue;
            total += grid[ri][rj];
        }
    }
    return total;
}

int main(void)
{
    // some set up
    InitWindow(screenWidth, screenHeight, "Conway's game of life");
    SetTargetFPS(60);
    Vector2 clickpos = {0.0f, 0.0f};
    int running = 0;

    while (!WindowShouldClose())
    {
        // updates 
        clickpos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !running) {
            int x = floor(clickpos.x/pixelw);
            int y = floor(clickpos.y/pixelw);
            if (grid[x][y])
                grid[x][y] = 0; 
            else 
                grid[x][y] = 1;
        }

        if (IsKeyPressed(KEY_R)) {
            running = 1;
        }

        if (IsKeyPressed(KEY_S)) {
            running = 0;
        }

        // if we are running, conway time. 
        if (running) {
            // copy to a new grid. 
            gridcpy(ngrid, grid);
            for (int i = 0; i<pixcounth; i++) {
                for (int j = 0; j<pixcountw; j++) {
                    int nei = neighbours(j, i);
                    if (grid[j][i]) {
                        if (nei < 2 || nei > 3) 
                            ngrid[j][i] = 0;
                    } else {
                        if (nei == 3)
                            ngrid[j][i] = 1;
                    }
                }
            }

            // now replace current grid with new one
            gridcpy(grid, ngrid);

            // delay
            WaitTime(0.25);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i<pixcounth; i++) {
            for (int j = 0; j<pixcountw; j++) {
                Color c = LIGHTGRAY; 
                if (running)
                    c = WHITE;
                if (grid[j][i] == 1) 
                    c = BLACK;
                DrawRectangle(j*pixelw, i*pixelw, pixelw, pixelw, c);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
