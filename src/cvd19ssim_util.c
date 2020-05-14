#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_util.h"
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"

#ifndef _WIN32
    static int sleep_in_ms(long);
#endif

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

        if(is_infected)
            init_entity_inf_cvd_report(entities, i);

        entities[i].entity_cvd_report.days_of_infections = 0;
        entities[i].entity_cvd_report.have_symptoms = \
        (RAND_GEN(100) < PERCENT_OF_AFFECTED_WITH_SYMPTOMS) ? 1 : 0;
        entities[i].entity_cvd_report.is_hospitalized = 0;
        entities[i].entity_cvd_report.is_quarantined = 0;
        entities[i].entity_cvd_report.is_recovered = 0;
        entities[i].entity_cvd_report.is_tested = 0;

        entities[i].pos_data.cur_pos.x = SQUARE_FRAME_SIZE + RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5));
        entities[i].pos_data.cur_pos.y = SQUARE_FRAME_SIZE + RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5));
        entities[i].pos_data.speed.x = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
        entities[i].pos_data.speed.y = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));


}

void init_entity_inf_cvd_report(entity_health_record_t *entities, uint32_t j) {

    entities[j].entity_cvd_report.is_infected = 1;
    entities[j].entity_cvd_report.days_of_infections = 0;
    entities[j].entity_cvd_report.is_hospitalized = 0;
    entities[j].entity_cvd_report.is_quarantined = 0;
    entities[j].entity_cvd_report.have_symptoms = \
    (((RAND_GEN(PERCENT)) < PERCENT_OF_AFFECTED_WITH_SYMPTOMS) ? 1 : 0);
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
