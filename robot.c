#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#define GRID_SIZE 14
#define PI 3.141592

typedef struct {
  int active;
  float x;
  float y;
  float speed;
  int heading;
} Missile;

typedef struct {
  int id;
  char name[50];
  float x;
  float y;
  float energy;
  float speed;
  int heading;
  Missile my_missile;

}Robot;

typedef struct {
  int active ;
  int x;
  int y;
}Target;


// This function moves the cursor to (0,0) without clearing the screen
void reset_cursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hOut, coord);
}




// Optional: Hides the blinking underscore cursor so it looks like a game
void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
int fire_weapon(Robot *rb) {
  if(rb->my_missile.active == 0) {
    rb->my_missile.active = 1;
    rb->my_missile.x = rb->x;
    rb->my_missile.y = rb->y;
    rb->my_missile.heading = rb->heading;
    rb->my_missile.speed = 2.0;
    return 1;
  } else {
    return 0;
  }
}
void motion(Robot *rb) {

  for(int i = 0; i < 1; i++) {

    char command;
    printf("Enter your move (W/A/S/D) :  \n");
    command = getch();
    float rad = rb->heading *(PI / 180.0);
    switch (command) {
      case 'w':
        rb->x += cos(rad) * 1.0;
        rb->y += sin(rad) * 1.0;
      if(rb->y < 0) {
        rb->y = GRID_SIZE-0.1;
      }
      if(rb->x < 0) {
        rb->x = GRID_SIZE-0.1;
      }
      break;
      case 's':
      rb->x -= cos(rad) * 1.0;
      rb->y -= sin(rad) * 1.0;
      if(rb->y > GRID_SIZE-1) {
        rb->y = 0.0;
        if(rb->x > GRID_SIZE-1) {
          rb->x = 0.0;
        }
      }
      break;
      case 'd':
      rb->heading += 10;
      if(rb->heading >= 360) {
        rb->heading = 0;
      }
      break;
      case 'a':
      rb->heading -= 10;
      if(rb->heading < 0) {
        rb->heading =350;
      }
      break;
      case 'm': 
        fire_weapon(rb);
        break;
      default : 
        printf("just enter the a letter between (W,S,D,A)\n");
      break;
    }
  }

}

void show_map(Robot *rb, Target *t1) {
  reset_cursor();
  char grid[GRID_SIZE][GRID_SIZE];
  for(int y = 0 ; y < GRID_SIZE ; y++) {
    for(int x = 0 ; x < GRID_SIZE; x++) {
      grid[y][x] = '.';
    }
  }
  int displayX = (int) rb->x;
  int displayY = (int) rb->y;
  grid[displayY][displayX] = 'R';
  if(rb->my_missile.active == 1) {
        int mx = (int)rb->my_missile.x;
        int my = (int)rb->my_missile.y;
        
        if(mx >= 0 && mx < GRID_SIZE && my >= 0 && my < GRID_SIZE) {
            grid[my][mx] = '*';
        }
    }
  if (t1->active == 1) {
    grid[t1->y][t1->x] = 'T';
  }
  for(int y = 0; y < 14; y++) {
    for(int x = 0; x < 14; x++) {
      printf("%c  " ,grid[y][x]);
    }
    printf("\n");
  }
  printf("Robot : %s | Pos : %.1f, %.1f %ddegree\n", rb->name , rb->y, rb->x,rb->heading);
}

void update_missile(Missile *m) {
    if (m->active == 1) {
        
        float rad = m->heading * (PI / 180.0);
        
        m->x += cos(rad) * m->speed;
        m->y += sin(rad) * m->speed;
        
        if (m->x < 0 || m->x >= GRID_SIZE || 
            m->y < 0 || m->y >= GRID_SIZE) {
            
            m->active = 0; 
        }
    }
}

int main() {
  hide_cursor();
  system("cls");
  int size = 1;
  Robot *rb1 = malloc(size * sizeof(Robot));
  rb1[0].id = 1;
  strcpy(rb1[0].name, "Megaman" );
  rb1->x = 7.0;
  rb1->y = 7.0;
  rb1->energy = 80;
  rb1->speed = 1;
  rb1->heading = 0;
  Target t1;
  t1.active = 1;
  t1.x = 10;
  t1.y = 10;
  for(int tick = 0; tick < 100; tick++) {
    motion(&rb1[0]);
    update_missile(&rb1[0].my_missile);
    show_map(&rb1[0],&t1);
    Sleep(100);

  }
  free(rb1);

  return 0;
}
