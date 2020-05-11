#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"


#ifndef _WIN32
    static int sleep_in_ms(long);
#endif
static void sleep_ms();
static void print_cvd19ssim_core_t(cvd19ssim_core_t *);
static void print_cvd19ssim_entity_health_record_t(cvd19ssim_core_t *, uint32_t);

CVD19SSIM_STATUS_t cvd19ssim_RUNNER_MAIN() {
    
    srand(time(0)); 
    cvd19ssim_core_t hCVD19;

    if(cvd19ssim_core_t_init(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    if(cvd19ssim_core_t_init_entities(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    UNUSED(print_cvd19ssim_core_t);
    UNUSED(print_cvd19ssim_entity_health_record_t);
    /*
    UNUSED(print_cvd19ssim_core_t(&hCVD19));
    printf("__________________INIT   D O N E_______________________\n");
    for(uint32_t i = 0; i < hCVD19.population_data.cur_population; i++) {
        printf("Entty: %d\n", i);
        print_cvd19ssim_entity_health_record_t(&hCVD19, i);
        printf("__________________INIT   D O N E_______________________\n");
    }
    */

    output_current_frame_ppm(&hCVD19);
    while (1) {

        sleep_ms();
        if(pos_move(&hCVD19))
            return CVD19SSIM_FAIL;

        output_current_frame_ppm(&hCVD19);

   }
   
    

    if(cvd19ssim_core_t_deinit(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    return CVD19SSIM_SUCCESS;

}

CVD19SSIM_STATUS_t cvd19ssim_core_t_init(cvd19ssim_core_t *HCVD19) {
    /* should read params from file or call master
    func. with struct feild values */
    UNUSED(RAND_GEN(3));
    HCVD19->avg_birth_rate = 2 + RAND_GEN(2);
    HCVD19->avg_death_rate = 2 + RAND_GEN(2);
    HCVD19->capacity_per_hospital = 20;
    HCVD19->num_of_hospitals_in_city = 4;
    HCVD19->city_space = 108;
    HCVD19->cur_filled_hospital_capacity = 0;
    HCVD19->population_data.max_allowed_population_in_city = MAX_ALLOWED_POPULATION;
    HCVD19->population_data.cur_population = \
    HCVD19->population_data.max_allowed_population_in_city - RAND_GEN(100);
    HCVD19->population_data.total_population = \
    HCVD19->population_data.cur_population;
    HCVD19->initialy_infected = MIN_INITIALLY_INFECTED + \
    RAND_GEN(HCVD19->population_data.cur_population / 20);
    HCVD19->population_data.total_infected = HCVD19->initialy_infected;
    HCVD19->population_data.total_infected_n_died = 0;
    HCVD19->population_data.total_recovered = 0;
    HCVD19->max_spread_distance = 3;
    
    if(!(HCVD19->entities = 
    malloc(sizeof(entity_health_record_t) * HCVD19->population_data.max_allowed_population_in_city)))
        return CVD19SSIM_FAIL;

    return CVD19SSIM_SUCCESS;

}

CVD19SSIM_STATUS_t cvd19ssim_core_t_deinit(cvd19ssim_core_t *HCVD19) {

    free(HCVD19->entities);
    return CVD19SSIM_SUCCESS;

}

static void print_cvd19ssim_core_t(cvd19ssim_core_t *HCVD19) {

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

CVD19SSIM_STATUS_t cvd19ssim_core_t_init_entities(cvd19ssim_core_t *HCVD19) {

    uint32_t infected_cntr = 0;
    for (uint32_t i = 0; i < HCVD19->population_data.cur_population; i++) {

        HCVD19->entities[i].is_alive = 1;
        HCVD19->entities[i].prob_early_death = MIN_PROB_OF_EARLY_NORMAL_DEATH + \
        RAND_GEN((MAX_PROB_OF_EARLY_NORMAL_DEATH - MIN_PROB_OF_EARLY_NORMAL_DEATH));
        HCVD19->entities[i].prob_better_immunity = MIN_PROB_OF_BETTER_IMMUNITY + \
        RAND_GEN((MAX_PROB_OF_BETTER_IMMUNITY - MIN_PROB_OF_BETTER_IMMUNITY));

        if(infected_cntr < HCVD19->initialy_infected) {
            HCVD19->entities[i].entity_cvd_report.is_infected = 1;
            ++infected_cntr;
        }
        HCVD19->entities[i].entity_cvd_report.days_of_infections = 0;
        HCVD19->entities[i].entity_cvd_report.have_symptoms = \
        (RAND_GEN(100) < PERCENT_OF_AFFECTED_WITH_SYMPTOMS) ? 1 : 0;
        HCVD19->entities[i].entity_cvd_report.is_hospitalized = 0;
        HCVD19->entities[i].entity_cvd_report.is_quarantined = 0;
        HCVD19->entities[i].entity_cvd_report.is_recovered = 0;
        HCVD19->entities[i].entity_cvd_report.is_tested = 0;

        HCVD19->entities[i].pos_data.cur_pos.x = RAND_GEN(MAX_CITY_DEFAULT_SIZE);
        HCVD19->entities[i].pos_data.cur_pos.y = RAND_GEN(MAX_CITY_DEFAULT_SIZE);
        HCVD19->entities[i].pos_data.speed.x = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));
        HCVD19->entities[i].pos_data.speed.y = MIN_SPEED + RAND_GEN(((MAX_SPEED - MIN_SPEED) + 1));

    }

    return CVD19SSIM_SUCCESS;

}

static void print_cvd19ssim_entity_health_record_t(cvd19ssim_core_t *HCVD19, uint32_t idx) {

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


static void sleep_ms() {

    /* if Windows system */
    #ifdef _WIN32
        Sleep(DEFAULT_SLEEP_TIME);
    /* UNIX based systems */
    #else
        sleep_in_ms(DEFAULT_SLEEP_TIME);
    #endif
}
