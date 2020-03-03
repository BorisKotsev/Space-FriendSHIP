#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::init(SDL_Renderer* renderer, string configFile)
{
    m_configFile = "config\\" + configFile;
    fstream stream;

    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_health;
    stream >> tmp >> m_spawn_x >> m_spawn_y;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_max_speed;
    stream >> tmp >> m_min_speed;
    stream >> tmp >> m_rotationAngle;
    stream >> tmp >> s_move_left;
    stream >> tmp >> s_move_right;
    stream >> tmp >> s_gas;
    stream >> tmp >> s_brake;

    stream.close();

    if(s_gas == "W")
    {
        gas = SDL_SCANCODE_W;
    }
    if(s_brake == "S")
    {
        brake = SDL_SCANCODE_S;
    }
    if(s_move_left == "A")
    {
        move_left = SDL_SCANCODE_A;
    }
    if(s_move_right == "D")
    {
        move_right = SDL_SCANCODE_D;
    }

    if(s_gas == "Up")
    {
        gas = SDL_SCANCODE_UP;
    }
    if(s_brake == "Down")
    {
        brake = SDL_SCANCODE_DOWN;
    }
    if(s_move_left == "Left")
    {
        move_left = SDL_SCANCODE_LEFT;
    }
    if(s_move_right == "Right")
    {
        move_right = SDL_SCANCODE_RIGHT;
    }

    m_img = "img\\" + m_img;
    m_objectRect.x = m_spawn_x;
    m_objectRect.y = m_spawn_y;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);

}

void Player::update()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    m_screen_speed = m_speed  * SPEED_FACTOR;

    if(state != NULL){

        if (state[gas])
        {
            m_speed ++;

            if(m_speed > m_max_speed)
            {
                m_speed = m_max_speed;
            }
        }
        else if(state[brake])
        {
            m_speed --;

            if(m_speed < m_min_speed)
            {
                m_speed = m_min_speed;
            }
        }
        else if(state[move_right])
        {
            m_rotationAngle += 5;
        }
        else if(state[move_left])
        {
            m_rotationAngle -= 5;
        }
    }

    m_objectRect.x += sin(m_rotationAngle * PI / 180) * m_screen_speed;
    m_objectRect.y -= cos(m_rotationAngle * PI / 180) * m_screen_speed;
}

void Player::draw(SDL_Renderer* renderer)
{
    SDL_Point center;
    center.x = 40;
    center.y = 0;

    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, &center, SDL_FLIP_NONE);
}
