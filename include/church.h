#ifndef __church_h__
#define __church_h__

#include <raylib.h>

typedef struct {
  Model model;
  Texture2D tex;
  Vector3 pos;
} Church;

void LoadChurch (Church *);
void DrawChurch (Church *);
void UnloadChurch (Church *);

#endif