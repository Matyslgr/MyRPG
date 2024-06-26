/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_decors
*/

#include "rpg.h"

static void init_decor_anim2(decor_anim_t *decor, sfVector2f scale)
{
    int init_col = rand() % decor->nb_cols;

    decor->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(decor->shape, (sfVector2f){decor->width,
        decor->height});
    sfRectangleShape_setFillColor(decor->shape, sfTransparent);
    sfRectangleShape_setOutlineThickness(decor->shape, 1);
    sfRectangleShape_setOutlineColor(decor->shape, sfMagenta);
    sfRectangleShape_setOrigin(decor->shape, (sfVector2f){decor->width / 2,
        decor->height / 2});
    sfRectangleShape_setScale(decor->shape, scale);
    sfRectangleShape_setPosition(decor->shape, decor->pos);
    decor->anim->rect = (sfIntRect){init_col * decor->width, 0,
        decor->width, decor->height};
    sfSprite_setTextureRect(decor->anim->sprite, decor->anim->rect);
}

static decor_anim_t *init_decor_anim(char **infos)
{
    decor_anim_t *decor = malloc(sizeof(decor_anim_t));
    sfVector2f scale = {TILE_SCALE * atof(infos[9]),
        TILE_SCALE * atof(infos[10])};

    decor->type = (!strcmp(infos[0], "G")) ? GROUND : HIGH;
    decor->anim = init_anim(infos[1], atoi(infos[2]), atoi(infos[3]));
    decor->width = atoi(infos[2]);
    decor->height = atoi(infos[3]);
    decor->speed = atof(infos[4]);
    decor->nb_cols = atoi(infos[5]) - 1;
    decor->nb_rows = atoi(infos[6]) - 1;
    decor->pos = (sfVector2f){atoi(infos[7]), atoi(infos[8])};
    sfSprite_setPosition(decor->anim->sprite, decor->pos);
    sfSprite_setScale(decor->anim->sprite, scale);
    decor->rect = (sfIntRect){decor->pos.x, decor->pos.y,
        decor->width, decor->height};
    init_decor_anim2(decor, scale);
    return decor;
}

decor_anim_t **init_decors(unsigned int *size)
{
    char **tab = file_to_array(".decors.csv");
    char **infos = NULL;
    decor_anim_t **decors = malloc(sizeof(decor_anim_t *) *
        (tab_len(tab)) + 1);

    for (int i = 0; tab[i] != NULL; i++) {
        infos = split_string(tab[i], ";");
        decors[i] = init_decor_anim(infos);
        (*size)++;
        free_array(infos);
    }
    printf("\033[1;33mDecors size: %d\033[0m\n", *size);
    free_array(tab);
    return decors;
}
