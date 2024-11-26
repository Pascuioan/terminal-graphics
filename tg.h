#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

const int SH = 30, SW = 120;
const int FPS = 30;
 
struct Line{
  int p1, p2;
};

struct Vec2 {
  float x, y;
};

char buffer[SH][SW];
 
void clear_screen(){
  printf("\033[H\033[2J");
}

void clean_buffer(){
  memset(buffer, ' ', SW * SH * sizeof(char));
}

void draw(){
  for(int i = 0; i < SH; i++){
    for(int j = 0; j < SW; j++){
      putchar(buffer[i][j]);
    }
    putchar('\n');
  }  
}

void plot(Vec2 point){
  if(point.x < 0 || point.x >= SW || point.y < 0 || point.y >= SH)
    return;
  buffer[SH - static_cast<int>(point.y)- 1][static_cast<int>(point.x)] = '*';
}

Vec2 translate(const Vec2& point, const Vec2& offset){
  return Vec2 {point.x + offset.x, point.y + offset.y};
}

Vec2 rotate(const Vec2& point, float angle){
  float s = sin(angle), c = cos(angle);
  return Vec2{point.x * c - point.y * s, point.x * s + point.y * c};
}

Vec2 scale(const Vec2& point, float x_scale, float y_scale){
  return Vec2{point.x * x_scale, point.y * y_scale};
}

void draw_line(const Vec2& p1, const Vec2& p2){
  float 
    dx = abs(p1.x - p2.x),
    dy = abs(p1.y - p2.y);
    
    float screenx, screeny;

    if(dx == 0){
      for(int i = std::min(p1.y, p2.y); i <= std::max(p1.y, p2.y); i++){
        screenx = p1.x,
        screeny = i;
        plot(Vec2{screenx, screeny});
      }
      return;
    }

    float
    slope = (p2.y - p1.y) / (p2.x - p1.x),
    offset = p1.y - slope * p1.x;
    float x;

    if(dy < dx){
      x = slope;
      for(int i = std::min(p1.x,p2.x); i <= std::max(p1.x,p2.x); i++){
        screenx = i;
        screeny = slope * i + offset;
        plot(Vec2{screenx, screeny});
      }
    }else{
      for(int i = std::min(p1.y, p2.y); i <= std::max(p1.y, p2.y); i++){
        screenx = (i - offset) / slope;
        screeny = i;
        plot(Vec2{screenx, screeny});
      }
    }
}

void run(void (*set_buffer)(), void (*update)()){
  while(true){
    clear_screen();
    set_buffer();
    draw();
    clean_buffer();
    update();
    usleep(1000000 / FPS);
  }
}