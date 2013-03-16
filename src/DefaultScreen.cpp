#include "StdAfx.h"
#include "stellabellum.h"
#include "DefaultScreen.h"
#include "Asteroid.h"
#include "World.h"
#include "Input.h"


namespace stellabellum {

    DefaultScreen::DefaultScreen( void ) : Screen() {
        setBgColor(video::SColor(255, 0, 0, 0));
    }

    void DefaultScreen::enter() {
        getScene()->clear();

        ICameraSceneNode* camera = getScene()->addCameraSceneNode();
        m_world = new game::World(camera);

        m_world->init(getContainer(), getScene());

        m_random = getContainer()->getDevice()->createDefaultRandomizer();
    }

    void DefaultScreen::leave() {
        m_random->drop();
        m_random = 0;

        delete m_world;

        getScene()->clear();
    }

    void DefaultScreen::update(const f32 delta) {        
        /*if (getContainer()->getInput()->isKeyPressed(KEY_BACK)) {
            leave();
            enter();
        }*/

        m_world->update(getContainer(), delta);
    }

    void DefaultScreen::init() {
        Screen::init();        
        
        /*m_asteroidMesh = getScene()->getMesh("d:\\xpn_2013\\export\\asteroid.X");

        m_playerMesh = getScene()->getMesh();

        m_enemyMeshes[0] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_01.X");
        m_enemyMeshes[1] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_02.X");
        m_enemyMeshes[2] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_03.X");
        m_enemyMeshes[3] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_04.X");

        m_rocketMesh = getScene()->getMesh("d:\\xpn_2013\\export\\rocket.X");*/
    }

    /*
    void DefaultScreen::moveCamera() {
        const f32 movementAmount = 0.5f;

        core::vector3df cameraPosition = m_camera->getPosition();
        core::vector3df direction = m_camera->getTarget() - cameraPosition;
        direction.normalize();

        core::vector3df movement;

        if (getGame()->getInput()->isKeyPressed(KEY_KEY_W)) {
            movement += direction* movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_S)) {
            movement += direction* -movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_D)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction)* movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_A)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction)* -movementAmount;
        }

        cameraPosition += movement;
        m_camera->setPosition(cameraPosition);
    }

    void DefaultScreen::addRocket()
    {
         ISceneNode* asteroid = new Asteroid(0, getScene()->getRootSceneNode(), getScene(), -1, m_rocketMesh, getGame()->getRocketTexture("asteroid"));
        
        if(asteroid) {
            core::vector3df start, end, rotation;

            start = m_player->getPosition();

            end = start;
            end.Y += 600;            

            rotation.X = 0;//(m_random->frand() - 0.5f)* core::PI / (1.0f + m_random->frand()* 5.0f);
            rotation.Y = (m_random->frand() - 0.5f)* core::PI / (1.0f + m_random->frand()* 5.0f);
            rotation.Z = 0;//(m_random->frand() - 0.5f)* core::PI / (1.0f + m_random->frand()* 5.0f);

            f32 dist = end.getDistanceFrom(start);

            f32 speed = (300.0f + m_random->frand()* 100.0f);

            u32 timeToFly = static_cast<u32>((dist/speed)* 1000);

            scene::ISceneNodeAnimator *flyAnim = getScene()->createFlyStraightAnimator(start, end, timeToFly, false, true);
            scene::ISceneNodeAnimator *hideAnim = getScene()->createDeleteAnimator(timeToFly);
            scene::ISceneNodeAnimator *rotationAnim = getScene()->createRotationAnimator(rotation);

            asteroid->addAnimator(flyAnim);            
            asteroid->addAnimator(hideAnim);            
            asteroid->addAnimator(rotationAnim);

            flyAnim->drop();
            hideAnim->drop();
            rotationAnim->drop();

            asteroid->drop();
        }
    }

    
    */
}