#include <raylib.h>
#include <stdio.h>

int
main ()
{
  Camera3D camera;
  Vector3 cube_pos;

  camera.position = (Vector3) {0.f, 10.f, 10.f};
  camera.target = (Vector3) {0.f, 0.f, 0.f};
  camera.up = (Vector3) {0.f, 1.f, 0.f};
  camera.fovy = 45.f;
  camera.projection = CAMERA_PERSPECTIVE;

  
  InitWindow (720, 360, "teste");
  SetTargetFPS (60);
  while (!WindowShouldClose ())
  {
    BeginDrawing ();

    ClearBackground (WHITE);

    BeginMode3D(camera);
      DrawGrid (10, 1.f);
    EndMode3D();

    EndDrawing ();
  }

  CloseWindow ();
  return 0;
}
