#include "textura.h"

#include <SDL_image.h>

extern SDL_Texture *carregarTextura(SDL_Renderer *render, const char *arquivo) {
    SDL_Surface *img = IMG_Load(arquivo);

    if (!img) {
        return NULL;
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(render, img);
    SDL_FreeSurface(img);

    return text;
}
