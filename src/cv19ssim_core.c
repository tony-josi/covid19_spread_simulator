#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"

static void print_cvd19ssim_core_t_(cvd19ssim_core_t *);

CVD19SSIM_STATUS_t cvd19ssim_RUNNER_MAIN() {
    
    srand(time(0)); 
    cvd19ssim_core_t hCVD19;

    if(cvd19ssim_core_t_init(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    print_cvd19ssim_core_t_(&hCVD19);

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
    HCVD19->population_data.max_allowed_population_in_city = 500;
    HCVD19->population_data.cur_population = \
    HCVD19->population_data.max_allowed_population_in_city - RAND_GEN(100);
    HCVD19->population_data.total_population = \
    HCVD19->population_data.cur_population;
    HCVD19->population_data.total_infected = 0;
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

static void print_cvd19ssim_core_t_(cvd19ssim_core_t *HCVD19) {

    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
    HCVD19->avg_birth_rate,
    HCVD19->avg_death_rate,
    HCVD19->capacity_per_hospital,
    HCVD19->num_of_hospitals_in_city,
    HCVD19->city_space,
    HCVD19->cur_filled_hospital_capacity,
    HCVD19->population_data.max_allowed_population_in_city,
    HCVD19->population_data.cur_population,
    HCVD19->population_data.total_population,
    HCVD19->population_data.total_infected,
    HCVD19->population_data.total_infected_n_died,
    HCVD19->population_data.total_recovered,
    HCVD19->max_spread_distance);

}


