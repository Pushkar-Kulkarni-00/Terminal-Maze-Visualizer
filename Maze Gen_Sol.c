    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <conio.h>


    #define W 33
    #define H 33

    int score=0;

    int maze[H][W];
    int visited[H][W];

    int dir[4][2] = {
        {1,0}, {0,1}, {-1,0}, {0,-1}
    };

    int carve_dir[4][2] = {
        {-2,0}, {2,0}, {0,-2}, {0,2}
    };

    void drawmap(){
        printf("\033[H");
        for(int y = 0;y < H;y++){
            for(int x = 0;x < W;x++){
                if(maze[y][x] == 1) printf("\033[0;32m|||\033[0m");
                else if(maze[y][x]==4)printf("\033[0;35m + \033[0m");
                else printf("   ");
            }
            printf("\n");
        }
        fflush(stdout);
    }

    void shuffle(int arr[4]){
        for(int i = 0;i < 4;i++){
            int j = rand() % (i+1);
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }

    int carve(int x, int y){
        maze[y][x] = 0;
        int order[4] = {0,1,2,3};
        shuffle(order);

        for(int i = 0;i < 4;i++){
            int d = order[i];
            int nx = x + carve_dir[d][1];
            int ny = y + carve_dir[d][0];
            if(nx > 0 && nx < W - 1 && ny > 0 && ny < H - 1 && maze[ny][nx] == 1){
                maze[y + carve_dir[d][0] / 2][x + carve_dir[d][1] / 2] = 0;
                int abc=rand()%5;
                if(!abc)  maze[y + carve_dir[d][0] / 2][x + carve_dir[d][1] / 2] = 4;
                carve(nx,ny);
            }
        }
    }

    void update(int y, int x, int goal){
        printf("\033[%d;%dH", y + 1, x*3 + 1);

        if(goal) printf("\033[0;31m . \033[0m");
        else printf("\033[0;33m . \033[0m");
        fflush(stdout);
    }

    int solve(int x, int y){
        printf("\033[%d;%dH\033[0;32m SCORE: %d\033[0m\n", H+4, 1,score);
        if(x < 0 || y < 0 || x >= W || y >= H) return 0;
        if(visited[y][x] || maze[y][x] == 1) return 0;

        
        visited[y][x] = 1;
        if(maze[y][x]==4)score+=5;
        maze[y][x] = 2;
        
        update(y,x,(y == H-1 && x == W-2));
        usleep(20000);
        
        if(y == H - 1 && x == W - 2) return 1;

        for(int i = 0;i<4;i++){
            int nx = x + dir[i][1];
            int ny = y + dir[i][0];
            if(solve(nx,ny)) return 1;
        }

        maze[y][x] = 0;
        printf("\033[%d;%dH   \033[0m", y + 1, x*3 + 1);
        fflush(stdout);
        return 0;
    }

    int getkeypress() {
        int ch = getch();
        if(ch == '#') return -2;

        if(ch == 0 || ch == 224){
            int arrow = getch();
            if(arrow == 72) return 0; 
            if(arrow == 80) return 1; 
            if(arrow == 77) return 2; 
            if(arrow == 75) return 3; 
        }
        return -1;
    }


    void oneplayer(){
        int cx = 1;
        int cy = 0;
        printf("\033[%d;%dH\033[0;32m SCORE: %d\033[0m\n", H+4, 1,score);
        visited[cy][cx] = 1;
        if(maze[cy][cx]==4)score+=5;
        printf("\033[%d;%dH\033[0;33m . \033[0m", cy+1, cx*3+1);
        fflush(stdout);

        while(!(cy == H-1 && cx == W-2)){
            int d = getkeypress();
            if(d == -1) continue;
            if(d == -2) solve(cx,cy);
            int nx = cx;
            int ny = cy;
            
            if(d == 0) ny--;      
            else if(d == 1) ny++; 
            else if(d == 2) nx++; 
            else if(d == 3) nx--; 
            
            if(nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
            if(maze[ny][nx] == 1) continue;
            if(maze[ny][nx]==4)score+=5;


            if(visited[ny][nx] == 1){
                visited[cy][cx] = 0;
                printf("\033[%d;%dH   \033[0m", cy+1, cx*3+1);
                fflush(stdout);
            }
            else {
                visited[ny][nx] = 1;
                printf("\033[%d;%dH\033[0;33m . \033[0m", ny+1, nx*3+1);
                fflush(stdout);
            }

            cx = nx;
            cy = ny;

            printf("\033[%d;%dH\033[0;32m SCORE: %d\033[0m", H+4, 1, score);
            fflush(stdout);
        }
        printf("\033[%d;%dH\033[0;32m MAZE COMPLETED! \033[0m\n", H+2, 1);
        printf("\033[%d;%dH\033[0;32m SCORE: %d\033[0m\n", H+4, 1,score);
    }


    int main() {
        srand(time(NULL));

        for(int y = 0;y < H;y++){
            for(int x = 0;x < W;x++){
                maze[y][x] = 1;
            }
        }
        carve(1,1);
        maze[0][1] = 0;
        maze[H-1][W-2] = 0;
        drawmap();
        int select=0;
        printf("Enter player mode [0 for Auto Solver 1 for Single player] :: ");
        scanf("%d",&select);
        if(select == 0)solve(1,0);
        else oneplayer();
        return 0;
    }
