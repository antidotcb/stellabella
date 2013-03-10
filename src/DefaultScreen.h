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

        void _addAsteroid() 
        {
            scene::IMeshSceneNode* asteroid = m_scene->addMeshSceneNode(m_asteroidMesh);
            if(asteroid) {
                asteroid->setPosition(core::vector3df(0,0,30));
                asteroid->setMaterialTexture(0, getGame()->getTextureByName("asteroid"));
                asteroid->setMaterialFlag(video::EMF_LIGHTING, false);
            }
            m_asteroids.push_back(asteroid);
        }

        virtual void leave();
        virtual void update( const f32 delta );

        virtual void init();

        virtual int getId() { return DefaultScreenID; }
    
    private:
        void _moveCamera();

        typedef std::vector<scene::ISceneNode *> AsteroidList;

        IAnimatedMesh * m_asteroidMesh;
        ICameraSceneNode * m_camera;
        AsteroidList m_asteroids;
    };

}