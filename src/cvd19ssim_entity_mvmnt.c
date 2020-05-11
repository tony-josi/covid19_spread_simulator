#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_entity_mvmnt.h"
#include "../inc/cvd19ssim_core_data_defs.h"

int pos_move(cvd19ssim_core_t *HCVD19) {
    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {
        
        if(HCVD19->entities[i].is_alive & !(HCVD19->entities[i].entity_cvd_report.is_hospitalized)) {
            if(CHECK_RANGE((HCVD19->entities[i].pos_data.cur_pos.x + HCVD19->entities[i].pos_data.speed.x)))
                HCVD19->entities[i].pos_data.cur_pos.x += HCVD19->entities[i].pos_data.speed.x;
            if(CHECK_RANGE((HCVD19->entities[i].pos_data.cur_pos.y + HCVD19->entities[i].pos_data.speed.y)))
                HCVD19->entities[i].pos_data.cur_pos.y += HCVD19->entities[i].pos_data.speed.y;
        }

        if(RAND_GEN(PERCENT) > (PERCENT - PERCENT_OF_HIGH_SPEED))
            HCVD19->entities[i].pos_data.speed.x = RAND_GEN(HIGH_SPEED_POSSIBLE);
        else
            HCVD19->entities[i].pos_data.speed.x = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
        if(RAND_GEN(PERCENT) > (PERCENT - PERCENT_OF_HIGH_SPEED))
            HCVD19->entities[i].pos_data.speed.y = RAND_GEN(HIGH_SPEED_POSSIBLE);
        else
            HCVD19->entities[i].pos_data.speed.y = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));

        if(RAND_GEN(2))
            HCVD19->entities[i].pos_data.speed.x *= -1;
        if(RAND_GEN(2))
            HCVD19->entities[i].pos_data.speed.y *= -1;

    }
    return 0;
}
