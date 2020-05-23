/*
 * Copyright (C)    Tony Josi
 * Date             19-05-2020
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_util.h"
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"

#ifndef _WIN32
    #include <time.h>
    static int sleep_in_ms(long);
#else
    #include <windows.h>
#endif /* _WIN32 */

void print_cvd19ssim_core_t(cvd19ssim_core_t *HCVD19) {

    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
    HCVD19->avg_birth_rate,
    HCVD19->avg_death_rate,
    HCVD19->capacity_per_hospital,
    HCVD19->num_of_hospitals_in_city,
    HCVD19->city_space,
    HCVD19->cur_filled_hospital_capacity,
    HCVD19->population_data.max_allowed_population_in_city,
    HCVD19->population_data.cur_population,
    HCVD19->initialy_infected,
    HCVD19->population_data.total_population,
    HCVD19->population_data.total_infected,
    HCVD19->population_data.total_infected_n_died,
    HCVD19->population_data.total_recovered,
    HCVD19->max_spread_distance);

}

void print_cvd19ssim_entity_health_record_t(cvd19ssim_core_t *HCVD19, uint32_t idx) {

    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
    HCVD19->entities[idx].is_alive,
    HCVD19->entities[idx].prob_better_immunity,
    HCVD19->entities[idx].prob_early_death,
    HCVD19->entities[idx].pos_data.cur_pos.x,
    HCVD19->entities[idx].pos_data.cur_pos.y,
    HCVD19->entities[idx].pos_data.speed.x,
    HCVD19->entities[idx].pos_data.speed.y,
    HCVD19->entities[idx].entity_cvd_report.days_of_infections,
    HCVD19->entities[idx].entity_cvd_report.have_symptoms,
    HCVD19->entities[idx].entity_cvd_report.is_hospitalized,
    HCVD19->entities[idx].entity_cvd_report.is_infected,
    HCVD19->entities[idx].entity_cvd_report.is_quarantined,
    HCVD19->entities[idx].entity_cvd_report.is_recovered,
    HCVD19->entities[idx].entity_cvd_report.is_tested);

}

void init_entity(entity_health_record_t *entities, uint32_t i, bool is_infected) {

        entities[i].is_alive = 1;
        entities[i].prob_early_death = MIN_PROB_OF_EARLY_NORMAL_DEATH + \
        RAND_GEN((MAX_PROB_OF_EARLY_NORMAL_DEATH - MIN_PROB_OF_EARLY_NORMAL_DEATH));
        entities[i].prob_better_immunity = MIN_PROB_OF_BETTER_IMMUNITY + \
        RAND_GEN((MAX_PROB_OF_BETTER_IMMUNITY - MIN_PROB_OF_BETTER_IMMUNITY));
        entities[i].days_alive = 0;

        init_entity_inf_cvd_report(entities, i, is_infected);

        entities[i].pos_data.cur_pos.x = SQUARE_FRAME_SIZE + \
        RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5));
        entities[i].pos_data.cur_pos.y = SQUARE_FRAME_SIZE + \
        RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5));
        entities[i].pos_data.speed.x = MIN_SPEED + \
        RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
        entities[i].pos_data.speed.y = MIN_SPEED + \
        RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
}

void init_entity_inf_cvd_report(entity_health_record_t *entities, uint32_t j, bool is_infected) {

    if(is_infected) {
        entities[j].entity_cvd_report.is_infected = 1;
        entities[j].entity_cvd_report.have_symptoms = \
        (((RAND_GEN(PERCENT)) < PERCENT_OF_AFFECTED_WITH_SYMPTOMS) ? 1 : 0);
    }
    else {
        entities[j].entity_cvd_report.is_infected = 0;
        entities[j].entity_cvd_report.have_symptoms = 0;
    }
        
    entities[j].entity_cvd_report.days_of_infections = 0;
    entities[j].entity_cvd_report.is_hospitalized = 0;
    entities[j].entity_cvd_report.is_quarantined = 0;
    entities[j].entity_cvd_report.is_tested = 0;
    
}

FILE* init_log_file(char *f_name) {
    FILE* l_fptr = NULL;
    l_fptr = fopen(f_name, "w");
    return l_fptr;
}


void de_init_log_file(FILE *l_fptr) {
    fclose(l_fptr);
} 

bool cvd_death_chance(entity_health_record_t *entty) {

    uint32_t hosp_factor = \
    ((entty->entity_cvd_report.is_hospitalized) ? (RAND_GEN(PERCENT)) : 0);
    uint32_t temp_data = entty->prob_better_immunity + hosp_factor;
    temp_data = (uint32_t) temp_data / 2;

    if(temp_data < CVD_DEATH_FACTOR)
        return 1;

    return 0;
}

bool if_already_in_buffer(uint32_t *buff, uint32_t size, uint32_t item) {
    
    for(uint32_t i = 0; i < size; ++i) {
        if(buff[i] == item)
            return 1;
    }
    return 0;
}



#ifndef _WIN32
    static int sleep_in_ms(long ms) {

        struct timespec ts;
        int res;

        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;

        do {
            res = nanosleep(&ts, &ts);
        } while (res);

        return res;
    }
#endif


void sleep_ms() {
    /* if Windows system */
    #ifdef _WIN32
        Sleep(DEFAULT_SLEEP_TIME);
    /* UNIX based systems */
    #else
        sleep_in_ms(DEFAULT_SLEEP_TIME);
    #endif
}
