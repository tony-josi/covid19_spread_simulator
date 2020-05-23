/*
 * Copyright (C)    Tony Josi
 * Date             19-05-2020
 */

#ifndef _CVD19SSIM_CORE_UTIL_H
#define _CVD19SSIM_CORE_UTIL_H

#include "cvd19ssim_core.h"

CVD19SSIM_STATUS_t cvd19ssim_struct_init(cvd19ssim_core_t *);
CVD19SSIM_STATUS_t cvd19ssim_daily_summary_calc(cvd19ssim_core_t *);
CVD19SSIM_STATUS_t cvd19ssim_core_t_hosp_deinit(cvd19ssim_core_t *);
CVD19SSIM_STATUS_t cvd19ssim_core_t_entity_deinit(cvd19ssim_core_t *);
CVD19SSIM_STATUS_t cvd19ssim_log_per_day_report(cvd19ssim_core_t *, FILE *);

#endif /* _CVD19SSIM_CORE_UTIL_H */
