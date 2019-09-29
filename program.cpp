#include "splashkit.h"
#include "bird.h"
#include "feature.h"
#include "up_pipe.h"
#include "down_pipe.h"
#include "title.h"
#include <vector>
#include <iostream>
#define RESET   "\033[0m"
#define RED     "\033[31m" 

#define RANGEX 10000
#define RANGEY 500

bool game_end = false;

struct game_data
{
    bird_data bird;
    vector<up_pipe_data> up_pipe;
    vector<down_pipe_data> down_pipe;
    vector<feature_data> feature;
    title_data title;
};
void apply_feature(game_data &game)
{
    game.feature.push_back(new_feature(rnd(RANGEX + 300 ), rnd(RANGEY + 50)));
}

void remove_feature(game_data &game, int index)
{
    int length = game.feature.size();
    if(index >= 0 and index < length)
    {
        int last_idx;
        last_idx = length-1;
        game.feature[index] = game.feature[last_idx];
        game.feature.pop_back();
    }
}

void apply_pipe(game_data &game)
{
    game.up_pipe.push_back(new_up_pipe());
    game.down_pipe.push_back(new_down_pipe());
}

void remove_up_pipe(game_data &game, int index)
{
    int length = game.up_pipe.size();
    if(index >= 0 and index < length)
    {
        int last_idx;
        last_idx = length - 1;
        game.up_pipe[index] = game.up_pipe[last_idx];
        game.up_pipe.pop_back();
    }
}

void remove_down_pipe(game_data &game, int index)
{
    int length = game.down_pipe.size();
    if(index >= 0 and index < length)
    {
        int last_idx;
        last_idx = length-1;
        game.down_pipe[index] = game.down_pipe[last_idx];
        game.down_pipe.pop_back();
    }
}

void check_collisions_feature(game_data &game)
{
    int length = game.feature.size();
    for(int i = 0; i < length; i++)
    {
        if(sprite_collision(game.feature[i].feature_sprite,game.bird.bird_sprite))
        {
            switch(game.feature[i].kind)
            {
                case ZERO:
                {
                    game.bird.score += 0;
                    play_sound_effect(("point.wav"));
                    break;
                }
                case ONE:
                {
                    game.bird.score += 1;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case TWO:
                {
                    game.bird.score += 2;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case THREE:
                {
                    game.bird.score += 3;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case FOUR:
                {
                    game.bird.score += 4;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case FIVE:
                {
                    game.bird.score += 5;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case SIX:
                {
                    game.bird.score += 6;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case SEVEN:
                {
                    game.bird.score += 7;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case EIGHT:
                {
                    game.bird.score +=8;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
                case NINE:
                {
                    game.bird.score += 9;
                    play_sound_effect(sound_effect_named("point"));
                    break;
                }
            }
            apply_feature(game);
            remove_feature(game,i);

        }
    }
}

void check_collisions_up_pipe(game_data &game)
{
    int length = game.up_pipe.size();
    for(int i = 0; i < length; i++)
    {
        if(sprite_collision(game.up_pipe[i].up_pipe_sprite,game.bird.bird_sprite))
        {
            switch(game.up_pipe[i].kind)
            {
                case GREEN1:
                {
                    play_sound_effect(sound_effect_named("hit"));
                    game_end = true;
                    break;
                }
                case ORANGE1:
                {
                    play_sound_effect(sound_effect_named("hit"));
                    game_end = true;
                    break;
                }
            }
            remove_up_pipe(game,i);
        }
    }
}

void check_collisions_down_pipe(game_data &game)
{
    int length = game.down_pipe.size();
    for(int i = 0; i < length; i++)
    {
        if(sprite_collision(game.down_pipe[i].down_pipe_sprite,game.bird.bird_sprite))
        {
            switch(game.up_pipe[i].kind)
            {
                case GREEN:
                {
                    play_sound_effect(sound_effect_named("hit"));
                    game_end = true;
                    break;
                }
                case ORANGE:
                {
                    play_sound_effect(sound_effect_named("hit"));
                    game_end = true;
                    break;
                }
            }
            remove_down_pipe(game,i);
        }
    }
}

game_data new_game()
{
    game_data result;
    result.title = new_title();
    for(int i = 0; i < 80; i++)
    {
        apply_feature(result);
        apply_pipe(result);
    }
    result.bird = new_bird();
    
    return(result);
}
void update_game(game_data &result)
{
    update_title(result.title);
    check_collisions_feature(result);
    check_collisions_up_pipe(result);
    check_collisions_down_pipe(result);
    update_bird(result.bird);
    update_pipe(result.up_pipe);
    update_pipe(result.down_pipe);
    update_feature(result.feature); 
    
}
void draw_game(game_data &game)
{
    draw_bird(game.bird);
    draw_title(game.title);
    draw_feature(game.feature);
    draw_pipe(game.up_pipe);
    draw_pipe(game.down_pipe);
    
}

void load_resources()
{
    load_resource_bundle("game_bundle", "flippy_bird.txt");
    load_sound_effect("die", "die.wav");
    load_sound_effect("point", "point.wav");
    load_sound_effect("hit", "hit.wav");
    load_sound_effect("fly", "fly.wav");
    load_sound_effect("panel", "panel.wav");
    load_music("bgm", "bgm.mp3");
}


void HUD(game_data game)
{
    draw_bitmap(bitmap_named("score_panel"), -50,-20, option_scale_bmp(0.5, 0.5, option_to_screen()));
    draw_text("  LOCATION: " + point_to_string(center_point(game.bird.bird_sprite)), COLOR_WHITE, 10, 480, option_to_screen());
    draw_text( to_string(game.bird.score), COLOR_RED, 100, 30, option_to_screen());
    if (game.bird.score >= 0 and game.bird.score < 25 )
    {
        draw_bitmap(bitmap_named("medals_3"), 14, 23, option_scale_bmp(0.5, 0.5, option_to_screen()));
    }
    if (game.bird.score >= 25 and game.bird.score < 50)
    {
        clear_bitmap(bitmap_named("medals_3"), COLOR_BLACK);
        draw_bitmap(bitmap_named("medals_2"), 14, 23, option_scale_bmp(0.5, 0.5, option_to_screen()));
    }
    if (game.bird.score >= 50 and game.bird.score < 75)
    {
        clear_bitmap(bitmap_named("medals_2"), COLOR_BLACK);
        draw_bitmap(bitmap_named("medals_1"), 14, 23, option_scale_bmp(0.5, 0.5, option_to_screen()));
    }
    if (game.bird.score >= 75)
    {
        clear_bitmap(bitmap_named("medals_1"), COLOR_BLACK);
        draw_bitmap(bitmap_named("medals_0"), 14, 23, option_scale_bmp(0.5, 0.5, option_to_screen()));
    }
    if(game_end == true)
        {
        delay(1000);
        draw_bitmap(bitmap_named("text_game_over"), 180, 200, option_to_screen());
        play_sound_effect(sound_effect_named("die"));
        }
    
}

void switch_background()
{
    
    draw_bitmap(bitmap_named("bg_day1"), -10, -10, option_to_screen());
    if (key_typed(NUM_4_KEY))
    draw_bitmap_on_bitmap(bitmap_named("bg_day1"), bitmap_named("bg_night"), 0, 0, option_to_screen());
}

string read_string(string prompt)
{
    string result;
    write_line(prompt);
    result = read_line();
    return result;
}

void game_start()
{
    cout << RED << " Game is Starting in... "<< RESET<< endl;
    cout << RED << " 3 "<< RESET<< endl;
    delay(1000);
    cout << RED << " 2 "<< RESET<< endl;
    delay(1000);
    cout << RED << " 1 "<< RESET<< endl;
    delay(1000);
}



int main()
{
    string answer;

    answer = read_string("== Do you want to start the game? ==");
    if (answer == to_lowercase("yes"))

    {
        game_start();
        open_window("FlippyBird", 550, 500);
        load_resources();
        game_data game = new_game();
        play_music(music_named("bgm.mp3"));
        set_music_volume(0.35);
        
        bitmap_set_cell_details(bitmap_named("lizard"), 40, 60, 4, 4, 16); 
        animation_script dance_script = load_animation_script("Script", "lizard.txt");
        animation test = create_animation(dance_script, "WalkFront");

        while ( not quit_requested() )
        {
            
            // Handle input to adjust bird movement
            process_events();
            handle_input(game.bird);
            title_switch(game.title);
            // handle_input1(game.pipe);
            update_game(game);




            // Update the animation
            update_animation(test);

            process_events();

            if ( key_typed(LEFT_KEY))
            {
                assign_animation(test, "WalkBack");
            }
            else if ( key_typed(RIGHT_KEY))
            {
                assign_animation(test, "WalkFront");
            }
        
            
            // Redraw everything
            clear_screen(COLOR_BLACK);
            
            switch_background();
            draw_bitmap(bitmap_named("lizard"), 20, 20, option_with_animation(test));
            draw_game(game);
            
            HUD(game);
            // including something stationary - it doesn't move
        
            refresh_screen(60);

            if(game_end == true)
            {
                delay(3000);
                break;
            }
            
        }
        return 0;
    }
}