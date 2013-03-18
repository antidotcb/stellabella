#include "stellabellum.h"
#include "Entity.h"

namespace stellabellum {
    namespace entities {

        CEntity::CEntity(game::CWorld* world, scene::ISceneManager* scene,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)

            :ISceneNode(scene->getRootSceneNode(), scene, -1, position, rotation, scale),
            Acceleration(0,0,0), Velocity(0,0,0), AngularVelocity(0,0,0),
            Type(GenericEntity),
            World(world),
            Node(0), Width(0), Height(0)
        {
            setAutomaticCulling(scene::EAC_OFF);
        }

        CEntity::EntityType CEntity::getType() {
            return Type;
        }

        bool CEntity::isFixedPosition() {
            return false;
        }

        void CEntity::render() {}

        void CEntity::OnRegisterSceneNode() {
            if (IsVisible)
                SceneManager->registerNodeForRendering(this);

            ISceneNode::OnRegisterSceneNode();
        }

        const core::aabbox3d<f32>& CEntity::getBoundingBox() const {
            return Box;
        }

        void CEntity::setTexture(video::ITexture* texture) {
            if (!texture) {
                throw std::exception("Empty texture param.");
            }

            if (Node) {
                Node->setMaterialTexture(0, texture);
                Node->setMaterialFlag(video::EMF_LIGHTING, false);
            } else {
                throw std::exception("No child node attached for texture.");
            }
        }

        void CEntity::setMesh(scene::IAnimatedMesh* mesh) {
            if (Node) {
                Node->drop();
                Node->remove();
                Node = 0;
            }

            Box.reset(core::vector3df());

            if (mesh) {
                Node = getSceneManager()->addAnimatedMeshSceneNode(mesh, this);
                Node->grab();
                
                Box.addInternalBox(mesh->getBoundingBox());
                updateSizes();
            }
        }

        CEntity::~CEntity() {
            setMesh(0);
        }

        void CEntity::setConstrains(const core::aabbox3df& box) {
            Constrains = box;
        }

        void CEntity::setVelocity(const core::vector3df& velocity) {
            Velocity = velocity;
        }

        void CEntity::setAcceleration(const core::vector3df& acceleration) {
            Acceleration = acceleration;
        }

        void CEntity::setAngularVelocity(const core::vector3df& angularVelocity) {
            AngularVelocity = angularVelocity;
        }

        void CEntity::updateSizes()
        {
            Width = Box.MaxEdge.X - Box.MinEdge.X;
            Height = Box.MaxEdge.Y - Box.MinEdge.Y;
        }

    }
}