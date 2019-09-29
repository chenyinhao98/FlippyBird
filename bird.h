
#include "splashkit.h"
using namespace std;


#define BIRD_SPEED 3
#define BIRD_ROTATE_SPEED 3
#define SCREEN_BORDER 275

enum bird_kind
{
    YELLOW,
    BLUE,
    RED
};


struct bird_data
{
    sprite      bird_sprite;
    bird_kind kind;
    int score = 0;
};

bird_data new_bird();

void draw_bird(const bird_data &bird_to_draw);

void update_bird(bird_data &bird_to_update);

void bird_switch(bird_data &bird, bird_kind target);

void handle_input(bird_data &bird);
