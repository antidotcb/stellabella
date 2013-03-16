#include "stellabellum.h"
#include "World.h"
#include "Player.h"
#include "Game.h"

namespace stellabellum {
    namespace game {

        World::~World() {
            m_camera->drop();
            m_player->drop();
        }

        void stellabellum::game::World::init(game::Game* g, scene::ISceneManager* mgr) {
            m_player = new entities::Player(this, mgr->getRootSceneNode(), mgr, -1, core::vector3df(0,-200,0));

            scene::IAnimatedMesh* playerMesh = mgr->getMesh("d:\\xpn_2013\\export\\fighter.X");
            scene::IAnimatedMeshSceneNode* playerNode = mgr->addAnimatedMeshSceneNode(playerMesh, m_player, -1);

            playerNode->setPosition(core::vector3df(0,0,0));
            playerNode->setMaterialTexture(0, g->getPlayerTexture(""));
            playerNode->setMaterialFlag(video::EMF_LIGHTING, false);
        }

        stellabellum::game::World::World(scene::ICameraSceneNode* camera):
        m_camera(camera)
        {
            m_camera->grab();
            m_camera->setPosition(core::vector3df(0,0,-300));
            //m_camera->setFOV(irr::core::PI);
        }

        void stellabellum::game::World::update(game::Game* g, f32 delta) {
            m_player->update(g, delta);
        }

    }
}