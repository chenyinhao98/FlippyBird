#include "splashkit.h"
#include <vector>

enum up_pipe_kind
{
    GREEN1,
    ORANGE1
};

struct up_pipe_data
{
    sprite      up_pipe_sprite;
    up_pipe_kind kind;
};

bitmap pipe_bitmap(up_pipe_kind kind);

up_pipe_data new_up_pipe();

void draw_pipe(const vector<up_pipe_data> &pipe_to_draw);

void update_pipe(vector<up_pipe_data> &pipe_to_update);

// void pipe_switch(vector<up_pipe_data> &pipe, vector<up_pipe_kind> target);

// void handle_input1(vector<up_pipe_data> &pipe_to_switch );