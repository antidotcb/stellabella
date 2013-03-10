#include "StdAfx.h"
#include "DefaultScreen.h"

namespace stellabellum {

    DefaultScreen::DefaultScreen( void ) : Screen(), m_asteroidMesh(0) {
        m_bgColor = video::SColor(255, 128, 128, 128);
    }

    void DefaultScreen::enter() {
        m_camera = m_scene->addCameraSceneNodeFPS();
        
        _addAsteroid();


        getGame()->getDevice().setInputReceivingSceneManager(m_scene);
    }

    void DefaultScreen::leave() {
        
    }

    void DefaultScreen::update(const f32 delta) {
        AsteroidList::iterator it;
        for(it = m_asteroids.begin(); it != m_asteroids.end(); ++it) {
            scene::ISceneNode * node = *it;
            //node.setPosition(
        }

        _moveCamera();

    }

    void DefaultScreen::init() {
        Screen::init();
        m_asteroidMesh = m_scene->getMesh("d:\\xpn_2013\\export\\asteroid.X");
    }

    void DefaultScreen::_moveCamera()
    {
        const f32 movementAmount = 0.005f;

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

}