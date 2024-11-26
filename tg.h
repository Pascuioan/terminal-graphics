#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

const int SH = 30, SW = 120;
const int FPS = 30;
 
struct Point{
  float x, y;
};

struct Line{
  int p1, p2;
};
 
char buffer[SH][SW];
 
void clear_screen(){
  printf("\033[H\033[2J");
}

void draw(){
  for(int i = 0; i < SH; i++){
    for(int j = 0; j < SW; j++){
      putchar(buffer[i][j]);
    }
    putchar('\n');
  }  
}

void plot(int x, int y){
  buffer[SH - y - 1][x] = '*';
}

Point translate(Point point, Point offset){
  return Point {point.x + offset.x, point.y + offset.y};
}

void run(void (*set_buffer)(), void (*update)()){
  while(true){
    clear_screen();
    set_buffer();
    draw();
    update();
    usleep(1000000 / FPS);
  }
}