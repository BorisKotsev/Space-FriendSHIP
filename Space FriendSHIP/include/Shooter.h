#ifndef SHOOTER_H
#define SHOOTER_H

#include "Enemy.h"

class Shooter : public Enemy
{
    public:
        Shooter();
        virtual ~Shooter();

        virtual void init(string configFile, coordinates coor, float rotation, SDL_Renderer* renderer);
    protected:

    private:
};

#endif // SHOOTER_H