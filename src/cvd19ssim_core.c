#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_util.h"
#include "../inc/cvd19ssim_entity_mvmnt.h"

CVD19SSIM_STATUS_t cvd19ssim_RUNNER_MAIN() {
    
    srand(time(0)); 
    cvd19ssim_core_t hCVD19;
    uint64_t loop_cntr = 0;
    FILE *log_fptr;
    bool is_log_closed = 0;

    if(cvd19ssim_core_t_init(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;

    if(cvd19ssim_core_t_init_entities(&hCVD19) != CVD19SSIM_SUCCESS)
        return CVD19SSIM_INIT_FAIL;
        
#if ENABLE_LOGGING
    if((log_fptr = init_log_file(LOG_FILE_PATH)) == NULL)
        return CVD19SSIM_INIT_FAIL;
#endif /* ENABLE_LOGGING */

    UNUSED(print_cvd19ssim_core_t);
    UNUSED(print_cvd19ssim_entity_health_record_t);
    UNUSED(loop_cntr);
    UNUSED(is_log_closed);
    UNUSED(log_fptr);

    for(int i = 0; i < STILL_FRAMES_AT_START; i++) {
        sleep_ms();
        output_current_frame_ppm(&hCVD19);
    }
    
    while ((loop_cntr++ )< DEBUG_MAX_DAYS) {

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
        cvd19ssim_daily_summary_calc(&hCVD19);
        cvd19ssim_normal_deaths(&hCVD19);
        cvd19ssim_normal_births(&hCVD19);
        cvd19ssim_covid_deaths(&hCVD19);
        
        if(pos_move(&hCVD19))
            return CVD19SSIM_FAIL;
        
        cvd19ssim_covid_infections(&hCVD19);
        cvd19ssim_daily_diagnosis(&hCVD19);
        cvd19ssim_daily_recovery(&hCVD19);
        
        output_current_frame_ppm(&hCVD19);

    }

/*     uint32_t still_inf = 0;
    for(uint32_t k = 0; k  < hCVD19.population_data.max_allowed_population_in_city; ++k) {
        if(hCVD19.entities[k].entity_cvd_report.is_infected)
            still_inf++;
    }
    printf("STILL_INF: %d\n", still_inf); */
    
/*     uint32_t temp_loop = 0;
    while (temp_loop < 1000) {
        sleep_ms();
        //printf("Death\n");
        cvd19ssim_normal_deaths(&hCVD19);
        //printf("Birth\n");
        cvd19ssim_normal_births(&hCVD19);
        //printf("Inf\n");
        pos_move(&hCVD19);
        cvd19ssim_covid_infections(&hCVD19);
        cvd19ssim_daily_summary_calc(&hCVD19);
        cvd19ssim_log_per_day_report(&hCVD19, log_fptr);
        printf("___________________\n");
        temp_loop++;
    } */
    
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
/*         HCVD19->hospital_locations[i].x = \
        SQUARE_FRAME_SIZE + RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5));
        HCVD19->hospital_locations[i].y = \
        SQUARE_FRAME_SIZE + RAND_GEN((MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE - 5)); */
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

CVD19SSIM_STATUS_t cvd19ssim_normal_deaths(cvd19ssim_core_t *HCVD19) {
    uint32_t deaths_today = 0;
    //printf("DTH: %d\n", (NORMAL_DEATH_THRESHOLD));
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
                    //printf("CAN: %d     %d      %d\n", i, 
                    //(HCVD19->entities[i].prob_better_immunity - HCVD19->entities[i].prob_early_death), 
                    //MAG((NORMAL_DEATH_THRESHOLD)));
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
                    //printf("Birth i: %d\n", i);
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
            
            //HCVD19->entities[i].entity_cvd_report.days_of_infections += 1;
            
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
