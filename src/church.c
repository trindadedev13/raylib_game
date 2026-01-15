// Simples Objeto 3D de um Igreja

#include "church.h"

#include <raylib.h>

void
LoadChurch (Church *church) {
  church->model = LoadModel ("resources/models/church.obj");
  church->tex = LoadTexture ("resources/textures/church_diffuse.png");
  church->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = church->tex;
  church->model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = church->tex;
}

void
DrawChurch (Church *church) {
  DrawModel (church->model, church->pos, 0.5f, WHITE);
}

void
UnloadChurch (Church *church) {
  UnloadTexture (church->tex);
  UnloadModel (church->model);
}
