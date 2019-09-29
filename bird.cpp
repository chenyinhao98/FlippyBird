#include "splashkit.h"
#include "bird.h"
using namespace std;

bitmap bird_bitmap(bird_kind kind)
{
    switch (kind)
    {
    case YELLOW:
        return bitmap_named("bird0_0");
    case BLUE:
        return bitmap_named("bird1_0");
    default:
        return bitmap_named("bird2_0");
    }
}

bird_data new_bird()
{
    bird_data result;
    bitmap default_bitmap = bird_bitmap(YELLOW);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the bird kind selected
    result.bird_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.bird_sprite, bird_bitmap(BLUE), "bird1_0");
    sprite_add_layer(result.bird_sprite, bird_bitmap(RED), "bird2_0");

    // Default to layer 0 = YELLOW so hide others
    sprite_hide_layer(result.bird_sprite, 1);
    sprite_hide_layer(result.bird_sprite, 2);

    result.kind = YELLOW;

    // Position in the centre of the initial screen
    sprite_set_x(result.bird_sprite, 0);
    sprite_set_y(result.bird_sprite, (screen_height()-sprite_height(result.bird_sprite))/2);

    sprite_set_dx(result.bird_sprite, BIRD_SPEED);

    return result;
}

void draw_bird(const bird_data &bird_to_draw)
{
    draw_sprite(bird_to_draw.bird_sprite);
}

void update_bird(bird_data &bird_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(bird_to_update.bird_sprite);


    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the bird
    point_2d sprite_center = center_point(bird_to_update.bird_sprite);


    // Test top/bottom of screen
    if (sprite_center.y < top_edge)
    {
        sprite_center.y = top_edge;
    }
    else if (sprite_center.y > bottom_edge)
    {
        sprite_center.y = bottom_edge;
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

void bird_switch(bird_data &bird, bird_kind target)
{
    // only do this if there is a change
    if (bird.kind != target)
    {
        // show then hide layers
        sprite_show_layer(bird.bird_sprite, static_cast<int>(target));
        sprite_hide_layer(bird.bird_sprite, static_cast<int>(bird.kind));

        // remember what is currently shown
        bird.kind = target;
    }
}

void handle_input(bird_data &bird)
{
    // Allow the bird to switch ships
    if (key_typed(NUM_1_KEY))
        bird_switch(bird, YELLOW);
    if(key_typed(NUM_2_KEY))
        bird_switch(bird, BLUE);
    if (key_typed(NUM_3_KEY))
        bird_switch(bird, RED);

    // Handle movement - rotating left/right and moving forward/back
    float rotation = sprite_rotation(bird.bird_sprite);
    

    // Allow rotation with left/right keys
    if (key_down(UP_KEY))
        {
            sprite_set_rotation(bird.bird_sprite, rotation - BIRD_ROTATE_SPEED);
            play_sound_effect(sound_effect_named("fly"),1,0.2);
        }
    if (key_down(DOWN_KEY))
            sprite_set_rotation(bird.bird_sprite, rotation + BIRD_ROTATE_SPEED);
    //    float y = sprite_y(bird.bird_sprite);
    // if (mouse_clicked(LEFT_BUTTON))
    // {
    //     sprite_set_y(bird.bird_sprite, y + 10);

    //     sprite_set_y(bird.bird_sprite, (y + 10) - 10);
        
    // }
}
