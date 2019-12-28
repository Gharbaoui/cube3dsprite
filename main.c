#include "cube.h"

int main()
{
    map_inf map;
    player pl;

    int j = -1, i;
    void *img, *win;

    
    i = fill_map_struct(&map, "map.cub");

    pl.map = &map;
    j = -1;
    pl.obj = malloc(sizeof(t_sprite *) * i);
    while (++j < i)
    {
        pl.obj[j] = malloc(sizeof(t_sprite));
        pl.obj[j]->hit = 0;
        pl.obj[j]->order = -1;
    }
    handel_img_memory(&pl);
    handel_fill_img_structs(&pl);
    map.mlx_ptr = mlx_init();
    map.img_ptr = mlx_new_image(map.mlx_ptr, map.w,map.h);
    win = mlx_new_window(map.mlx_ptr, map.w, map.h, "Game");
    mlx_pixel_put(map.mlx_ptr, win, 1571, 570, 0xffffff);
    draw_maze(&pl);
    map.win_ptr = mlx_new_window(map.mlx_ptr, map.w, map.h, "Game");
    mlx_put_image_to_window(map.mlx_ptr, map.win_ptr, map.img_ptr, 0,0);
    mlx_hook(map.win_ptr, 2, 0, update_scene, &pl);
    mlx_loop(map.mlx_ptr);
}

