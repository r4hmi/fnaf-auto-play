#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include <ctime>

using namespace std;

bool program_on = true;

int x_pos; int y_pos;
int x_goal; int y_goal;

int cursor_spd = 5;
int millisec_delay = 1;
int repeat_delay;

int target_id;
int cicle_times;
int click_delay;

bool reached_target;
int cam_id = 0;

int turn_off()
{
    program_on = false;
    return 0;
}


int rand_id()
{
    return target_id = rand() % 5;
}


void cursor_loc_id()
{
    while(program_on)
    {       
        switch(target_id)
        {
                case 0: x_goal = 1230; y_goal = 500; break;
                
                case 1: x_goal = 1230; y_goal = 350; break;

                case 2: x_goal = 50; y_goal = 500; break;
                
                case 3: x_goal = 50; y_goal = 350; break;
                
                case 4:
                x_goal = 650; y_goal = 700; 
                this_thread::sleep_for(chrono::milliseconds(3000));
                x_goal = 950; y_goal = 470;
                cout << x_goal << " " << y_goal << " ";
                this_thread::sleep_for(chrono::milliseconds(3000));
                x_goal = 650; y_goal = 700;
                this_thread::sleep_for(chrono::milliseconds(3000));
                target_id = rand() % 4;

                default: x_goal = 650; y_goal = 450; break;
                
        }    }
}

int main()
{
    srand(time(NULL));
    rand_id();

    x_pos = 700; y_pos = 400;
    thread cursor_thread(cursor_loc_id);

    while (program_on)
    {

        if(x_pos - x_goal > 10 || x_pos - x_goal < -10)
        {
            x_pos < x_goal ? x_pos += cursor_spd : x_pos -= cursor_spd;
        }
        if(y_pos - y_goal > 10 || y_pos - y_goal < -10)
        {
            y_pos < y_goal ? y_pos += cursor_spd : y_pos -= cursor_spd;
        }
        
        if(click_delay > (target_id + rand() % 100) + 100)
        {
            cout << "mouse clicked ";
            click_delay = 0;
            mouse_event(MOUSEEVENTF_LEFTDOWN, x_pos, y_pos, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, x_pos, y_pos, 0, 0);
        }
        
        if(x_pos - x_goal <= 10 && x_pos - x_goal >= -10)
        {
            if(y_pos - y_goal <= 10 && y_pos - y_goal >= -10)
            {

                if(cicle_times > (target_id + 150) && target_id != 4)
                {
                    rand_id();
                    cicle_times = 0;
                }

            }
        }
        
        cicle_times++;
        click_delay++;

        SetCursorPos(x_pos,y_pos);
        this_thread::sleep_for(chrono::milliseconds(millisec_delay));

        if(GetAsyncKeyState(VK_NUMPAD0))
        {
            turn_off();
        }
        
    }
    
return 0;
}
