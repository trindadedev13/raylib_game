#ifndef __SKY__
#define __SKY__

#include <raylib.h>

typedef struct {
  Model model; //Criei para caso um dia precise retornar mais de uma variavel

} Sky;

Sky createSkybox();

TextureCubemap LoadCubemapFrom6Faces(
    const char *,
    const char *,
    const char *,
    const char *,
    const char *,
    const char *
);


#endif