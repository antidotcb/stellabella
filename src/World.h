#pragma once

#include "list"

namespace stellabellum {
    namespace game {

        class CWorld {
        public:
            CWorld(scene::ISceneManager* scene, game::CGame* game);

            ~CWorld();

            void update( f32 delta);

            void addEntity(entities::CEntity* entity);

            void /*entities::CEntity**/ shotRocket(entities::CEntity * parent,
                core::vector3df& position,
                core::vector3df& velocity,
                core::vector3df& acceleration);

            entities::CEntity* createPlayer(const core::vector3df& playerPosition);

        private:
            void addCamera(game::CGame* game, scene::ISceneManager* scene);

            void setupConstrains(entities::CEntity* entity);

            const f32 getMaxX(const entities::CEntity* entity) const;
            const f32 getMinX(const entities::CEntity* entity) const;
            const f32 getMaxY(const entities::CEntity* entity) const;
            const f32 getMinY(const entities::CEntity* entity) const;

            scene::ISceneManager* Scene;
            scene::ICameraSceneNode* Camera;
            entities::CPlayer* Player;
            game::CGame* Game;

            typedef std::list<entities::CEntity *> EntityList;
            
            EntityList Entities;
            EntityList NewEntities;
        };

    }
}