#include "StdAfx.h"
#include "DefaultScreen.h"

namespace stellabellum {

    DefaultScreen::DefaultScreen( void ) : Screen(), m_asteroidMesh(0) {
        m_bgColor = video::SColor(255, 0, 0, 0);
    }

    void DefaultScreen::enter() {
        m_random = getGame()->getDevice().createDefaultRandomizer();

        m_scene->clear();

        m_camera = m_scene->addCameraSceneNodeFPS();
        
        int i = 100;
        while (--i) {
            _addAsteroid();
        }

        getGame()->getDevice().setInputReceivingSceneManager(m_scene);
    }

    void DefaultScreen::leave() {
        //getGame()->releaseInput();
    }

    void DefaultScreen::update(const f32 delta) {
        AsteroidList::iterator it;
        for(it = m_asteroids.begin(); it != m_asteroids.end(); ++it) {
            scene::ISceneNode * node = *it;
            

            //node.setPosition(
        }

        _moveCamera();

        irr::core::array<ISceneNode *> result;
        m_scene->getSceneNodesFromType(ESNT_ANY, result);
        
        if ((m_random->frand() > 0.95f) && ( result.size()< 100) ) {
            _addAsteroid();
        }
    }

    void DefaultScreen::init() {
        Screen::init();
        m_asteroidMesh = m_scene->getMesh("d:\\xpn_2013\\export\\asteroid.X");
    }

    void DefaultScreen::_moveCamera()
    {
        const f32 movementAmount = 0.5f;

        core::vector3df cameraPosition = m_camera->getPosition();
        core::vector3df direction = m_camera->getTarget() - cameraPosition;
        direction.normalize();

        core::vector3df movement;

        if (getGame()->getInput().isKeyPressed(KEY_KEY_W)) {
            movement += direction * movementAmount;
        }
        if (getGame()->getInput().isKeyPressed(KEY_KEY_S)) {
            movement += direction * -movementAmount;
        }
        if (getGame()->getInput().isKeyPressed(KEY_KEY_D)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction) * movementAmount;
        }
        if (getGame()->getInput().isKeyPressed(KEY_KEY_A)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction) * -movementAmount;
        }


        cameraPosition += movement;
        m_camera->setPosition(cameraPosition);
    }

    void DefaultScreen::_addAsteroid()
    {
        scene::IMeshSceneNode* asteroid = m_scene->addMeshSceneNode(m_asteroidMesh);
        if(asteroid) {
            asteroid->setPosition(core::vector3df(0,0,30));
            asteroid->setMaterialTexture(0, getGame()->getTextureByName("asteroid"));
            asteroid->setMaterialFlag(video::EMF_LIGHTING, false);
            core::vector3df start, end, rotation;
            start.X = (m_random->frand() - 0.5f) * 2000;
            start.Y = (m_random->frand() - 0.5f) * 2000;
            start.Z = (m_random->frand() - 0.5f) * 2000;

            end.X = (m_random->frand() - 0.5f) * 200;
            end.Y = (m_random->frand() - 0.5f) * 200;
            end.Z = (m_random->frand() - 0.5f) * 200;

            rotation.X = (m_random->frand() - 0.5f) * core::PI / (m_random->frand() * 15);
            rotation.Y = (m_random->frand() - 0.5f) * core::PI / (m_random->frand() * 15);
            rotation.Z = (m_random->frand() - 0.5f) * core::PI / (m_random->frand() * 15);

            f32 dist = end.getDistanceFrom(start);

            f32 speed = (5.0f + m_random->frand() * 25.0f);

            u32 timeToFly = static_cast<u32>((dist/speed) * 1000);

            asteroid->addAnimator(m_scene->createFlyStraightAnimator(start, end, timeToFly, false, true));
            asteroid->addAnimator(m_scene->createDeleteAnimator(timeToFly * 10));
            asteroid->addAnimator(m_scene->createRotationAnimator(rotation));

            m_asteroids.push_back(asteroid);
        }
    }

}