#include "cube.h"

int     handel_sprite_index(t_sprite **sp, point hitpos)
{
    int i;

    i = -1;

    while (sp[++i]->pos.x >= 0)
        if (sp[i]->pos.x == hitpos.x && sp[i]->pos.y == hitpos.y)
            return i;
    return -5;
}