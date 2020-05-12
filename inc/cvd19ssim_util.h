#ifndef _CVD19SSIM_UTIL
#define _CVD19SSIM_UTIL

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/cvd19ssim_core.h"
#include "../inc/cvd19ssim_core_data_defs.h"
#include "../inc/cvd19ssim_ppm.h"
#include "../inc/cvd19ssim_util.h"

void sleep_ms();
void print_cvd19ssim_core_t(cvd19ssim_core_t *);
void print_cvd19ssim_entity_health_record_t(cvd19ssim_core_t *, uint32_t);
void init_entity(entity_health_record_t *, uint32_t, bool);

#endif /* _CVD19SSIM_UTIL */
