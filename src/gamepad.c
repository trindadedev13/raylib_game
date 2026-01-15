#ifdef __ANDROID__
#include "gamepad.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <string.h>

void
CreatePad (Pad *pad) {
  Vector2 pad_pos = { 200, GetScreenHeight () - BUTTON_RADIUS * 3 };

  Vector2 buttons_pos[BUTTON_MAX] = {
    { pad_pos.x, pad_pos.y - BUTTON_RADIUS * 1.5f }, // Up
    { pad_pos.x - BUTTON_RADIUS * 1.5f, pad_pos.y }, // Left
    { pad_pos.x + BUTTON_RADIUS * 1.5f, pad_pos.y }, // Right
    { pad_pos.x, pad_pos.y + BUTTON_RADIUS * 1.5f }  // Down
  };

  char *buttons_label[BUTTON_MAX] = {
    "Y ", // Up
    "X",  // Left
    "B",  // Right
    "A"   // Down
  };

  Color buttons_label_colors[BUTTON_MAX] = { YELLOW, BLUE, RED, GREEN };

  pad->pressed = BUTTON_NONE;
  memcpy (pad->buttons_pos, buttons_pos, sizeof (buttons_pos));
  memcpy (pad->buttons_label_colors, buttons_label_colors,
          sizeof (buttons_label_colors));
  for (int i = 0; i < BUTTON_MAX; i++)
    pad->buttons_label[i] = buttons_label[i];
}

void
DrawPad (Pad *pad, Camera3D *cam) {
  Vector2 input_pos = { 0, 0 };

  if ((GetTouchPointCount () > 0))
    input_pos = GetTouchPosition (0);
  else
    input_pos = GetMousePosition ();

  pad->pressed = BUTTON_NONE;
  if ((GetTouchPointCount () > 0)
      || ((GetTouchPointCount () == 0)
          && IsMouseButtonDown (MOUSE_BUTTON_LEFT))) {
    for (int i = 0; i < BUTTON_MAX; i++) {
      float distX = fabsf (pad->buttons_pos[i].x - input_pos.x);
      float distY = fabsf (pad->buttons_pos[i].y - input_pos.y);
      if ((distX + distY < BUTTON_RADIUS)) {
        pad->pressed = i;
        break;
      }
    }
  }

  // verificar qual botao for clicado
  // dai fazer o m movimento
  float cam_accel = 5.f * GetFrameTime ();
  // se deixar true, ele nao vai poder "voar" pelo mundo, apenas andar, igual FPS
  bool move_in_world_plane = true;
#define is(i) pad->pressed == i
  if (is (BUTTON_UP)) {
    CameraMoveForward (cam, cam_accel, move_in_world_plane);
  } else if (is (BUTTON_LEFT)) {
    CameraMoveRight (cam, -cam_accel, move_in_world_plane);
  } else if (is (BUTTON_DOWN)) {
    CameraMoveForward (cam, -cam_accel, move_in_world_plane);
  } else if (is (BUTTON_RIGHT)) {
    CameraMoveRight (cam, cam_accel, move_in_world_plane);
  }
#undef is
  for (int i = 0; i < BUTTON_MAX; i++) {
    DrawCircleV (pad->buttons_pos[i], BUTTON_RADIUS,
                 (i == pad->pressed) ? DARKGRAY : BLACK);
    DrawText (pad->buttons_label[i], (int)pad->buttons_pos[i].x - 7,
              (int)pad->buttons_pos[i].y - 8, 20,
              pad->buttons_label_colors[i]);
  }
}

#endif
