#ifndef _CVD19SSIM_PPM
#define _CVD19SSIM_PPM

#include "cvd19ssim_core.h"

#define MAX_CITY_DEFAULT_SIZE           384

#define SQUARE_FRAME_SIZE               14

#define PIXEL_SIZE                      4

#define PPM_SIZE                        ((MAX_CITY_DEFAULT_SIZE * PIXEL_SIZE) + (2 * SQUARE_FRAME_SIZE))

#define CHECK_RANGE(N)                  (bool)(((N >= (SQUARE_FRAME_SIZE)) && (N < (MAX_CITY_DEFAULT_SIZE - SQUARE_FRAME_SIZE))) ? 1 : 0)

void output_current_frame_ppm(cvd19ssim_core_t *);

#endif /* _CVD19SSIM_PPM */
