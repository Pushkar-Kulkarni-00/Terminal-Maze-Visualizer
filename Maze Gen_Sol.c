#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 31
#define HEIGHT 31

int maze[HEIGHT][WIDTH];
int visited[HEIGHT][WIDTH];

int dir[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};
int carve_dir[4][2] = {
    {-2, 0}, {2, 0}, {0, -2}, {0, 2}
};

void resetCursor() {
    printf("\033[H");
}

void drawStaticMaze() {
    resetCursor();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (maze[y][x] == 1)
                printf("\033[0;32m|||\033[0m");   
            else
                printf("   ");                    
        }
        printf("\n");
    }
    fflush(stdout);
}

void updateDot(int y, int x, int isGoal) {
    printf("\033[%d;%dH", y + 1, x*3 + 1);   

    if (isGoal)
        printf("\033[0;31m . \033[0m");
    else
        printf("\033[0;33m . \033[0m");

    fflush(stdout);
}

void shuffle(int arr[4]) {
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

void carve(int x, int y) {
    maze[y][x] = 0;

    int order[4] = {0, 1, 2, 3};
    shuffle(order);

    for (int i = 0; i < 4; i++) {
        int d = order[i];
        int nx = x + carve_dir[d][1];
        int ny = y + carve_dir[d][0];

        if (ny > 0 && ny < HEIGHT - 1 &&
            nx > 0 && nx < WIDTH - 1 &&
            maze[ny][nx] == 1) {

            maze[y + carve_dir[d][0] / 2][x + carve_dir[d][1] / 2] = 0;
            carve(nx, ny);
        }
    }
}

int solve(int x, int y) {
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return 0;
    if (maze[y][x] == 1 || visited[y][x])
        return 0;

    visited[y][x] = 1;
    maze[y][x] = 2;

    updateDot(y, x, (y == HEIGHT-1 && x == WIDTH-2));
    usleep(20000);

    if (y == HEIGHT - 1 && x == WIDTH - 2)
        return 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][1];
        int ny = y + dir[i][0];
        if (solve(nx, ny))
            return 1;
    }

    maze[y][x] = 0;
    printf("\033[%d;%dH   ", y + 1, x*3 + 1);
    fflush(stdout);

    return 0;
}

int main() {
    srand(time(NULL));

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            maze[y][x] = 1;


    carve(1, 1);
    maze[0][1] = 0;
    maze[HEIGHT - 1][WIDTH - 2] = 0;

    drawStaticMaze();

    solve(1, 0);

    return 0;
}
