#include "splashkit.h"
#include <vector>


enum feature_kind
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

struct feature_data
{
    feature_kind kind;
    sprite feature_sprite;
};

bitmap feature_bitmap(feature_kind powerup);

feature_data new_feature(double x,double y);

void draw_feature(const vector<feature_data> &feature_to_draw);

void update_feature(vector <feature_data> &feature_to_update);