#ifdef __ANDROID__
#ifndef __gamepad_h__
#define __gamepad_h__

#include <raylib.h>

#define BUTTON_RADIUS 100

typedef enum {
  BUTTON_NONE = -1,
  BUTTON_UP,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_DOWN,
  BUTTON_MAX
} PadButton;

typedef struct {
  Vector2 buttons_pos[BUTTON_MAX];
  const char *buttons_label[BUTTON_MAX];
  Color buttons_label_colors[BUTTON_MAX];
  PadButton pressed;
} Pad;

void CreatePad (Pad *);

void DrawPad (Pad *, Camera3D *);

#endif
#endif
