#include "feature.h"
#include "splashkit.h"

bitmap feature_bitmap(feature_kind feature)
{
    switch(feature)
    {
        case ZERO: return bitmap_named("font_048");
        case ONE: return bitmap_named("font_049");
        case TWO: return bitmap_named("font_050");
        case THREE: return bitmap_named("font_051");
        case FOUR: return bitmap_named("font_052");
        case FIVE: return bitmap_named("font_053");
        case SIX: return bitmap_named("font_054");
        case SEVEN: return bitmap_named("font_055");
        case EIGHT: return bitmap_named("font_056");
        case NINE: return bitmap_named("font_057");
    }
}

feature_data new_feature(double x,double y)
{
    feature_data result;
    result.kind=static_cast<feature_kind>(rnd(10));
    result.feature_sprite=create_sprite(feature_bitmap(result.kind));
    sprite_set_x(result.feature_sprite, x);
    sprite_set_y(result.feature_sprite, y);
    sprite_set_dx(result.feature_sprite,1.2);
    sprite_set_dy(result.feature_sprite,rnd() * 4 - 2);
    return result;
}


void draw_feature(const vector<feature_data> &feature_to_draw)
{
    int length=feature_to_draw.size();
    for(int i = 0; i < length; i++)
    {
        draw_sprite(feature_to_draw[i].feature_sprite);
    }
}
void update_feature(vector <feature_data> &feature_to_update)
{
    int length = feature_to_update.size();
    for(int i = 0; i < length; i++)
    {
        update_sprite(feature_to_update[i].feature_sprite);
        if(sprite_x(feature_to_update[i].feature_sprite) >= 10000 || sprite_x(feature_to_update[i].feature_sprite) <= 300)
        {
            sprite_set_dx(feature_to_update[i].feature_sprite, -1 * sprite_dx(feature_to_update[i].feature_sprite));
        }
        if(sprite_y(feature_to_update[i].feature_sprite) >= 450 || sprite_y(feature_to_update[i].feature_sprite) <= 50)
        {
            sprite_set_dy(feature_to_update[i].feature_sprite, -1 * sprite_dy(feature_to_update[i].feature_sprite));
        }
               
    }
}