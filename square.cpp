#include "tg.h"

Point points[] = {
5.0f, 5.0f, 
5.0f, -0.0f, 
-0.0f, -0.0f, 
-0.0f, 5.0f,
0.0f, 0.0f,
-5.0f, 0.0f,
0.0f, -5.0f, 
};

Point screen_center{SW / 2, SH / 2};

Line lines[] = {
  0, 1,
  0, 3,
  1, 2,
  2, 3,
  4, 5,
  4, 6,
  5, 6,
};

float angle, s, c = 1;

void update(){
  angle += M_PI / 180 / FPS * 120;
  if(angle > 2 * M_PI)
    angle -= 2 * M_PI;
  s = sin(angle);
  c = cos(angle);
}

void set_buffer(){
  memset(buffer, ' ', SW * SH * sizeof(char));
  for(int i = 0; i < 7; i++){
    Point 
    //unmodified point
    basic_p1 = points[lines[i].p1],
    basic_p2 = points[lines[i].p2],
    //translated point
    p1{round(basic_p1.x * c - basic_p1.y * s) * 2, round(basic_p1.x * s + basic_p1.y * c)},
    p2{round(basic_p2.x * c - basic_p2.y * s) * 2, round(basic_p2.x * s + basic_p2.y * c)};

    float 
    dx = abs(p1.x - p2.x),
    dy = abs(p1.y - p2.y);
    
    if(dx == 0){
      for(int i = std::min(p1.y, p2.y); i <= std::max(p1.y, p2.y); i++){
        int
        screenx = p1.x + (SW / 2),
        screeny = i + (SH / 2);
        plot(screenx, screeny);
      }
      continue;
    }

    float
    slope = (p2.y - p1.y) / (p2.x - p1.x),
    offset = p1.y - slope * p1.x;
    int screenx, screeny;

    if(dy < dx){
      for(int i = std::min(p1.x,p2.x); i <= std::max(p1.x,p2.x); i++){
        screenx = i;
        screeny = round(slope * i + offset);
      }
    }else{
      for(int i = std::min(p1.y, p2.y); i <= std::max(p1.y, p2.y); i++){
        screenx = round((i - offset) / slope);
        screeny = i;
      }
    }
  }
}
 
int main(){
  run(set_buffer, update);
}