#include <raylib.h>

#include "sun.h"
#include "church.h"
#include "rlext.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

typedef struct {
  Shader bloom_shader;
  int width, height;
  Color bg_color;
} State;

static State state = { 0 };

void
LoadBloomShader (void) {
  state.bloom_shader = LoadShader (
      0, TextFormat ("resources/shaders/glsl%i/bloom.fs", GLSL_VERSION));

  int size_loc = GetShaderLocation (state.bloom_shader, "size");
  Vector2 size = { state.width, state.height };
  SetShaderValue (state.bloom_shader, size_loc, &size, SHADER_UNIFORM_VEC2);
}

int
main (void) {
#ifndef __ANDROID__
  state.width = 800;
  state.height = 800;
#endif
  state.bg_color = (Color){ 0, 0, 20, 255 };

  SetConfigFlags (FLAG_MSAA_4X_HINT);
  InitWindow (state.width, state.height, "teste");

#ifdef __ANDROID__
  state.width = GetScreenWidth ();
  state.height = GetScreenHeight ();
  SetWindowSize (state.width, state.height);
  SetConfigFlags (FLAG_FULLSCREEN_MODE);
#endif

  Camera camera = { 0 };
  camera.position = (Vector3){ 2.0f, 3.0f, 2.0f };
  camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // carregar shader de brilho
  LoadBloomShader ();

  // criar renderizador de textura pra renderizar
  RenderTexture2D target = LoadRenderTexture (state.width, state.height);

  SetTargetFPS (60);

  // criar o sol
  Sun sun = { .dir = 0,
              .speed = 0.05f,
              .min = 0.f,
              .max = 10.f,
              .scale = 3.f,
              .pos = (Vector3){ 0.f, 10.f, 10.f } };
  LoadSunTexture (&sun);

  // criar igreja
  Church church = {.pos =(Vector3) {0.f, 0.f, 0.f}};
  LoadChurch(&church);

  while (!WindowShouldClose ()) {
    UpdateCamera (&camera, CAMERA_FREE);

    BeginTextureMode (target);
      ClearBackground (BLANK);

      BeginMode3D (camera);
        DrawSun (&sun);
      EndMode3D ();
    EndTextureMode ();
    

    BeginDrawing ();
      ClearBackground (state.bg_color);

      BeginMode3D (camera);
        DrawChurch(&church);
        RxtDrawGrid (10, 1.0f, GRAY);
        DrawPlane ((Vector3){ 0.f, 0.f, 0.f }, (Vector2){ 10.f, 10.f }, BLACK);
      EndMode3D ();
      
      BeginShaderMode (state.bloom_shader);
        // A textura de renderização precisa ser invertida no eixo Y devido ao
        // OpenGL padrão. coordenadas (canto inferior esquerdo)
        DrawTextureRec (target.texture,
                        (Rectangle){ 0, 0, (float)target.texture.width,
                                     (float)-target.texture.height },
                        (Vector2){ 0, 0 }, WHITE);
      EndShaderMode ();
      DrawFPS (700, 15);
    EndDrawing ();
    //----------------------------------------------------------------------------------
  }

  UnloadSun (&sun);
  UnloadShader (state.bloom_shader);
  UnloadRenderTexture (target);

  CloseWindow ();
  return 0;
}
