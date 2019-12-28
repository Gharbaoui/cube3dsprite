#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include "get_next_line.h"

typedef struct 
{
    char *north;
    char *weast;
    char *east;
    char *south;
    char *sprite;
    int floor;
    int celling;
}       texture;

typedef struct 
{
    int width;
    int height;
    int colorchar;
    int numcolors;
    char **strcolor;
    int *num;
    char **xpm;
}   image;

typedef struct 
{
    double x;
    double y;  
} point;

typedef struct 
{
    double lengthblock;
    double lengthsprite;
    int wasvert;
    int washorz;
    point *pblock;
    point *psprite;
} rayhit;

typedef struct 
{
    texture *txt;
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int width;
    int height;
    int map_heigth;
    char **map_lines;
    int h;
    int w;
}       map_inf;

typedef struct 
{
    point pos;
    image img;
    point hitp;
    double length;
    int hit;
    int order;
    int offset;
    double width;
}       t_sprite;

typedef struct 
{
    double x;
    double y;
    double slope;
    double c;
}   line;

typedef struct 
{
    double xs;
    double ys;
    double x;
    double y;
    int order;
    double look;
    image *img[4];
    t_sprite **obj;
    map_inf *map;
}       player;

typedef struct 
{
    int up;
    int down;
    int right;
    int left;
    int strightright;
    int strightleft;
    int strightup;
    int strightdown;
    double angel;
    int spech;
    int wasvert;
    double xh, yh;
    double xv, yv;
} dirction;

// the start of fill struct map_info with inforamation that need
int     str_cmp(char *s1, char **s2, int len, int ismaoveable);
int    fill_map_struct(map_inf *map, char *mapname);
void    handel_resolution(map_inf *map, char **line);
int     is_digit(char c);
int     ft_atoi(char **numstr);
char    *str_cat(char **line, int isfree, int len, int ismoveable);
void    handel_texture(texture *txt, char **line, int flag);
int     rgb_to_int(char *str);
int     count_height_map(map_inf *map, int fd, char *line);
int     fill_map_lines(char ***line, int height, int length, int fd);
void    handel_rest_pos_sprite(player *pl, int j, double x, double y, int lineindex);
// the end of this part

void    draw_one_line(char *line, player *pl, int lineindex);
void    draw_maze(player *pl);
void    put_pixel(map_inf *map, int x, int y, int color);
int     can_move(player *pl, char c, double speed);
int is_there_wall(map_inf *map, double x, double y, point *hitpos);
void    player_pos(player *inf, double speed, char c, double angel);
int     update_scene(int key, player *pl);
void    draw_player(player *pl);
char    *line_without_spaces(char *str, int *obj);


// the start of raycasting 
double  raycasting(player *pl, double angel, double *xp, double *yp, int *wasvert);
double  handel_h(double dx, double ypos, player *pl, dirction *dir);
double  calculate_length(double x1, double y1, double x2, double y2);
void    handel_ypos_dx(double *ypos, double *dx, player *pl, dirction dir);
void    ray_dirction(dirction *dir, double angel);
double  handel_angel(double angel);
int     can_move(player *pl, char c, double speed);
double  handel_raycasting_vert(player *pl, dirction *dir);
double  handel_v(double xpos, double dy, player *pl, dirction *dir);
int     is_on_line(double slope, double x0, double y0, double x, double y);
// the end of raycasting

// the start of drawing 
void    draw3dmap(double length, int x, player *pl, int wasvert, double xp, double yp);
void    handel_img_memory(player *pl);
int     handel_hex(char *str);
void    handel_fill_img_structs(player *pl);
void    fill_image_info(image *img, char *filename, int fd);
void    handel_rest_fill_image(image *img, int fd);
void    fill_xpm(image *img, int fd);
int     handel_image_color(int wasvert, double xp, double yp, player  *pl, double height, int heightindex);
int     index_in_image(char *line, image img);

// the end of drawing
void    rest_pos_sprite(player *pl, int lineindex, double y, int j);
int     handel_sprite_index(t_sprite **sp, point hitpos);
void    offset_sprite(t_sprite *sp, player *pl, point p, dirction dir);
int     is_in_range(double xinter,double yinter, double left, double right, double up, double down);
double sprite_length(line spline, double yup, double ydown, double left, double right);
int   sprite_color(player *pl, int heightindex, double height);