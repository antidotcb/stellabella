#include "stellabellum.h"
#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Game.h"
#include "Rocket.h"

namespace stellabellum {
    namespace game {

        CWorld::CWorld(scene::ISceneManager* scene, game::CGame* game)
            : Scene(scene), Game(game)
        {
            addCamera(game, scene);

        }

        CWorld::~CWorld() {
            Camera->drop();
            Player->drop();

            BOOST_FOREACH(entities::CEntity * entity, Entities) {
                entity->drop();
            }
            Entities.clear();

            BOOST_FOREACH(entities::CEntity * entity, NewEntities) {
                entity->drop();
            }
            NewEntities.clear();
        }

        void CWorld::addEntity(entities::CEntity* entity) {
            entity->grab();
            
            setupConstrains(entity);

            NewEntities.push_back(entity);
        }

        void CWorld::update(f32 delta)
        {
            //Player->update(Game, delta);

            EntityList & entitiesList = Entities;
            EntityList & appendList = NewEntities;
            bool checkCollisions = true;

            EntityList::iterator it;
            for(it = entitiesList.begin(); it != entitiesList.end(); ++it) {
                entities::CEntity * entity = *it;
                if(entity->update(Game, delta)) {
                    // check collisions

                } else {
                    entity->remove();

                    it = entitiesList.erase(it);
                    entity->drop();

                    entity = 0;
                }
            }

            if (appendList.size()) {
                entitiesList.insert(entitiesList.end(), appendList.begin(), appendList.end());
                appendList.clear();
            }
        }

        entities::CEntity* CWorld::createPlayer( const core::vector3df& playerPosition )
        {
            Player = new entities::CPlayer(this, Scene, playerPosition);
            
            Player->setMesh(Scene->getMesh("d:\\xpn_2013\\export\\fighter.X"));
            Player->setTexture(Game->getPlayerTexture());

            return Player;
        }

        const f32 CWorld::getMaxX(const entities::CEntity* entity) const {
            const scene::SViewFrustum * frustrum = Camera->getViewFrustum();

            const core::vector3df& pos = entity->getPosition();
            const core::aabbox3df& box = entity->getBoundingBox();

            const f32 size = (box.MaxEdge.X - box.MinEdge.X);
            
            core::vector3df begin, end;
            begin = end = (pos + box.MinEdge);

            end.X += size;

            core::line3df axis(begin, end);            
            
            core::plane3df plane = 
                frustrum->planes[scene::SViewFrustum::VF_RIGHT_PLANE];

            core::vector3df point = frustrum->getFarRightUp();
            plane.recalculateD(point);

            core::vector3df result;
            
            plane.getIntersectionWithLine(axis.end, axis.getVector(), result);

            return result.X - (size / 4.f);
        }

        const f32 CWorld::getMinX(const entities::CEntity* entity) const {
            const scene::SViewFrustum * frustrum = Camera->getViewFrustum();

            const core::vector3df& pos = entity->getPosition();
            const core::aabbox3df& box = entity->getBoundingBox();

            const f32 size = (box.MaxEdge.X - box.MinEdge.X);

            core::vector3df begin, end;
            begin = end = (pos + box.MinEdge);

            end.X += size;

            core::line3df axis(begin, end);            

            core::plane3df plane = 
                frustrum->planes[scene::SViewFrustum::VF_LEFT_PLANE];

            plane.recalculateD(frustrum->getFarLeftUp());

            core::vector3df result;

            plane.getIntersectionWithLine(axis.end, axis.getVector(), result);

            return result.X + (size / 4.f);
        }

        const f32 CWorld::getMaxY(const entities::CEntity* entity) const {
            const scene::SViewFrustum * frustrum = Camera->getViewFrustum();

            const core::vector3df& pos = entity->getPosition();
            const core::aabbox3df& box = entity->getBoundingBox();

            const f32 size = (box.MaxEdge.Y - box.MinEdge.Y);

            core::vector3df begin, end;
            begin = end = (pos + box.MinEdge);

            end.Y += size;

            core::line3df axis(begin, end);            

            core::plane3df plane = 
                frustrum->planes[scene::SViewFrustum::VF_TOP_PLANE];

            plane.recalculateD(frustrum->getFarRightUp());

            core::vector3df result;

            plane.getIntersectionWithLine(axis.end, axis.getVector(), result);

            return result.Y - (size / 4.f);
        }

        const f32 CWorld::getMinY(const entities::CEntity* entity) const {
            const scene::SViewFrustum * frustrum = Camera->getViewFrustum();

            const core::vector3df& pos = entity->getPosition();
            const core::aabbox3df& box = entity->getBoundingBox();

            const f32 size = (box.MaxEdge.Y - box.MinEdge.Y);

            core::vector3df begin, end;
            begin = end = (pos + box.MinEdge);

            end.Y += size;

            core::line3df axis(begin, end);            

            core::plane3df plane = 
                frustrum->planes[scene::SViewFrustum::VF_BOTTOM_PLANE];

            plane.recalculateD(frustrum->getFarLeftDown());

            core::vector3df result;

            plane.getIntersectionWithLine(axis.end, axis.getVector(), result);

            return result.Y + (size / 4.f);
        }

        void CWorld::setupConstrains(entities::CEntity* entity) {
            core::aabbox3df box;

            core::vector3df min, max;
            min.X = getMinX(entity);
            max.X = getMaxX(entity);

            min.Y = getMinY(entity);
            max.Y = getMaxY(entity);

            min.Z = Camera->getViewFrustum()->boundingBox.MinEdge.Z;
            max.Z = Camera->getViewFrustum()->boundingBox.MaxEdge.Z;

            box.addInternalPoint(min);
            box.addInternalPoint(max);

            entity->setConstrains(box);
        }

        void/*entities::CEntity**/ CWorld::shotRocket(entities::CEntity * entity,
            core::vector3df& position,
            core::vector3df& velocity,
            core::vector3df& acceleration)
        {
            entities::CRocket * rocket = new entities::CRocket(this, Scene, entity->getPosition());
            
            rocket->setMesh(Game->getRocketMesh());
            rocket->setTexture(Game->getRocketTexture());

            rocket->setPosition(position);
            rocket->setVelocity(velocity);
            rocket->setAcceleration(acceleration);
            rocket->setAngularVelocity(core::vector3df(0,360,0));

            addEntity(rocket);
            rocket->drop();

            //return rocket;
        }

        void CWorld::addCamera(game::CGame* game, scene::ISceneManager* scene) {
            f32 width = game->getWidth(), height = Game->getHeight();

            Camera = scene->addCameraSceneNode();

            Camera->grab();
            Camera->setPosition(core::vector3df(0,0,-300));
            Camera->setTarget(core::vector3df(0,0,300));
            Camera->setUpVector(core::vector3df(0,1,0));            
            Camera->setAspectRatio((width/height));
            Camera->setFOV();
            Camera->updateAbsolutePosition();
            Camera->render();

            Scene->setActiveCamera(Camera);
        }

    }
}