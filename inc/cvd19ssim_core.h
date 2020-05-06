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
    uint32_t total_other_deaths;

} cur_population_stat_t;


typedef struct _entity_health_record {
    
    uint32_t enitity_id;
    bool is_alive;
    bool is_infected;
    bool is_quarantined;
    bool is_recovered;
    cvd19ssim_entity_mvmnt_t pos_data;
    uint8_t prob_early_death;
    uint8_t prob_better_immunity;

} entity_health_record_t;


typedef struct _cvd19ssim_core {

    uint32_t                city_space;
    cur_population_stat_t   population_data;
    entity_health_record_t  *entities;
    uint32_t                num_of_hospitals_in_city;
    uint32_t                capacity_per_hospital;

};


#endif /* _CVD19SSIM_CORE_H */