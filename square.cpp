#include "tg.h"

Vec2 points[] = {
5.0f, 5.0f, 
5.0f, -0.0f, 
-0.0f, -0.0f, 
-0.0f, 5.0f,
0.0f, 0.0f,
-5.0f, 0.0f,
0.0f, -5.0f, 
};

Vec2 screen_center{SW / 2, SH / 2};

Line lines[] = {
  0, 1,
  0, 3,
  1, 2,
  2, 3,
  4, 5,
  4, 6,
  5, 6,
};

float angle;

void update(){
  angle += M_PI / 180 / FPS * 90;
  if(angle > 2 * M_PI)
    angle -= 2 * M_PI;
}

void set_buffer(){
  for(int i = 0; i < 7; i++){
    Vec2 
    p1 = points[lines[i].p1],
    p2 = points[lines[i].p2];

    p1 = rotate(p1, angle);
    p1 = scale(p1, 2, 1);
    p1 = translate(p1, screen_center);

    p2 = rotate(p2, angle);
    p2 = scale(p2, 2, 1);
    p2 = translate(p2, screen_center);

    draw_line(p1, p2);
  }
}
 
int main(){
  run(set_buffer, update);
}