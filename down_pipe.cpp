#include "down_pipe.h"
#include "splashkit.h"

#define RANGEX 10000
#define RANGEY 500

bitmap pipe_bitmap(down_pipe_kind kind)
{
    switch (kind)
    {
    case GREEN:
        return bitmap_named("pipe_up");
    case ORANGE:
        return bitmap_named("pipe2_up");
    }
}

down_pipe_data new_down_pipe()
{
    down_pipe_data result;
    bitmap default_bitmap = pipe_bitmap(GREEN);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the pipe kind selected
    result.down_pipe_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.down_pipe_sprite, pipe_bitmap(GREEN), "pipe_up");
    sprite_add_layer(result.down_pipe_sprite, pipe_bitmap(ORANGE), "pipe2_up");

    // Default to layer 0 = YELLOW so hide others
    sprite_hide_layer(result.down_pipe_sprite, 1);
    sprite_hide_layer(result.down_pipe_sprite, 2);

    result.kind = GREEN;

    // Position in the centre of the initial screen
    sprite_set_x(result.down_pipe_sprite, rnd(RANGEX));
    sprite_set_y(result.down_pipe_sprite, rnd(RANGEY) + 225);

    return result;
}

void draw_pipe(const vector<down_pipe_data> &pipe_to_draw)
{
    int length = pipe_to_draw.size();
    for(int i = 0; i < length; i++)
    {
        draw_sprite(pipe_to_draw[i].down_pipe_sprite);
    }
    
}

void update_pipe(vector<down_pipe_data> &pipe_to_update)
{
    int length = pipe_to_update.size();
    for(int i = 0; i < length; i++)
    {
        update_sprite(pipe_to_update[i].down_pipe_sprite);
    }
    // Apply movement based on rotation and velocity in the sprite
}

// void pipe_switch(vector<down_pipe_data> &pipe, vector<down_pipe_kind> target)
// {
//     // only do this if there is a change
//     int length = pipe.size();
//     for(int i = 0; i < length; i++)
//     {
//         if (pipe.kind != target)
//         {
//             sprite_show_layer(pipe.down_pipe_sprite, static_cast<int>(target));
//             sprite_hide_layer(pipe.down_pipe_sprite, static_cast<int>(pipe.kind));

//             pipe.kind = target;
//         }
//     }
// }
// void handle_input1(vector<down_pipe_data> &pipe_to_switch )
// {
//     if (key_typed(Q_KEY))
//     {
//         int length = pipe_to_switch.size();
//         for(int i = 0; i < length; i++)
//         {
//             pipe_switch(pipe_to_switch,ORANGE);
//         }
//     }
    
//     if (key_typed(E_KEY))
//     {
//         int length = pipe_to_switch.size();
//         for(int i = 0; i < length; i++)
//         {
//             pipe_switch(pipe_to_switch,GREEN);
//         }
//     }
// }