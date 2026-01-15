#include "rlext.h"

#include <raylib.h>
#include <rlgl.h>

void
RxtDrawGrid (int slices, float space, Color color) {
  const int half_slices = slices / 2;
  rlBegin (RL_LINES);
  for (int i = -half_slices; i <= half_slices; i++) {
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);
    rlColor3f (color.r, color.g, color.b);

    rlVertex3f ((float)i * space, 0.f, (float)-half_slices * space);
    rlVertex3f ((float)i * space, 0.f, (float)half_slices* space);

    rlVertex3f ((float)-half_slices * space, 0.f, (float)i * space);
    rlVertex3f ((float)half_slices * space, 0.f, (float)i * space);
  }
  rlEnd ();
}

Model RxtCreatePlane(Vector2 size, char* texture_dir){
  Texture2D texture = LoadTexture(texture_dir);

  Mesh meshPlane = GenMeshPlane(size.x, size.y, 1, 1);

  Model model = LoadModelFromMesh(meshPlane);

  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  return model;
}
