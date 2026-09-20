#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "box2d/box2d.h"
#include "chad.h"

b2WorldId CreateMortalWorld(void);
void DrawWorld(b2WorldId world);

#endif
