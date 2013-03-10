#pragma once

#include <irrlicht.h>
using namespace irr;

#include "Screen.h"

namespace stellabellum {
    class DefaultScreen: public Screen {
    public:
    
        static const int DefaultScreenID = 0;
        
        DefaultScreen(void);

        virtual void enter();

        void _addAsteroid();

        virtual void leave();
        virtual void update( const f32 delta );

        virtual void init();

        virtual int getId() { return DefaultScreenID; }
    
    private:
        void _moveCamera();

        typedef std::vector<scene::ISceneNode *> AsteroidList;
        
        IRandomizer * m_random;
        IAnimatedMesh * m_asteroidMesh;
        ICameraSceneNode * m_camera;
        AsteroidList m_asteroids;
    };

}