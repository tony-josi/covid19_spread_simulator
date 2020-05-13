#include <math.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_entity_mvmnt.h"

#define SQUARE(X)                   (X * X)


double pos_calc_distance(position_t pt1, position_t pt2) {
    
    return (sqrt(MAG((SQUARE((pt1.x - pt2.x)) + SQUARE((pt1.y - pt2.y))))));

}

bool check_if_in_spread_range(cvd19ssim_core_t hCVD19, uint32_t i, uint32_t j) {
    
    if(pos_calc_distance(hCVD19.entities[i].pos_data.cur_pos, hCVD19.entities[j].pos_data.cur_pos) <= \
    ((double)hCVD19.max_spread_distance))
        return 1;
    else
        return 0;

}
