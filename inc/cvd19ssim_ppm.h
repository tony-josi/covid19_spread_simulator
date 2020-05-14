#ifndef _CVD19SSIM_PPM
#define _CVD19SSIM_PPM

#include "cvd19ssim_core.h"

#define MAX_CITY_DEFAULT_SIZE           262

#define PIXEL_SIZE                      4

#define SQUARE_FRAME_SZ                 10

#define PPM_SIZE                        ((MAX_CITY_DEFAULT_SIZE + SQUARE_FRAME_SZ) * PIXEL_SIZE)

#define CHECK_RANGE(N)                  (bool)(((N >= (PIXEL_SIZE + SQUARE_FRAME_SZ)) && (N < (MAX_CITY_DEFAULT_SIZE - (PIXEL_SIZE + SQUARE_FRAME_SZ)))) ? 1 : 0)

void output_current_frame_ppm(cvd19ssim_core_t *);

#endif /* _CVD19SSIM_PPM */
