#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_core_data_defs.h"

#define SQUARE(X)                   (X * X)


double pos_calc_distance(position_t pt1, position_t pt2) {
    return (sqrt(SQUARE((pt1.x - pt2.x)) + SQUARE((pt1.y - pt2.y))));
}
