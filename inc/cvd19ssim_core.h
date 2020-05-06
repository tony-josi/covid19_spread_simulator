#ifndef _CVD19SSIM_CORE_H
#define _CVD19SSIM_CORE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct _cur_population_stat {

    uint32_t max_allowed_population_in_city;
    uint32_t cur_population;
    uint32_t total_infected;
    uint32_t total_recovered;
    uint32_t total_infected_n_died;
    uint32_t total_other_deaths;

} cur_population_stat_t;


typedef struct _entity_health_record
{

    uint32_t enitity_id;
    bool is_alive;
    bool is_infected;
    bool is_recovered;


} entity_health_record_t;



typedef struct _cvd19ssim_core {

    uint32_t                city_space;
    cur_population_stat_t   population_data;


};


#endif /* _CVD19SSIM_CORE_H */