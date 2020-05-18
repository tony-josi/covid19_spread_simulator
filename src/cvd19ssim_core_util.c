#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_core_util.h"
#include "../inc/cvd19ssim_ppm.h"

CVD19SSIM_STATUS_t cvd19ssim_struct_init(cvd19ssim_core_t *hCVD19) {
    
    if(cvd19ssim_core_t_init(hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;
    if(cvd19ssim_core_t_init_entities(hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;
    
    return CVD19SSIM_SUCCESS;
}


CVD19SSIM_STATUS_t cvd19ssim_daily_summary_calc(cvd19ssim_core_t *HCVD19) {

    HCVD19->days_passed += 1;
    
    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {
        if(HCVD19->entities[i].is_alive) {
            HCVD19->entities[i].days_alive += 1;
            if(HCVD19->entities[i].entity_cvd_report.is_infected)
                HCVD19->entities[i].entity_cvd_report.days_of_infections += 1;
        }
    }
    return CVD19SSIM_SUCCESS;

} 

CVD19SSIM_STATUS_t cvd19ssim_log_per_day_report(cvd19ssim_core_t *HCVD19, FILE *fptr) {

    char str_buff[LOG_FILE_LINE_BUFF_SIZE];

    sprintf(str_buff, "DAY: %d, CUR_POPL: %d, TOTAL_CVD_INF: %d, TOTAL_CVD_ACTIVE: %d, \
TOTAL_CVD_RECVRD: %d, TOTAL_CVD_DCSD: %d, NEW_BIRTHS: %d, NORML_DEATHS: %d\n", \
    HCVD19->days_passed, HCVD19->population_data.cur_population, \
    HCVD19->population_data.total_infected, \
    (HCVD19->population_data.total_infected - \
    (HCVD19->population_data.total_recovered + \
    HCVD19->population_data.total_infected_n_died)), \
    HCVD19->population_data.total_recovered, \
    HCVD19->population_data.total_infected_n_died,
    HCVD19->population_data.total_new_births,
    HCVD19->population_data.total_normal_deaths);

    //printf("%s", str_buff);
    fputs(str_buff, fptr);

    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_core_t_init(cvd19ssim_core_t *HCVD19) {
    /* should read params from file or call master
    func. with struct feild values */
    UNUSED(RAND_GEN(3));
    HCVD19->avg_birth_rate = 2 + RAND_GEN(2);
    HCVD19->avg_death_rate = 2 + RAND_GEN(2);
    HCVD19->capacity_per_hospital = 20;
    HCVD19->num_of_hospitals_in_city = 3;
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
    HCVD19->population_data.total_new_births = 0;
    HCVD19->population_data.total_normal_deaths = 0;
    HCVD19->max_spread_distance = MAX_SPREAD_DISTANCE;
    HCVD19->days_passed = 0;
    HCVD19->max_testing_capacity = MAX_TESTING_CAP;

    if(!(HCVD19->hospital_locations = 
    calloc(sizeof(position_t), HCVD19->num_of_hospitals_in_city)))
        return CVD19SSIM_FAIL;

    for(uint32_t i = 0; i < HCVD19->num_of_hospitals_in_city; ++i) {
        HCVD19->hospital_locations[i].x = SQUARE_FRAME_SIZE + (MAX_CITY_DEFAULT_SIZE / 2);
        HCVD19->hospital_locations[i].y = SQUARE_FRAME_SIZE + \
        ((MAX_CITY_DEFAULT_SIZE / HCVD19->num_of_hospitals_in_city) / 2) + \
        ((i) * (MAX_CITY_DEFAULT_SIZE / HCVD19->num_of_hospitals_in_city));
    }
    if(!(HCVD19->entities = 
    calloc(sizeof(entity_health_record_t), HCVD19->population_data.max_allowed_population_in_city)))
        return CVD19SSIM_FAIL;

    return CVD19SSIM_SUCCESS;

}

CVD19SSIM_STATUS_t cvd19ssim_core_t_deinit(cvd19ssim_core_t *HCVD19) {

    free(HCVD19->entities);
    return CVD19SSIM_SUCCESS;

}
