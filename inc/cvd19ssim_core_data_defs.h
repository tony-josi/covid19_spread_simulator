#ifndef _CVD19SSIM_CORE_DATA_DEFS_H
#define _CVD19SSIM_CORE_DATA_DEFS_H

#define MAX_ALLOWED_POPULATION                  200

#define INIT_POPL_LOWER_LIMIT_DIFF              100

#define MAX_SPREAD_DISTANCE                     5

#define PERCENT_CHANCE_OF_CVD_INF_IN_SPRD_DIST  80

#define MAX_SPEED                               2

#define MIN_SPEED                               1

#define MAX_PROB_OF_EARLY_NORMAL_DEATH          60

#define MIN_PROB_OF_EARLY_NORMAL_DEATH          10

#define MAX_PROB_OF_BETTER_IMMUNITY             70

#define MIN_PROB_OF_BETTER_IMMUNITY             30

#define MIN_INITIALLY_INFECTED                  10

#define PERCENT_OF_AFFECTED_WITH_SYMPTOMS       60

#define DEFAULT_SLEEP_TIME                      0

#define STILL_FRAMES_AT_START                   10

#define PERCENT_OF_HIGH_SPEED                   10

#define HIGH_SPEED_POSSIBLE                     10

#define PERCENT                                 100

#define PERCENT_CHANCE_BIRTHS_OCCUR             5

#define PERCENT_CHANCE_DEATHS_OCCUR             5

#define INVERSE_DEATH_CONSTANT                  20

#define NORMAL_DEATH_THRESHOLD                  ((MIN_PROB_OF_BETTER_IMMUNITY + ((MAX_PROB_OF_BETTER_IMMUNITY - MIN_PROB_OF_BETTER_IMMUNITY) / 2)) - \
                                                (MIN_PROB_OF_EARLY_NORMAL_DEATH + ((MAX_PROB_OF_EARLY_NORMAL_DEATH - MIN_PROB_OF_EARLY_NORMAL_DEATH) / 2)) - \
                                                INVERSE_DEATH_CONSTANT)

#endif /* _CVD19SSIM_CORE_DATA_DEFS_H */
