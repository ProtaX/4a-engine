#include "Control.hpp"

namespace fae
{

    KeyPressed::KeyPressed(int left, int right, int up, int down, int interaction)
    {
        this->left = left;
        this->right = right;
        this->up = up;
        this->down = down;
        this->interaction = interaction;
        this->data = left;
        std::mutex g_mutex;
    }

    void KeyPressed::action(int key)
    {
        if (key == this->left)
            move_left;
        else if (key == this->right)
            move_right();
        else if (key == this->up)
            move_up();
        else if (key == this->down)
            move_down();
        else if (key == this->interaction)
            do_interaction();
    }

    void KeyPressed::move_left()
    {
        this->g_mutex.lock();

        if (currentKeyPressed == GLFW_KEY_D) {
                        //Изменяем поворот спрайта и отрисовываем следующий кадр
                        glUniform1i(orientationLocation, 1);
                        currentGlTexture = GL_TEXTURE1;
                        animationState = 0;
                        break;
                    } 
        glUniform1i(orientationLocation, -1);
        if (currentGlTexture - GL_TEXTURE0 >= animationFrames)
            currentGlTexture = GL_TEXTURE1;
        else
            currentGlTexture ++;
        model = glm::translate(model, heroGoLeft);
        orthCam.MoveCamera(heroGoRight);

        this->g_mutex.unlock();
    }
    void KeyPressed::move_right()
    {
        this->g_mutex.lock();
        glUniform1i(orientationLocation, 1);
        currentGlTexture = GL_TEXTURE1;
        animationState = 0;
        this->g_mutex.unlock();
    }
    void KeyPressed::move_up()
    {
        this->g_mutex.lock();

        this->g_mutex.unlock();
    }
    void KeyPressed::move_down()
    {
        this->g_mutex.lock();

        this->g_mutex.unlock();
    }
    void KeyPressed::do_interaction()
    {
        this->g_mutex.lock();

        this->g_mutex.unlock();
    }

    void KeyPressed::setData(int newData) {
        DWORD res = WaitForSingleObject(mtx, INFINITE);
        if (res == WAIT_OBJECT_0) {
            this->data = newData;
        }
        ReleaseMutex(mtx);
    }
    int KeyPressed::getData() {
        int ret = -1;
        DWORD res = WaitForSingleObject(mtx, INFINITE);
        if (res == WAIT_OBJECT_0) {
            ret = this->data;
        }
        ReleaseMutex(mtx);

        return ret;
    }
}
