#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/cvd19ssim_ppm.h"

static long colors[] = {0xFF0000, 0x00FF00, 0xFFFFFF};
static unsigned char ppm_buf[3L * PPM_SIZE * PPM_SIZE];

static void buf_clear(void);
static void buf_set(int , int , long);
static void buf_set_pixel(int , int , long);
static void buf_write(void);

void output_current_frame_ppm(cvd19ssim_core_t *HCVD19) {

    buf_clear();

    for(uint32_t i = 0; i < HCVD19->population_data.cur_population; ++i) {
        if(HCVD19->entities[i].is_alive) {

            if(HCVD19->entities[i].entity_cvd_report.is_infected)
                buf_set_pixel(HCVD19->entities[i].pos_data.cur_pos.y * PIXEL_SIZE, \
                HCVD19->entities[i].pos_data.cur_pos.x * PIXEL_SIZE, colors[0]);

            else if(HCVD19->entities[i].entity_cvd_report.is_recovered)
                buf_set_pixel(HCVD19->entities[i].pos_data.cur_pos.y * PIXEL_SIZE, \
                HCVD19->entities[i].pos_data.cur_pos.x * PIXEL_SIZE, colors[1]);

            else
                buf_set_pixel(HCVD19->entities[i].pos_data.cur_pos.y * PIXEL_SIZE, \
                HCVD19->entities[i].pos_data.cur_pos.x * PIXEL_SIZE, colors[2]);

        }
    }

    buf_write();
}


void buf_clear(void)
{
    memset(ppm_buf, 0, sizeof(ppm_buf));
}

void buf_set(int x, int y, long color)
{
    if (x >= 0 && x < PPM_SIZE && y >= 0 && y < PPM_SIZE) {
        ppm_buf[y * 3L * PPM_SIZE + x * 3L + 0] = color >> 16;
        ppm_buf[y * 3L * PPM_SIZE + x * 3L + 1] = color >>  8;
        ppm_buf[y * 3L * PPM_SIZE + x * 3L + 2] = color >>  0;
    }
}

void buf_set_pixel(int x, int y, long color) {

    for(int m = -(PIXEL_SIZE); m < PIXEL_SIZE; m++)
        for(int n = -(PIXEL_SIZE); n < PIXEL_SIZE; n++)
            buf_set(x + m, y + n, color);

}

void buf_write(void) {
    printf("P6\n%d %d\n255\n", PPM_SIZE, PPM_SIZE);
    fwrite(ppm_buf, sizeof(ppm_buf), 1, stdout);
}