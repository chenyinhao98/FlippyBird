#include "splashkit.h"
#include <vector>

#define BIRD_SPEED 3


struct title_data
{
    sprite title_sprite;
    sprite text_ready_sprite;
    sprite tutorial_sprite;
};

bitmap title_bitmap();

title_data new_title();

void draw_title(const title_data &title_to_draw);

void update_title(title_data &title_to_update);

void title_switch(title_data &title);