/*
 * Copyright (C)    Tony Josi
 * Date             19-05-2020
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_entity_mvmnt.h"
#include "../inc/cvd19ssim_core_data_defs.h"

#define SQUARE(X)                   (X * X)

int pos_move(cvd19ssim_core_t *HCVD19) {
    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {
        
        if(HCVD19->entities[i].is_alive && \
        !(HCVD19->entities[i].entity_cvd_report.is_hospitalized) && \
        !(HCVD19->entities[i].entity_cvd_report.is_quarantined)) {
            if(CHECK_RANGE((HCVD19->entities[i].pos_data.cur_pos.x + \
            HCVD19->entities[i].pos_data.speed.x)))
                HCVD19->entities[i].pos_data.cur_pos.x += \
                HCVD19->entities[i].pos_data.speed.x;
            if(CHECK_RANGE((HCVD19->entities[i].pos_data.cur_pos.y + \
            HCVD19->entities[i].pos_data.speed.y)))
                HCVD19->entities[i].pos_data.cur_pos.y += HCVD19->entities[i].pos_data.speed.y;
        }

        if(RAND_GEN(PERCENT) > (PERCENT - PERCENT_OF_HIGH_SPEED))
            HCVD19->entities[i].pos_data.speed.x = MIN_SPEED + \
            RAND_GEN(HIGH_SPEED_POSSIBLE);
        else
            HCVD19->entities[i].pos_data.speed.x = MIN_SPEED + \
            RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
        if(RAND_GEN(PERCENT) > (PERCENT - PERCENT_OF_HIGH_SPEED))
            HCVD19->entities[i].pos_data.speed.y = MIN_SPEED + \
            RAND_GEN(HIGH_SPEED_POSSIBLE);
        else
            HCVD19->entities[i].pos_data.speed.y = MIN_SPEED + \
            RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));

        if(RAND_GEN(2))
            HCVD19->entities[i].pos_data.speed.x *= -1;
        if(RAND_GEN(2))
            HCVD19->entities[i].pos_data.speed.y *= -1;

    }
    return 0;
}


double pos_calc_distance(position_t pt1, position_t pt2) {
    
    return (sqrt((SQUARE((pt1.x - pt2.x)) + SQUARE((pt1.y - pt2.y)))));

}

bool check_if_in_spread_range(cvd19ssim_core_t hCVD19, uint32_t i, uint32_t j) {
    
    double dist = pos_calc_distance(hCVD19.entities[i].pos_data.cur_pos, \
    hCVD19.entities[j].pos_data.cur_pos);
            //printf("Dist from inf %d to %d: %f\n", i, j, dist);

    if(dist <= ((double)hCVD19.max_spread_distance)) {
        //printf("Dist from inf %d to %d: %f\n", i, j, dist);
        return 1;
    }
    else
        return 0;

}
