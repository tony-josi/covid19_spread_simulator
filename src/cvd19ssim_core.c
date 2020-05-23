/*
 * Copyright (C)    Tony Josi
 * Date             19-05-2020
 */

#include <stdio.h>
#include <time.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_util.h"
#include "../inc/cvd19ssim_entity_mvmnt.h"
#include "../inc/cvd19ssim_core_util.h"

CVD19SSIM_STATUS_t cvd19ssim_RUNNER_MAIN() {
    
    srand(time(0)); 
    cvd19ssim_core_t hCVD19;
    uint64_t loop_cntr = 0;
    FILE *log_fptr;
    bool is_log_closed = 0;
    CVD19SSIM_STATUS_t ret_code = CVD19SSIM_SUCCESS;

    ret_code |= cvd19ssim_struct_init(&hCVD19);
        
#if ENABLE_LOGGING
    if((log_fptr = init_log_file(LOG_FILE_PATH)) == NULL)
        return CVD19SSIM_INIT_FAIL;
#endif /* ENABLE_LOGGING */

    for(int i = 0; i < STILL_FRAMES_AT_START; i++) {
        sleep_ms();
        //output_current_frame_ppm(&hCVD19);
    }
    
    while (((loop_cntr++ )< DEBUG_MAX_DAYS) && (ret_code == CVD19SSIM_SUCCESS)) {
#if ENABLE_LOGGING
        if(loop_cntr <= MAX_NUM_OF_LOOPS_TO_LOG)
            cvd19ssim_log_per_day_report(&hCVD19, log_fptr);
        else
            if(!is_log_closed) {
                de_init_log_file(log_fptr);
                is_log_closed = 1;
            }
#endif /* ENABLE_LOGGING */

        sleep_ms();
        ret_code |= cvd19ssim_daily_summary_calc(&hCVD19);
        ret_code |= cvd19ssim_normal_deaths(&hCVD19);
        ret_code |= cvd19ssim_normal_births(&hCVD19);
        ret_code |= cvd19ssim_covid_deaths(&hCVD19);
        
        if(pos_move(&hCVD19))
            return CVD19SSIM_FAIL;
        
        ret_code |= cvd19ssim_covid_infections(&hCVD19);
        ret_code |= cvd19ssim_daily_diagnosis(&hCVD19);
        ret_code |= cvd19ssim_daily_recovery(&hCVD19);
        
        //output_current_frame_ppm(&hCVD19);
    }
    if(cvd19ssim_core_t_deinit(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_normal_deaths(cvd19ssim_core_t *HCVD19) {
    uint32_t deaths_today = 0;
    if(HCVD19->population_data.cur_population > 0) {
        if((RAND_GEN(PERCENT)) > (PERCENT - PERCENT_CHANCE_DEATHS_OCCUR)) {
            for(uint32_t i = 0; ((i < HCVD19->population_data.max_allowed_population_in_city) & \
            (deaths_today < HCVD19->avg_death_rate)); ++i) {
                if(HCVD19->entities[i].is_alive && \
                ((HCVD19->entities[i].prob_better_immunity - HCVD19->entities[i].prob_early_death) < \
                (NORMAL_DEATH_THRESHOLD)) && (HCVD19->population_data.cur_population > 0)) {
                    HCVD19->entities[i].is_alive = 0;
                    ++deaths_today;
                    HCVD19->population_data.cur_population -= 1;
                    if(HCVD19->entities[i].entity_cvd_report.is_infected)
                        HCVD19->population_data.total_infected_n_died += 1;
                    else
                        HCVD19->population_data.total_normal_deaths += 1;
                }
            }           
        }
    }
    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_normal_births(cvd19ssim_core_t *HCVID19) {
    uint32_t births_today = 0;
    if(HCVID19->population_data.cur_population < \
    HCVID19->population_data.max_allowed_population_in_city) {
        if((RAND_GEN(PERCENT)) > (PERCENT - PERCENT_CHANCE_BIRTHS_OCCUR)) {
            for(uint32_t i = 0; ((i < HCVID19->population_data.max_allowed_population_in_city) && \
            (births_today < HCVID19->avg_birth_rate)); ++i) {
                if(!(HCVID19->entities[i].is_alive) && (HCVID19->population_data.cur_population < \
                HCVID19->population_data.max_allowed_population_in_city)) {
                    init_entity(HCVID19->entities, i, 0);
                    HCVID19->population_data.cur_population += 1;
                    HCVID19->population_data.total_new_births += 1;
                    ++births_today;
                }
            }
        }
    }
    return CVD19SSIM_SUCCESS;
}


CVD19SSIM_STATUS_t cvd19ssim_core_t_init_entities(cvd19ssim_core_t *HCVD19) {

    uint32_t infected_cntr = 0, i = 0;
    for (i = 0; i < HCVD19->population_data.cur_population; i++) {
        if(infected_cntr < HCVD19->initialy_infected) {
            init_entity(HCVD19->entities, i, 1);
            ++infected_cntr;
        }
        else
            init_entity(HCVD19->entities, i, 0);
    }

    for (; i < HCVD19->population_data.max_allowed_population_in_city; i++)
        HCVD19->entities[i].is_alive = 0;

    return CVD19SSIM_SUCCESS;

}


CVD19SSIM_STATUS_t cvd19ssim_covid_infections(cvd19ssim_core_t *HCVD19) {

    uint32_t temp_inf_ent_buff[MAX_ALLOWED_POPULATION], buff_cntr = 0;

    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {
        if(HCVD19->entities[i].is_alive && HCVD19->entities[i].entity_cvd_report.is_infected && \
        !(HCVD19->entities[i].entity_cvd_report.is_quarantined || \
        HCVD19->entities[i].entity_cvd_report.is_hospitalized)) {

            for(uint32_t j = 0; j < HCVD19->population_data.max_allowed_population_in_city; ++j) {
                if(HCVD19->entities[j].is_alive && (i != j) && \
                !(HCVD19->entities[j].entity_cvd_report.is_infected) && \
                !(HCVD19->entities[j].entity_cvd_report.is_recovered)) {
                    
                    if(check_if_in_spread_range(*HCVD19, i, j)){
                        if((RAND_GEN(PERCENT) < PERCENT_CHANCE_OF_CVD_INF_IN_SPRD_DIST)) {
                            if(!(if_already_in_buffer(temp_inf_ent_buff, buff_cntr, j))) {
                                temp_inf_ent_buff[buff_cntr] = j;
                                ++buff_cntr;
                            }
                        }
                    }
                }
            }
        } 
    }
    for(uint32_t j = 0; j < buff_cntr; ++j) {
        HCVD19->population_data.total_infected += 1;
        init_entity_inf_cvd_report(HCVD19->entities, temp_inf_ent_buff[j], 1);
    }

    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_covid_deaths(cvd19ssim_core_t *HCVD19) {
    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {
        if(HCVD19->entities[i].is_alive && HCVD19->entities[i].entity_cvd_report.is_infected) {
            if(HCVD19->entities[i].entity_cvd_report.days_of_infections >= INF_MIN_DEATH_DAYS) {

                if((HCVD19->entities[i].entity_cvd_report.days_of_infections > INF_MAX_DEATH_DAYS) ||\
                (cvd_death_chance(&(HCVD19->entities[i])))) {
                    HCVD19->entities[i].is_alive = 0;
                    HCVD19->population_data.cur_population -= 1;
                    HCVD19->population_data.total_infected_n_died += 1;
                    if(HCVD19->entities[i].entity_cvd_report.is_hospitalized)
                        HCVD19->cur_filled_hospital_capacity -= 1;
                    init_entity_inf_cvd_report(HCVD19->entities, i, 0);
                }
            }
        }
    }
    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_daily_diagnosis(cvd19ssim_core_t *hCVD19) {

    uint32_t temp_tests_done = 0, rand_hosp = 0;
    for(uint32_t i = 0; i < hCVD19->population_data.max_allowed_population_in_city; ++i) {
        if(hCVD19->entities[i].is_alive && \
        hCVD19->entities[i].entity_cvd_report.is_infected && \
        !(hCVD19->entities[i].entity_cvd_report.is_hospitalized) && \
        !(hCVD19->entities[i].entity_cvd_report.is_quarantined) && \
        (temp_tests_done < hCVD19->max_testing_capacity)) {

            if(RAND_GEN(PERCENT) > MIN_PERCENT_OF_NEG_RESULTS) {
                if((RAND_GEN(PERCENT) < PERCENT_TEST_POSTIVE_HOSPITALIZED) && \
                (hCVD19->cur_filled_hospital_capacity < \
                (hCVD19->capacity_per_hospital * hCVD19->num_of_hospitals_in_city))) {
                    rand_hosp = RAND_GEN(hCVD19->num_of_hospitals_in_city);
                    hCVD19->entities[i].entity_cvd_report.is_hospitalized = 1;
                    hCVD19->entities[i].pos_data.cur_pos.x = \
                    hCVD19->hospital_locations[rand_hosp].x;
                    hCVD19->entities[i].pos_data.cur_pos.y = \
                    hCVD19->hospital_locations[rand_hosp].y;
                    hCVD19->cur_filled_hospital_capacity += 1; 
                }
    
                else
                    hCVD19->entities[i].entity_cvd_report.is_quarantined = 1;
            }
            ++temp_tests_done;
        }
    }
    return CVD19SSIM_SUCCESS;
}

CVD19SSIM_STATUS_t cvd19ssim_daily_recovery(cvd19ssim_core_t *HCVD19) {

    uint32_t temp_rcvr_cntr = 0;
    bool rcvrd = 0;

    for(uint32_t i = 0; i < HCVD19->population_data.max_allowed_population_in_city; ++i) {        
        if(HCVD19->entities[i].is_alive && \
        HCVD19->entities[i].entity_cvd_report.is_infected && \
        (HCVD19->entities[i].entity_cvd_report.days_of_infections > MIN_DAYS_TO_RECOVER) && \
        (temp_rcvr_cntr < MAX_RECOVERY_PER_DAY)) {

            if(!(HCVD19->entities[i].entity_cvd_report.is_hospitalized) && \
            !(HCVD19->entities[i].entity_cvd_report.is_quarantined)) {
                if(RAND_GEN(PERCENT) < PERCENT_CHANCE_RCVRY_FROM_NO_TREATMNT)
                    rcvrd = 1;
            }
            if(HCVD19->entities[i].entity_cvd_report.is_hospitalized) {
                if(RAND_GEN(PERCENT) < PERCENT_CHANCE_RCVRY_FROM_HOSPTZN) {
                    rcvrd = 1;
                    HCVD19->cur_filled_hospital_capacity -= 1;
                }
            }
            if(HCVD19->entities[i].entity_cvd_report.is_quarantined) {
                if(RAND_GEN(PERCENT) < PERCENT_CHANCE_RCVRY_FROM_QRNTN)
                    rcvrd = 1;
            }
            if(rcvrd) {
                init_entity_inf_cvd_report(HCVD19->entities, i, 0);
                HCVD19->entities[i].entity_cvd_report.is_recovered = 1;
                HCVD19->population_data.total_recovered += 1;
                ++temp_rcvr_cntr;
                rcvrd = 0;
            }
        }
    }
    return CVD19SSIM_SUCCESS;
}
