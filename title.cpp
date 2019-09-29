#include "title.h"
#include "splashkit.h"

bitmap title_bitmap()
{
            return bitmap_named("title");
}
bitmap text_ready_bitmap()
{
            return bitmap_named("text_ready");
}
bitmap tutorial_bitmap()
{
            return bitmap_named("tutorial");
}

title_data new_title()
{
    title_data result;
    bitmap bitmap1 = title_bitmap();
    bitmap bitmap2 = text_ready_bitmap();
    bitmap bitmap3 = tutorial_bitmap();

    // Create the sprite with 3 layers - we can turn on and off based
    // on the title kind selected
    result.title_sprite = create_sprite(bitmap1);
    result.text_ready_sprite = create_sprite(bitmap2);
    result.tutorial_sprite = create_sprite(bitmap3);

    sprite_hide_layer(result.title_sprite, 1);
    sprite_hide_layer(result.text_ready_sprite, 1);
    sprite_hide_layer(result.tutorial_sprite, 1);


    // Position in the centre of the initial screen
    sprite_set_x(result.title_sprite, -75);
    sprite_set_y(result.title_sprite, 20);
    sprite_set_x(result.text_ready_sprite, -80);
    sprite_set_y(result.text_ready_sprite, 100);
    sprite_set_x(result.tutorial_sprite, -34);
    sprite_set_y(result.tutorial_sprite, 238);

    sprite_set_dx(result.title_sprite, BIRD_SPEED);
    sprite_set_dx(result.text_ready_sprite, BIRD_SPEED);
    sprite_set_dx(result.tutorial_sprite, BIRD_SPEED);
    return result;
}

void draw_title(const title_data &title_to_draw)
{
    draw_sprite(title_to_draw.title_sprite);
    draw_sprite(title_to_draw.text_ready_sprite);
    draw_sprite(title_to_draw.tutorial_sprite);
}

void update_title(title_data &title_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(title_to_update.title_sprite);
    update_sprite(title_to_update.text_ready_sprite);
    update_sprite(title_to_update.tutorial_sprite);
}

void title_switch(title_data &title)
{
    // only do this if there is a change
    if (mouse_clicked(LEFT_BUTTON))
    {
        sprite_hide_layer(title.title_sprite, static_cast<int>(0));
        sprite_hide_layer(title.text_ready_sprite, static_cast<int>(0));
        sprite_hide_layer(title.tutorial_sprite, static_cast<int>(0));

        // remember what is currently shown
    }
}
