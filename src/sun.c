#include "sun.h"

void
LoadSunTexture (Sun *sun) {
  // carrega a imagem
  sun->tex = LoadTexture ("resources/textures/sun.png");
  // cria uma malha de esfera
  Mesh mesh = GenMeshSphere (1.f, 16, 16);
  // cria um modelo desenhavel da nossa malha
  sun->model = LoadModelFromMesh (mesh);
  // aplica a textura2d no material do modelo
  sun->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = sun->tex;
  sun->model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = sun->tex;
}

void
DrawSun (Sun *sun) {
  switch (sun->dir) {
  case 0:
    if (sun->pos.x > sun->max) {
      sun->dir = 1;
      break;
    }
    sun->pos.x += sun->speed;
    break;
  case 1:
    if (sun->pos.y > sun->max) {
      sun->dir = 2;
      break;
    }
    sun->pos.y += sun->speed;
    break;
  case 2:
    if (sun->pos.x < sun->min) {
      sun->dir = 3;
      break;
    }
    sun->pos.x -= sun->speed;
    break;
  case 3:
    if (sun->pos.y < sun->min) {
      sun->dir = 0;
      break;
    }
    sun->pos.y -= sun->speed;
    break;
  }
  DrawModel (sun->model, sun->pos, sun->scale, WHITE);
}

void
UnloadSun (Sun *sun) {
  UnloadModel (sun->model);
  UnloadTexture (sun->tex);
}
