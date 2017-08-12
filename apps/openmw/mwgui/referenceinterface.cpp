#include "referenceinterface.hpp"

#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"

#include "../mwmechanics/actorutil.hpp"

namespace MWGui
{
    ReferenceInterface::ReferenceInterface()
        : mCurrentPlayerCell(NULL)
    {
    }

    ReferenceInterface::~ReferenceInterface()
    {
    }

    void ReferenceInterface::checkReferenceAvailable()
    {
        MWWorld::CellStore* playerCell = MWMechanics::getPlayer().getCell();

        // check if count of the reference has become 0
        if (!mPtr.isEmpty() && mPtr.getRefData().getCount() == 0)
        {
            if (!mPtr.isEmpty())
            {
                mPtr = MWWorld::Ptr();
                onReferenceUnavailable();
            }
        }

        mCurrentPlayerCell = playerCell;
    }
}
