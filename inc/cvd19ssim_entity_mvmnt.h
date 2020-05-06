#ifndef _CVD19SSIM_ENTITY_MVMNT_H
#define _CVD19SSIM_ENTITY_MVMNT_H

#include <stdint.h>

typedef struct _position {
    uint32_t x;
    uint32_t y;
} position_t;

typedef struct _cvd19ssim_entity_mvmnt {

    position_t cur_pos;
    position_t acceleration;

} cvd19ssim_entity_mvmnt_t;

int init_position(position_t *, uint32_t, uint32_t);
int add_2_postions_to_first(position_t *, position_t *);
int scale_position(position_t *, uint32_t);



#endif /* _CVD19SSIM_ENTITY_MVMNT_H */
