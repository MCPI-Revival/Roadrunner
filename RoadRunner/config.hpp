#pragma once

// World
constexpr int SEED = 0;
constexpr float SPAWN_X = 180.f;
constexpr float SPAWN_Y = 72.f;
constexpr float SPAWN_Z = 180.f;
// Game mode
constexpr bool IS_CREATIVE = false;
// The largest number of blocks the player can move at once before being pulled back
// High numbers are better for slow connection
constexpr float MAX_DIST = 5.0;
// If the player is blocked from going past the world border
#define WORLD_BORDER true
