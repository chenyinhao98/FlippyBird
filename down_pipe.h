#include "splashkit.h"
#include <vector>

enum down_pipe_kind
{
    GREEN,
    ORANGE
};

struct down_pipe_data
{
    sprite      down_pipe_sprite;
    down_pipe_kind kind;
};

bitmap pipe_bitmap(down_pipe_kind kind);

down_pipe_data new_down_pipe();

void draw_pipe(const vector<down_pipe_data> &pipe_to_draw);

void update_pipe(vector<down_pipe_data> &pipe_to_update);

// void pipe_switch(vector<down_pipe_data> &pipe, vector<down_pipe_kind> target);

// void handle_input1(vector<down_pipe_data> &pipe_to_switch );