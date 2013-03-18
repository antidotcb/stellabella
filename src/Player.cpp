#include "stellabellum.h"
#include "Player.h"
#include "Game.h"
#include "Input.h"
#include "World.h"

namespace stellabellum {
    namespace entities {

        CPlayer::CPlayer(
            game::CWorld* world, scene::ISceneManager* scene, 
            const core::vector3df& position)

            : CEntity(world, scene, position),
            LastRocketShotTime(0)
        {
            Type = CEntity::PlayerEntity;
            setName("Player");
            
            setRotation(core::vector3df(-30,0,0));
            Rotation = getRotation();

            LeftWing = scene->addEmptySceneNode(this);
            LeftWing->grab();

            RightWing = scene->addEmptySceneNode(this);
            RightWing->grab();
        }

        bool CPlayer::update(const game::CGame * g, float delta) {            
            move(g, delta);

            u32 currentTime = g->getDevice()->getTimer()->getTime();

            if (g->getControls().isFirePressed()) {
                if (currentTime - LastRocketShotTime > 1000)
                {
                    makeShot();
                    LastRocketShotTime = currentTime;
                }
            }

            return true;
        }

        void CPlayer::move(const game::CGame * g, const f32 delta) {
            const f32 maxVelocity = getPlayerVelocity();

            core::vector3df position = getPosition();
            core::vector2df movement2d(0.f, 0.f);

            g->getControls().getMovement(movement2d);

            core::vector3df movement(movement2d.X, movement2d.Y, 0.f);

            Acceleration = movement * maxVelocity;
            Velocity += Acceleration * delta;

            if (Velocity.getLengthSQ() > maxVelocity*maxVelocity) {
                Velocity = Velocity.normalize() * maxVelocity;
            } else {
                Velocity -= Velocity * 0.5f * delta;
            }

            position += Velocity * delta;

            core::vector3df rotation = Rotation;
            f32 rotY = -(Velocity.X / maxVelocity) * 15;//core::PI;
            f32 rotZ = 0;
            rotation += core::vector3df(0,rotY,rotZ);
            setRotation(rotation);

            fitIntoConstrains(position);

            setPosition(position);
        }

        void CPlayer::fitIntoConstrains(core::vector3df& position) {
            if (position.X > Constrains.MaxEdge.X) {
                position.X = Constrains.MaxEdge.X;
                Acceleration.X = 0;
            }

            if (position.X < Constrains.MinEdge.X) {
                position.X = Constrains.MinEdge.X;
                Acceleration.X = 0;
            }

            if (position.Y > Constrains.MaxEdge.Y) {
                position.Y = Constrains.MaxEdge.Y;                
                Acceleration.Y = 0;
            }

            if (position.Y < Constrains.MinEdge.Y) {
                position.Y = Constrains.MinEdge.Y;                
                Acceleration.Y = 0;
            }

            if (position.Z > Constrains.MaxEdge.Z) {
                position.Z = Constrains.MaxEdge.Z;                
                Acceleration.Z = 0;
            }

            if (position.Z < Constrains.MinEdge.Z) {
                position.Z = Constrains.MinEdge.Z;                
                Acceleration.Z = 0;
            }
        }

        void CPlayer::makeShot() {
            core::vector3df rocketVelocity;
            rocketVelocity.Y = getRocketVelocity();
            
            core::vector3df rocketAcceleration;
            rocketAcceleration.Y = getRocketAcceleration();

            core::vector3df rocketPosition = getPosition();
            WingLastShot = !WingLastShot;

            core::aabbox3df box = getBoundingBox();
            f32 width = box.MaxEdge.X - box.MinEdge.X;
            if(WingLastShot) {
                rocketPosition = LeftWing->getAbsolutePosition();
            } else {
                rocketPosition = RightWing->getAbsolutePosition();
            }

            World->shotRocket(this, rocketPosition, rocketVelocity, rocketAcceleration);
        }

        f32 CPlayer::getRocketVelocity() {
            return -50.f;
        }

        f32 CPlayer::getPlayerVelocity() {
            return 250.f;
        }

        f32 CPlayer::getRocketAcceleration() {
            return 300.f;
        }

        CPlayer::~CPlayer() {
            LeftWing->drop();
            RightWing->drop();
        }

        void CPlayer::updateSizes() {
            CEntity::updateSizes();

            core::vector3df position;
            position.Y -= 15;
            position.Z -= 10;

            position.X = (Width/3.5f);
            LeftWing->setPosition(position);
            LeftWing->updateAbsolutePosition();

            position.X = -(Width/3.5f);
            RightWing->setPosition(position);
            RightWing->updateAbsolutePosition();
        }

    }
}