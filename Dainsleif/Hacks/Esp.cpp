#include "Esp.h"
#include <optional>

std::optional<Vector2> WorldToScreen(Vector3 entPos, WindowSize& windowSize) {
    float viewMatrix[4][4];
    memcpy(&viewMatrix, (PBYTE*)(Modules::client + dwViewMatrix), sizeof(viewMatrix));
    Vector4 clipCoords{};
    clipCoords.x = entPos.x * viewMatrix[0][0] + entPos.y * viewMatrix[0][1] + entPos.z * viewMatrix[0][2] + viewMatrix[0][3];
    clipCoords.y = entPos.x * viewMatrix[1][0] + entPos.y * viewMatrix[1][1] + entPos.z * viewMatrix[1][2] + viewMatrix[1][3];
    clipCoords.z = entPos.x * viewMatrix[2][0] + entPos.y * viewMatrix[2][1] + entPos.z * viewMatrix[2][2] + viewMatrix[2][3];
    clipCoords.w = entPos.x * viewMatrix[3][0] + entPos.y * viewMatrix[3][1] + entPos.z * viewMatrix[3][2] + viewMatrix[3][3];

    if (clipCoords.w < 0.1f)
        return {};

    Vector3 NDC{};
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;
    std::optional<Vector2> screen = Vector2{};
    screen->x = (windowSize.w / 2 * NDC.x) + (NDC.x + windowSize.w / 2);
    screen->y = -(windowSize.h / 2 * NDC.y) + (NDC.y + windowSize.h / 2);
    return screen;
}

void Esp::DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color) {
    ID3DXLine* LineL;
    D3DXCreateLine(&this->pDevice, &LineL);

    D3DXVECTOR2 Line[2];
    Line[0] = D3DXVECTOR2(x1, y1);
    Line[1] = D3DXVECTOR2(x2, y2);
    LineL->SetWidth(thickness);
    LineL->Draw(Line, 2, color);
    LineL->Release();
}

void Esp::DrawOutLineRect(Vector2 top, Vector2 bottom, int thickness, D3DCOLOR color) {
    ID3DXLine* LineL;
    D3DXCreateLine(&this->pDevice, &LineL);

    float height = fabs(top.y - bottom.y);

    // apparently, height / 2 is the horizontal length of the rectangle.
    // top.x and bottom.x is located at the center of the entity
    // so x coordinate -(+) height / 4 should be the left and right end of the rectangle.
    D3DXVECTOR2 topLine[2] = {D3DXVECTOR2(top.x - height / 4, top.y), D3DXVECTOR2(top.x + height / 4, top.y)};
    D3DXVECTOR2 bottomLine[2] = {D3DXVECTOR2(bottom.x - height / 4, bottom.y), D3DXVECTOR2(bottom.x + height / 4, bottom.y)};
    D3DXVECTOR2 rightLine[2] = {D3DXVECTOR2(top.x + height / 4, top.y), D3DXVECTOR2(bottom.x + height / 4, bottom.y)};
    D3DXVECTOR2 leftLine[2] = {D3DXVECTOR2(top.x - height / 4, top.y), D3DXVECTOR2(bottom.x - height / 4, bottom.y)};

    LineL->SetWidth(thickness);
    LineL->Draw(topLine, 2, color);
    LineL->Draw(bottomLine, 2, color);
    LineL->Draw(rightLine, 2, color);
    LineL->Draw(leftLine, 2, color);
    LineL->Release();
}

void Esp::DrawFilledRect(Vector2 top, Vector2 bottom, D3DCOLOR color) {
    float height = fabs(top.y - bottom.y);

    LONG width = (static_cast<LONG>(bottom.x + height / 4)) - (static_cast<LONG>(top.x + height / 4));

    D3DRECT rect = {static_cast<LONG>(top.x + height / 4), static_cast<LONG>(top.y), static_cast<LONG>(bottom.x + height / 4), static_cast<LONG>(bottom.y)};
    this->pDevice.Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void Esp::LineOverlay() {
    for (auto& player : this->playerList) {
        if (player->GetHealth() && !player->IsDormant()) {
            std::optional<Vector2> entFootPos2D = WorldToScreen(player->GetBodyPosition(), this->windowSize);
            if (entFootPos2D) {
                D3DCOLOR color;
                if (player->GetTeam() == this->localTeamNum)
                    color = D3DCOLOR_ARGB(255, 0, 255, 0);
                else
                    color = D3DCOLOR_ARGB(255, 255, 0, 0);
                DrawLine(entFootPos2D->x, entFootPos2D->y, windowSize.w / 2, windowSize.h, 2, color);
            }
        }
    }
}

void Esp::RectangleOverlay() {
    for (auto& player : this->playerList) {
        if (player->GetHealth() && !player->IsDormant()) {
            std::optional<Vector2> entHeadPos2D = WorldToScreen(player->GetBonePosition(), this->windowSize);
            std::optional<Vector2> entFootPos2D = WorldToScreen(player->GetBodyPosition(), this->windowSize);
            if (entHeadPos2D && entFootPos2D) {
                D3DCOLOR color;
                if (player->GetTeam() == this->localTeamNum)
                    color = D3DCOLOR_ARGB(255, 0, 255, 0);
                else
                    color = D3DCOLOR_ARGB(255, 255, 0, 0);
                DrawOutLineRect(*entHeadPos2D, *entFootPos2D, 1, color);
            }
        }
    }
}

void Esp::HealthOverlay() {
    for (auto& player : this->playerList) {
        if (player->GetHealth() && !player->IsDormant()) {
            std::optional<Vector2> entHeadPos2D = WorldToScreen(player->GetBonePosition(), this->windowSize);
            std::optional<Vector2> entFootPos2D = WorldToScreen(player->GetBodyPosition(), this->windowSize);
            if (entHeadPos2D && entFootPos2D) {
                this->DrawFilledRect(*entHeadPos2D, *entFootPos2D, D3DCOLOR_ARGB(255, 255, 51, 51));
            }
        }
    }
}