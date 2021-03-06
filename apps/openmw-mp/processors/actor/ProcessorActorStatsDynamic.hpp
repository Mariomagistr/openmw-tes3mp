#ifndef OPENMW_PROCESSORACTORSTATSDYNAMIC_HPP
#define OPENMW_PROCESSORACTORSTATSDYNAMIC_HPP

#include "../ActorProcessor.hpp"

namespace mwmp
{
    class ProcessorActorStatsDynamic final: public ActorProcessor
    {
    public:
        ProcessorActorStatsDynamic()
        {
            BPP_INIT(ID_ACTOR_STATS_DYNAMIC)
        }

        void Do(ActorPacket &packet, const std::shared_ptr<Player> &player, BaseActorList &actorList) override
        {
            // Send only to players who have the cell loaded
            Cell *serverCell = CellController::get().getCell(actorList.cell);

            if (serverCell != nullptr && *serverCell->getAuthority() == actorList.guid)
            {
                serverCell->readActorList(packetID, &actorList);
                serverCell->sendToLoaded(&packet, &actorList);
            }
        }
    };
}

#endif //OPENMW_PROCESSORACTORSTATSDYNAMIC_HPP
