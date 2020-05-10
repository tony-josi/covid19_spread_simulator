#ifndef _CVD19SSIM_PPM
#define _CVD19SSIM_PPM

#define MAX_CITY_DEFAULT_SIZE          108

#define PIXEL_SIZE                      10

#define PPM_SIZE                        (MAX_CITY_DEFAULT_SIZE * PIXEL_SIZE)

#define CHECK_RANGE(N)                  (bool)(((N >= 0) & (N < MAX_CITY_DEFAULT_SIZE)) ? 1 : 0)

#endif /* _CVD19SSIM_PPM */
