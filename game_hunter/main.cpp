
#include "CommonFunction.h"
#include "BaseObject.h"
#include "map.h"
#include "Player.h"
#include "Time.h"
#include "Mobs.h"
#include "Exp.h"
#include "TextObject.h"
#include "stats.h"
#include "Bullet.h"
#include <SDL_mixer.h>
#define USE_AUDIO
BaseObject g_background;
TTF_Font* g_font_text = NULL;
TTF_Font* g_font_MENU = NULL;



bool InitData()
{
    bool success = true;
    int ret = SDL_Init( SDL_INIT_VIDEO);
    if(ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("HUNTER ",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(g_window == NULL )
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }


    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,2048)==-1)
    {
        success= false;
    }
    gsound1=Mix_LoadWAV("sound//sound1.wav");
    gsound2=Mix_LoadWAV("sound//sound2.wav");
    gsound3=Mix_LoadWAV("sound//sound3.wav");
    gsound4=Mix_LoadWAV("sound//sound4.wav");
      if((gsound1==NULL) || (gsound2 == NULL)||(gsound3==NULL)||(gsound4==NULL))
      {
       success= false;
      }

        g_font_text = TTF_OpenFont("font//dlxfont.ttf", 15);
        if (g_font_text == NULL)
        {
            success= false;
        }

        g_font_MENU = TTF_OpenFont("font//dlxfont.ttf", 50);
        if (g_font_MENU == NULL)
        {
            success= false;
        }

    }

    return success;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;
    Mix_FreeChunk(gsound1);
    Mix_FreeChunk(gsound2);
    Mix_FreeChunk(gsound3);
    Mix_FreeChunk(gsound4);
    Mix_CloseAudio();

    IMG_Quit();
    SDL_Quit();

}



bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false)
    {
        return false;
    }

    return true;


}

std::vector<Mobs*> MakeThreadList()
{

    std::vector<Mobs*> list_threats;

   Mobs* mob1 = new Mobs[20];

    for (int i = 0; i < 20; i++)
    {
        Mobs* mob = (mob1+i);
        if (mob!= NULL)
        {
            mob->LoadImg("img//mob_left.png", g_screen);
            mob->set_clips();
            mob->InitPlayer();
            mob->set_xpos(430  + i*550);
            mob->set_ypos(150);
            mob->set_type_move(Mobs::MOVE_IN_SPACE_TH);
            int pos1 = mob->get_x_pos() - 60;
            int pos2 = mob->get_x_pos() + 60;
            mob->SetAnimationPos(pos1, pos2);
            Bullet* p_bullet = new Bullet();
            mob->InitBullet(p_bullet, g_screen,1);
            list_threats.push_back(mob);
        }
    }
   Mobs* mob2 = new Mobs[15];

    for (int i = 0; i < 15; i++)
    {
       Mobs* mob1 = (mob2+i);
        if (mob1 != NULL)
        {
            mob1->LoadImg("img//mob_left1.png", g_screen);
            mob1->set_clips();
            mob1->InitPlayer();
            mob1->set_xpos(830  + i*1600);
            mob1->set_ypos(150);
            mob1->set_type_move(Mobs::MOVE_1);
            int pos3 = mob1->get_x_pos() - 60;
            int pos4 = mob1->get_x_pos() + 60;
            mob1->SetAnimationPos(pos3, pos4);
            list_threats.push_back(mob1);
        }

    }
    Mobs* mob3 = new Mobs[9];

    for (int i = 0; i < 9; i++)
    {
       Mobs* mob2 = (mob3+i);
        if (mob2 != NULL)
        {
           mob2->LoadImg("img//mob_left2.png", g_screen);
           mob2->set_clips();
           mob2->InitPlayer();
           mob2->set_xpos(4550 + i*1700);
           mob2->set_ypos(150);
           mob2->set_type_move(Mobs::MOVE_2);
           int pos5 = mob2->get_x_pos() - 60;
           int pos6 = mob2->get_x_pos() + 60;
           mob2->SetAnimationPos(pos5, pos6);
           Bullet* p_bullet = new Bullet();
           mob2->InitBullet(p_bullet, g_screen,2);
           list_threats.push_back(mob2);
        }

    }

    return list_threats;
}

int main(int argc, char* argv[])
{
     Time fps;
    //Start up SDL and create window
    if (InitData() == false)
    {
        return -1;
    }


    if(!LoadBackground())
    {
        return -1;
    }
     bool bsuccess=false;
    int ret_menu = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU, "Play", "Exit", "img//b3.png");
    if (ret_menu == 0)
    {
        bsuccess = true;
    }
    else
    {
           bsuccess=false;
           g_background.Free();
           close();
           SDL_Quit();
           return 0;
    }


    GameMap game_map;
    game_map.LoadMap("map//map.dat ");
    game_map.LoadMapTiles(g_screen);

    Player p_player;
    p_player.LoadImg(g_name_main_right, g_screen);
    p_player.set_clips();


    power player_power;
    player_power.Init(g_screen);


    money player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

    money1 player_money1;
    player_money1.Init(g_screen);
    player_money1.SetPos(SCREEN_WIDTH*0.5+ 210  ,8);



    std::vector<Mobs*> threats_list = MakeThreadList();

    Exp exp_threats;
    Exp exp_main;

    bool ret = exp_threats.LoadImg("img//exp3.png", g_screen);
    exp_threats.set_clips();
    if (!ret) return -1;


    ret = exp_main.LoadImg("img//exp3.png", g_screen);
    exp_main.set_clips();
    if (!ret) return 0;

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);

    TextObject money_count;
    money_count.setColor(TextObject::WHITE_TEXT);

    TextObject money1;
    money1.setColor(TextObject::WHITE_TEXT);

   int live = 0;
   unsigned int mark_value = 0;
   TextObject time_game;
   time_game.setColor(TextObject::WHITE_TEXT);

    bool quit = false;
    while(!quit)
    {
        fps.start();

        while( SDL_PollEvent(&g_event) != 0 )
        {
            //User requests quit
            if(g_event.type == SDL_QUIT )
            {
                quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen,gsound1);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map ga_map = game_map.GetMap();
        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(ga_map.start_x_, ga_map.start_y_);
        p_player.MovePlayer(ga_map);
        p_player.Show(g_screen);


        game_map.SetMap(ga_map);
       game_map.DrawMap(g_screen);

       player_power.Show(g_screen);
       player_money.Show(g_screen);
       player_money1.Show(g_screen);

       std::string str_time = "Time: ";
       Uint32 time_val = SDL_GetTicks() / 1000;
       Uint32 val_time = 200 - time_val;


       for (int i = 0; i < threats_list.size(); i++)
       {
           Mobs* mobs = threats_list.at(i);
           mobs->SetMapXY(ga_map.start_x_, ga_map.start_y_);
           mobs->ImpMoveType(g_screen);
           mobs->DoPlayer(ga_map);
           mobs->Show(g_screen);
           mobs->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);


           SDL_Rect rect_player = p_player.GetRectFrame();

           //COLLISION MOBS BULLET -> PLAYER
           bool is_col1 = false;
           std::vector<Bullet*> bullet_list =mobs->get_bullet_list();
           for (int am = 0; am < bullet_list.size(); am++)
           {
               Bullet* p_bullet = bullet_list.at(am);
               if (p_bullet)
               {
                   is_col1 = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), rect_player);
                   if (is_col1 == true)
                   {
                       mobs->ResetBullet(p_bullet);
                       break;
                   }
               }
           }

           SDL_Rect rect_threat = mobs->GetRectFrame();
           bool is_col2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat);

           if (is_col2 || is_col1)
           {

               int width_exp_frame = exp_main.get_frame_height();
               int heiht_exp_height = exp_main.get_frame_width();
               for (int ex = 0; ex < 8; ex++)
               {
                    int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                    int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                   exp_main.set_frame(ex);
                   exp_main.SetRect(x_pos, y_pos);
                   exp_main.Show(g_screen);
                   SDL_RenderPresent(g_screen);
               }



 #ifdef USE_AUDIO
         Mix_PlayChannel(-1,gsound3, 0);

#endif
              live++;
               if (live<=4)
              {
                   p_player.SetRect(0,0);
                   p_player.set_think_time(40);
                   SDL_Delay(1000);
                   player_power.Decrease();
                   player_power.Render(g_screen);
                   continue;

               }

               else
               {
                int ret_menu1 = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU,
                                                   "Exit"," ","img//b1.png");
                 if (ret_menu1 == 0)
                 {
                   quit=true;
                   g_background.Free();
                   mobs->Free();
                   close();
                   SDL_Quit();
                   return 0;
               }
           }
       }

       }
       //COLLISION  PLAYER'S BULLET -> MOBS
       std::vector<Bullet*> bullet_arr = p_player.get_bullet_list();
       int frame_exp_width = exp_threats.get_frame_width();
       int frame_exp_height = exp_threats.get_frame_width();
       for (int am = 0; am < bullet_arr.size(); am++)
       {
           Bullet* p_bullet = bullet_arr.at(am);

           if (p_bullet)
           {
               for (int i = 0; i < threats_list.size(); i++)
               {
                   Mobs* mobs = threats_list.at(i);

                   SDL_Rect threat_rect;
                   threat_rect.x = mobs->GetRect().x;
                   threat_rect.y = mobs->GetRect().y;
                   threat_rect.w = mobs->get_width_frame();
                   threat_rect.h = mobs->get_height_frame();

                   bool is_col = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), threat_rect);
                   if (is_col)
                   {
                       mark_value++;
                       for (int ex = 0; ex < 8; ex++)
                       {
                           int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                           int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                           exp_threats.set_frame(ex);
                           exp_threats.SetRect(x_pos, y_pos);
                           exp_threats.Show(g_screen);
                       }


                           p_player.RemoveBullet(am);
                           mobs->Free();
                           threats_list.erase(threats_list.begin() + i);

#ifdef USE_AUDIO
                     Mix_PlayChannel(-1, gsound4, 0);
#endif
                   }
               }

           }
       }

      if(val_time<=0)
      {
     #ifdef USE_AUDIO
     Mix_PlayChannel(-1,gsound2,0);
     #endif
        int ret_menu2 = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU,
                                                   "Exit", " ","img//b2.png");
                 if (ret_menu2 == 0)
                 {
                   quit=true;
                    break;
               }

      }
      else
     {
          std::string str_val = std::to_string(val_time);
           str_time += str_val;

           time_game.SetText(str_time);
           time_game.loadFromRenderedText(g_font_text, g_screen);
           time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
      }
       std::string val_str_mark = std::to_string(mark_value);
       std::string strMark("Score: ");
       strMark += val_str_mark;

       mark_game.SetText(strMark);
       mark_game.loadFromRenderedText(g_font_text, g_screen);
       mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

       int money_val = p_player.GetMoneyCount();
       std::string money_count_str = std::to_string(money_val);
       money_count.SetText(money_count_str);
       money_count.loadFromRenderedText(g_font_text, g_screen);
       money_count.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

       int money_val1 = p_player.GetPower();
       std::string money1_str = std::to_string(money_val1);
       money1.SetText(money1_str);
       money1.loadFromRenderedText(g_font_text, g_screen);
       money1.RenderText(g_screen, SCREEN_WIDTH*0.5 + 250 , 15);



        //Update screen
        SDL_RenderPresent(g_screen);

        int imp_time = fps.get_ticks();
        int time_for_one_frame = 1000/FRAMES_PER_SECOND;
        if(imp_time < time_for_one_frame)
        {
            SDL_Delay(time_for_one_frame - imp_time);
        }
         bool win = p_player.GetIsWin();
        if(win==true)
        {
         int ret_menu3 = SDLCommonFunction::ShowMenu(g_screen, g_font_MENU, "Exit", " ", "img//b4.png");
        if (ret_menu3 == 0)
        {
         quit = true;
         break;
         g_background.Free();
         close();
         SDL_Quit();

        }

        }
    }


    for (int i = 0; i < threats_list.size(); i++)
    {
        Mobs* p_mobs = threats_list.at(i);
        p_mobs->Free();
        p_mobs = NULL;
    }

    threats_list.clear();

    close();

    return 0;
}
