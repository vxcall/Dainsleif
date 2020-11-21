#include "MinimapHack.h"

void Minimap::Run(std::vector<Player*> playerList) {
    for (auto& player : playerList) {
        player->WriteValue<bool>(m_bSpotted, true);
    }
}

void Minimap::Stop(std::vector<Player*> playerList) {
    for (auto& player : playerList){
        player->WriteValue<bool>(m_bSpotted, false);
    }
}