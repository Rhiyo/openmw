
#include "probe.hpp"

#include <components/esm/loadlocks.hpp>

#include <components/esm_store/cell_store.hpp>

#include "../mwbase/environment.hpp"

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontake.hpp"
#include "../mwworld/inventorystore.hpp"

#include "../mwrender/objects.hpp"

#include "../mwsound/soundmanager.hpp"

namespace MWClass
{
    void Probe::insertObjectRendering (const MWWorld::Ptr& ptr, MWRender::RenderingInterface& renderingInterface) const
    {
        ESMS::LiveCellRef<ESM::Probe, MWWorld::RefData> *ref =
            ptr.get<ESM::Probe>();

        assert (ref->base != NULL);
        const std::string &model = ref->base->model;

        if (!model.empty())
        {
            MWRender::Objects& objects = renderingInterface.getObjects();
            objects.insertBegin(ptr, ptr.getRefData().isEnabled(), false);
            objects.insertMesh(ptr, "meshes\\" + model);
        }
    }

    void Probe::insertObject(const MWWorld::Ptr& ptr, MWWorld::PhysicsSystem& physics) const
    {
        ESMS::LiveCellRef<ESM::Probe, MWWorld::RefData> *ref =
            ptr.get<ESM::Probe>();


        const std::string &model = ref->base->model;
        assert (ref->base != NULL);
        if(!model.empty()){
            physics.insertObjectPhysics(ptr, "meshes\\" + model);
        }

    }


    std::string Probe::getName (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Probe, MWWorld::RefData> *ref =
            ptr.get<ESM::Probe>();

        return ref->base->name;
    }
    boost::shared_ptr<MWWorld::Action> Probe::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor) const
    {
        MWBase::Environment::get().getSoundManager()->playSound3D (ptr, getUpSoundId(ptr), 1.0, 1.0, MWSound::Play_NoTrack);

        return boost::shared_ptr<MWWorld::Action> (
            new MWWorld::ActionTake (ptr));
    }

    std::string Probe::getScript (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Probe, MWWorld::RefData> *ref =
            ptr.get<ESM::Probe>();

        return ref->base->script;
    }

    std::pair<std::vector<int>, bool> Probe::getEquipmentSlots (const MWWorld::Ptr& ptr) const
    {
        std::vector<int> slots;

        slots.push_back (int (MWWorld::InventoryStore::Slot_CarriedRight));

        return std::make_pair (slots, false);
    }

    int Probe::getValue (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Probe, MWWorld::RefData> *ref =
            ptr.get<ESM::Probe>();

        return ref->base->data.value;
    }

    void Probe::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Probe);

        registerClass (typeid (ESM::Probe).name(), instance);
    }

    std::string Probe::getUpSoundId (const MWWorld::Ptr& ptr) const
    {
        return std::string("Item Probe Up");
    }

    std::string Probe::getDownSoundId (const MWWorld::Ptr& ptr) const
    {
        return std::string("Item Probe Down");
    }
}
