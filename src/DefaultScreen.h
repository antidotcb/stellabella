#pragma once

#include <irrlicht.h>
using namespace irr;

#include "Screen.h"
#include "Asteroid.h"

namespace stellabellum {

    class DefaultScreen: public Screen {
    public:    
        static const int DefaultScreenID = 0;
        
        DefaultScreen(void);

        virtual void enter();

        void addRocket();

        virtual void leave();
        virtual void update( const f32 delta );

        virtual void init();

        virtual int getId() { return DefaultScreenID; }
    
    private:
        void moveCamera();
        void movePlayer(const f32 delta);

        IRandomizer * m_random;
        IAnimatedMesh * m_asteroidMesh;
        IAnimatedMesh * m_playerMesh;
        IAnimatedMesh * m_rocketMesh;
        IAnimatedMesh * m_enemyMeshes[4];
        ICameraSceneNode * m_camera;
        
        ISceneNode * m_player;

        u32 m_lastAsteroid;
    };

}