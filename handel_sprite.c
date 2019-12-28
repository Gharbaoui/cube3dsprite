#include "cube.h"

void    offset_sprite(t_sprite *sp, player *pl, point p, dirction dir)
{
    double slope1, slope2, angel, length, middel, between;
    double c1, c2;
    double xinter, yinter;
    int offset, range;
    double x0, y0, x1, y1;
    double xs, ys;

    line spline;
    line ydown;
    line yup;
    line xleft, xright;

    length = -9;
    x0 = (int)pl->x;
    y0 = (int)pl->y;
    x1 = p.x;
    y1 = p.y;
    xs = sp->pos.x;
    ys = sp->pos.y;
    if (x0 != x1 && y0 != y1)
    {
        slope1 = (y0 - y1) / (x0 - x1);
        slope2 = -1 / slope1;
        c1 = y0 - (slope1 * x0);
        c2 = ys - (slope2 * xs);
        xinter = (c2 - c1) / (slope1 - slope2);
        yinter = (slope2 * xinter) + c2;
        spline.slope = slope2;
        spline.c = c2;
    }
    else if (x0 == x1)
    {
        length = pl->map->width;
        xinter = x0;
        yinter = ys;
    }
    else if (y0 == y1)
    {
        length = pl->map->height;
        yinter = y0;
        xinter = xs;
    }
    yup.y = (int)y1 - ((int)y1 % pl->map->height);
    ydown.y = yup.y + pl->map->height;

    xleft.x = (int)x1 - ((int)x1 % pl->map->width);
    xright.x = xleft.x + pl->map->width;
    range = is_in_range(xinter, yinter, xleft.x, xright.x, yup.y, ydown.y);
    if (range)
    {
        if (length == -9)
            length = sprite_length(spline, yup.y, ydown.y, xleft.x, xright.x);
        sp->width = length;
        middel = length / 2;
        between = calculate_length(xs, ys, xinter, yinter);
        // if (dir.up || dir.strightup)
        // {
        //     if (xs > xinter)
        //         offset = (int)middel - (int)between;
        //     else
        //         offset = (int)middel + (int)between;
        // }
        // else if (dir.down || dir.strightdown)
        // {
        //     if (xs > xinter)
        //         offset = (int)middel + (int)between;
        //     else
        //         offset = (int)middel - (int)between;
        // }
        // else if (dir.strightright)
        // {
        //     if (ys > yinter)
        //          offset = (int)middel - (int)between;
        //     else
        //          offset = (int)middel + (int)between;
        // }
        // else if (dir.strightright)
        // {
        //     if (ys > yinter)
        //          offset = (int)middel + (int)between;
        //     else
        //          offset = (int)middel - (int)between;
        // }
        offset = (int)middel - (int)between;
        sp->offset = offset;
        sp->length = calculate_length(pl->x, pl->y, xs, ys);
    }
    else
        sp->hit = 0;
    
}