#ifndef _CVD19SSIM_CORE_H
#define _CVD19SSIM_CORE_H

#include "stdint.h"

typedef struct _cur_population_stat {

    uint32_t total_population;
    uint32_t total_infected;
    uint32_t total_recovered;
    uint32_t infected_n_died;
    uint32_t other_deaths;

} cur_population_stat_t;


typedef struct _cvd19ssim_core {

    uint32_t                living_space;
    cur_population_stat_t   population_data;


};


#endif /* _CVD19SSIM_CORE_H */