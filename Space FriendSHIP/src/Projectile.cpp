#include "Projectile.h"

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::init(string configFile, struct coordinates coor, float rotation, SDL_Renderer* renderer)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_health;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_collisonDamage;
    stream >> tmp >> m_img;

    stream.close();
    m_rotationAngle = rotation;
    m_coor.x = coor.x + 25*(sin(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_coor.y = coor.y - 25*(cos(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_img = "img\\" + m_img;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}

void Projectile::update()
{
    m_coor.x += (sin(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_coor.y -= (cos(m_rotationAngle * PI / 180) * m_speed * SPEED_FACTOR);
    m_objectRect.x = (int)m_coor.x;
    m_objectRect.y = (int)m_coor.y;
}

void Projectile::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
    //SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, NULL, NULL, SDL_FLIP_NONE);
}

