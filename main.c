#include <raylib.h>
#include <rlgl.h>
#include <stdio.h>

void
IDrawGrid (int slices, float spacing, Color color)
{
  int halfSlices = slices / 2;

  rlBegin (RL_LINES);
  for (int i = -halfSlices; i <= halfSlices; i++)
  {
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);

    rlVertex3f ((float)i * spacing, 0.0f, (float)-halfSlices * spacing);
    rlVertex3f ((float)i * spacing, 0.0f, (float)halfSlices * spacing);

    rlVertex3f ((float)-halfSlices * spacing, 0.0f, (float)i * spacing);
    rlVertex3f ((float)halfSlices * spacing, 0.0f, (float)i * spacing);
  }
  rlEnd ();
}

void DrawSun(int *dir, Vector3 *pos){

  float SPEED = 0.05f;
  float MIN = 0.0f;
  float MAX = 10.0f;

  switch(*dir){
    case 0:
      if(pos->x > MAX){
        *dir = 1;
        break;
      }
      pos->x += SPEED;
    break;
    case 1:
      if(pos->y > MAX){
        *dir = 2;
        break;
      }
      pos->y += SPEED;
    break;
    case 2:
      if(pos->x < MIN){
        *dir = 3;
        break;
      }
      pos->x -= SPEED;
    break;
    case 3:
      if(pos->y < MIN){
        *dir = 0;
        break;
      }
      pos->y -= SPEED;
    break;
  }
}

int
main (void)
{
  const int win_width = 800;
  const int win_height = 800;
  Camera3D camera = { 0 };
  Vector3 cube_pos = { 0.f, 1.f, 0.f };

  camera.position = (Vector3){ 0.f, 10.f, 10.f };
  camera.target = (Vector3){ 0.f, 0.f, 0.f };
  camera.up = (Vector3){ 0.f, 1.f, 0.f };
  camera.fovy = 45.f;
  camera.projection = CAMERA_PERSPECTIVE;

  InitWindow (win_width, win_height, "teste");
  DisableCursor ();
  SetTargetFPS (60);

  Vector3 terrain_pos = { 0.f, 0.f, 0.f };
  Vector2 terrain_size = { 10.f, 10.0f };

  int direction = 0;
  Vector3 sun_pos = {0,10.0f,10.0f};

  while (!WindowShouldClose ())
  {
    UpdateCamera (&camera, CAMERA_FREE);
    BeginDrawing ();

    ClearBackground ((Color){0,0,20});

    BeginMode3D (camera);
    DrawCube (cube_pos, 2.f, 2.f, 2.f, BLUE);
    DrawCubeWires (cube_pos, 2.f, 2.f, 2.f, MAROON);

    DrawCircle3D((Vector3){0.0f,10.0f,0.0f}, 1.0f, (Vector3){0.0f,0.0f,0.0f},0.0f, YELLOW);
    DrawSun(&direction, &sun_pos);
    DrawSphere(sun_pos, 1.0f, YELLOW);
    DrawPlane (terrain_pos, terrain_size, GREEN);

    IDrawGrid (10, 1.f, BLACK);
    EndMode3D ();

    EndDrawing ();
  }

  CloseWindow ();
  return 0;
}
