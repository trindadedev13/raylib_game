#ifndef __sun_h__
#define __sun_h__

#include <raylib.h>

typedef struct {
  float speed;
  float min;
  float max;
  float scale;
  int dir;

  Vector3 pos;
  Model model;
  Texture2D tex;
} Sun;

void LoadSunTexture (Sun *);
void DrawSun (Sun *);
void UnloadSun (Sun *);

#endif