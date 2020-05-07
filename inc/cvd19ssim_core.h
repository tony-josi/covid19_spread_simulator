#ifndef _CVD19SSIM_CORE_H
#define _CVD19SSIM_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include "cvd19ssim_entity_mvmnt.h"

typedef struct _cur_population_stat {

    uint32_t max_allowed_population_in_city;
    uint32_t cur_population;
    uint32_t total_infected;
    uint32_t total_recovered;
    uint32_t total_infected_n_died;

} cur_population_stat_t;

typedef struct _cvd19ssim_core_covid_entity_report {

    bool is_infected;
    bool is_quarantined;
    bool is_recovered;
    bool is_hospitalized;
    bool have_symptoms;
    bool is_tested;
    bool days_of_infections;

} cvd19ssim_core_covid_entity_report_t;


typedef struct _entity_health_record {

    cvd19ssim_entity_mvmnt_t                pos_data;
    cvd19ssim_core_covid_entity_report_t    entity_cvd_report;
    bool                                    is_alive;
    uint8_t                                 prob_early_death;
    uint8_t                                 prob_better_immunity;

} entity_health_record_t;


typedef struct _cvd19ssim_core {

    uint32_t                city_space;
    cur_population_stat_t   population_data;
    entity_health_record_t  *entities;
    uint64_t                master_entity_counter;
    uint32_t                num_of_hospitals_in_city;
    uint32_t                capacity_per_hospital;
    uint32_t                cur_filled_hospital_capacity;
    uint8_t                 avg_death_rate;
    uint8_t                 avg_birth_rate;

} cvd19ssim_core_t;


#endif /* _CVD19SSIM_CORE_H */