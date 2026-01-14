#include <raylib.h>
#include <stdio.h>

int
main (void)
{
  const int win_width = 800;
  const int win_height= 800;
  Camera3D camera = {0};
  Vector3 cube_pos = { 0.f, 0.f, 0.f };

  camera.position = (Vector3){ 0.f, 10.f, 10.f };
  camera.target = (Vector3){ 0.f, 0.f, 0.f };
  camera.up = (Vector3){ 0.f, 1.f, 0.f };
  camera.fovy = 45.f;
  camera.projection = CAMERA_PERSPECTIVE;

  InitWindow (win_width, win_height, "teste");
  DisableCursor ();
  SetTargetFPS (60);

  Vector3 terrain_pos = {
    0.f, 0.f, 0.f
  };
  Vector2 terrain_size = {
    10.f, 1.0f
  };

  while (!WindowShouldClose ())
  {
    UpdateCamera (&camera, CAMERA_FREE);
    BeginDrawing ();

    ClearBackground (WHITE);

    BeginMode3D (camera);
      DrawCube (cube_pos, 2.f, 2.f, 2.f, BLUE);
      DrawCubeWires(cube_pos, 2.f, 2.f, 2.f, MAROON);
      DrawPlane(terrain_pos, terrain_size, GREEN);
      DrawGrid (10, 1.f);
    EndMode3D ();

    EndDrawing ();
  }

  CloseWindow ();
  return 0;
}
