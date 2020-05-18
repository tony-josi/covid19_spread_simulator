/*
 * Copyright (C)    Tony Josi
 * Date             19-05-2020
 */

#ifndef _CVD19SSIM_ENTITY_MVMNT_H
#define _CVD19SSIM_ENTITY_MVMNT_H

#include <stdint.h>
#include <stdbool.h>
#include "cvd19ssim_core.h"

int pos_move(cvd19ssim_core_t *);
double pos_calc_distance(position_t, position_t);
bool check_if_in_spread_range(cvd19ssim_core_t, uint32_t, uint32_t);

#endif /* _CVD19SSIM_ENTITY_MVMNT_H */
