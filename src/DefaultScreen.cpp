#include "StdAfx.h"
#include "DefaultScreen.h"
#include "Entity.h"
#include "Asteroid.h"


namespace stellabellum {

    DefaultScreen::DefaultScreen( void ) : Screen(), m_asteroidMesh(0) {
        setBgColor(video::SColor(255, 0, 0, 0));
    }

    void DefaultScreen::enter() {
        getScene()->clear();
        m_camera = getScene()->addCameraSceneNode();
        m_camera->grab();
        m_camera->setPosition(vector3df(0,0,-300));


        m_player = new Asteroid(0, getScene()->getRootSceneNode(), getScene(), -1, m_playerMesh, getGame()->getPlayerTexture("player"), vector3df(0,-200,0));


        m_random = getGame()->getDevice()->createDefaultRandomizer();
    }

    void DefaultScreen::leave() {
        m_player->drop();
        m_player = 0;

        m_random->drop();
        m_random = 0;

        m_camera->drop();
        m_camera = 0;

        getScene()->clear();
    }

    void DefaultScreen::update(const f32 delta) {
        moveCamera();
        movePlayer(delta);

        if (getGame()->getInput()->isKeyPressed(KEY_BACK)) {
            leave();
            enter();
        }
    }

    void DefaultScreen::init() {
        Screen::init();        
        
        m_asteroidMesh = getScene()->getMesh("d:\\xpn_2013\\export\\asteroid.X");

        m_playerMesh = getScene()->getMesh("d:\\xpn_2013\\export\\fighter.X");

        m_enemyMeshes[0] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_01.X");
        m_enemyMeshes[1] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_02.X");
        m_enemyMeshes[2] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_03.X");
        m_enemyMeshes[3] = getScene()->getMesh("d:\\xpn_2013\\export\\enemies_04.X");

        m_rocketMesh = getScene()->getMesh("d:\\xpn_2013\\export\\rocket.X");
    }

    void DefaultScreen::moveCamera() {
        const f32 movementAmount = 0.5f;

        core::vector3df cameraPosition = m_camera->getPosition();
        core::vector3df direction = m_camera->getTarget() - cameraPosition;
        direction.normalize();

        core::vector3df movement;

        if (getGame()->getInput()->isKeyPressed(KEY_KEY_W)) {
            movement += direction * movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_S)) {
            movement += direction * -movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_D)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction) * movementAmount;
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_A)) {
            core::vector3df up = m_camera->getUpVector();
            movement += up.crossProduct(direction) * -movementAmount;
        }

        cameraPosition += movement;
        m_camera->setPosition(cameraPosition);
    }

    void DefaultScreen::addRocket()
    {
        ISceneNode * asteroid = new Asteroid(getGame(), getScene()->getRootSceneNode(), getScene(), -1, m_rocketMesh, getGame()->getRocketTexture("asteroid"));
        
        if(asteroid) {
            core::vector3df start, end, rotation;

            start = m_player->getPosition();

            end = start;
            end.Y += 600;            

            rotation.X = 0;//(m_random->frand() - 0.5f) * core::PI / (1.0f + m_random->frand() * 5.0f);
            rotation.Y = (m_random->frand() - 0.5f) * core::PI / (1.0f + m_random->frand() * 5.0f);
            rotation.Z = 0;//(m_random->frand() - 0.5f) * core::PI / (1.0f + m_random->frand() * 5.0f);

            f32 dist = end.getDistanceFrom(start);

            f32 speed = (300.0f + m_random->frand() * 100.0f);

            u32 timeToFly = static_cast<u32>((dist/speed) * 1000);

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

    void DefaultScreen::movePlayer(const f32 delta )
    {
        const f32 movementAmount = 0.5f;

        core::vector3df cameraPosition = m_player->getPosition();
        core::vector3df direction;// = m_camera->getTarget() - cameraPosition;
        direction.normalize();

        core::vector3df movement;

        const SEvent::SJoystickEvent & joystickData = getGame()->getInput()->getJoystickState();
        f32 moveHorizontal = 0.f; // Range is -1.f for full left to +1.f for full right
        f32 moveVertical = 0.f; // -1.f for full down to +1.f for full up.

        // We receive the full analog range of the axes, and so have to implement our
        // own dead zone.  This is an empirical value, since some joysticks have more
        // jitter or creep around the center point than others.  We'll use 5% of the
        // range as the dead zone, but generally you would want to give the user the
        // option to change this.
        const f32 DEAD_ZONE = 0.05f;

        moveHorizontal =
            (f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
        if(fabs(moveHorizontal) < DEAD_ZONE)
            moveHorizontal = 0.f;

        moveVertical =
            (f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
        if(fabs(moveVertical) < DEAD_ZONE)
            moveVertical = 0.f;

        u32 time = getGame()->getDevice()->getTimer()->getTime();

        if (getGame()->getInput()->isKeyPressed(KEY_SPACE) || 
            joystickData.IsButtonPressed(0)) {
            if (time - m_lastAsteroid > 100)
            {
                addRocket();
                m_lastAsteroid = time;
            }
        }

        if(!core::equals(moveHorizontal, 0.f) || !core::equals(moveVertical, 0.f))
        {
            movement.X += movementAmount/40.f * delta * moveHorizontal;
            movement.Y += movementAmount/60.f * delta * moveVertical;
        }

        if (getGame()->getInput()->isKeyPressed(KEY_KEY_L)) {
            direction = vector3df(1,0,0);
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_J)) {
            direction = vector3df(-1,0,0);
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_I)) {
            direction = vector3df(0,1,0);
        }
        if (getGame()->getInput()->isKeyPressed(KEY_KEY_K)) {
            direction = vector3df(0,-1,0);
        }

        movement += direction * movementAmount;
        cameraPosition += movement;
        m_player->setPosition(cameraPosition);
    }

}