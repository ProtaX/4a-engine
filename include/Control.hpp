#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <mutex>

namespace fae
{

class KeyPressed
{
    int left;
    int right;
    int up;
    int down;
    int interaction;
    int data;

public:
    KeyPressed(int left, int right, int up, int down, int interaction);
    ~KeyPressed() { }
    void action(int key);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void do_interaction();
    int getData();
    void setData(int newData);
};

} // namespace fae
