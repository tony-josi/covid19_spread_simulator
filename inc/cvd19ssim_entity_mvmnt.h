#ifndef _CVD19SSIM_ENTITY_MVMNT_H
#define _CVD19SSIM_ENTITY_MVMNT_H

#include <stdint.h>

typedef struct _position {
    uint32_t x;
    uint32_t y;
} position_t;

typedef struct _speed {
    int x;
    int y;
} speed_t;

typedef struct _cvd19ssim_entity_mvmnt {

    position_t      cur_pos;
    speed_t         speed;

} cvd19ssim_entity_mvmnt_t;

double pos_calc_distance(position_t, position_t);

#endif /* _CVD19SSIM_ENTITY_MVMNT_H */
