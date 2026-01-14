#include <raylib.h>
#include <rlgl.h>

#include "rlext.h"

typedef struct {
  float speed;
  float min;
  float max;

  Vector3 pos;

  int dir;

  Model model;

} Sun;

void
LoadSunTexture (Sun *sun) {
  // carrega a imagem
  Texture2D tex2D = LoadTexture ("resources/sun.png");
  // cria uma malha de esfera
  Mesh mesh = GenMeshSphere (1.f, 16, 16);
  // cria um modelo desenhavel da nossa malha
  sun->model = LoadModelFromMesh (mesh);
  // aplica a textura2d no material do modelo
  sun->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex2D;
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
    if (sun->pos.x > sun->max) {
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
    if (sun->pos.x < sun->min) {
      sun->dir = 0;
      break;
    }
    sun->pos.y -= sun->speed;
    break;
  }
  DrawModel (sun->model, sun->pos, 1.f, WHITE);
}

int
main (void) {
  Camera3D camera = { .position = (Vector3){ 0.f, 10.f, 10.f },
                      .target = (Vector3){ 0.f, 0.f, 0.f },
                      .up = (Vector3){ 0.f, 1.f, 0.f },
                      .fovy = 50.f,
                      .projection = CAMERA_PERSPECTIVE };

  // aqui vou definir o tamanho da janela de acordo com o OS
  // se for ANDROID vai ser fullscreen, caso contrario 800x800
  int win_width = 800, win_height = 800;
#ifdef __ANDROID__
  win_width = GetScreenWidth ();
  win_height = GetScreenHeight ();
#endif

  InitWindow (win_width, win_height, "teste");

  DisableCursor ();
  SetTargetFPS (60);

  Vector3 terrain_pos = { 0.f, 0.f, 0.f };
  Vector2 terrain_size = { 10.f, 10.0f };
  Vector3 cube_pos = { 0.f, 1.f, 0.f };

  // criar o sol
  Sun sun = { .speed = 0.05f,
              .min = 0.f,
              .max = 10.f,
              .pos = (Vector3){ 0.f, 10.f, 10.f } };
  LoadSunTexture (&sun);

  while (!WindowShouldClose ()) {
    UpdateCamera (&camera, CAMERA_FREE);
    BeginDrawing ();

    ClearBackground ((Color){ 0, 0, 20, 255 });

    BeginMode3D (camera);
    DrawCube (cube_pos, 2.f, 2.f, 2.f, BLUE);
    DrawCubeWires (cube_pos, 2.f, 2.f, 2.f, MAROON);

    DrawCircle3D ((Vector3){ 0.0f, 10.0f, 0.0f }, 1.0f,
                  (Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, YELLOW);

    DrawSun (&sun);

    DrawPlane (terrain_pos, terrain_size, GREEN);

    RxtDrawGrid (10, 1.f, BLACK);
    EndMode3D ();

    EndDrawing ();
  }

  CloseWindow ();
  return 0;
}
