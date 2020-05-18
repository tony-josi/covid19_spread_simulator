#ifndef _CVD19SSIM_CORE_DATA_DEFS_H
#define _CVD19SSIM_CORE_DATA_DEFS_H

#include "cvdssim_core_private_defs.h"

#define MAX_ALLOWED_POPULATION                  500

#define INIT_POPL_LOWER_LIMIT_DIFF              400

#define NUM_OF_HOSPITALS                        3

#define CAPACITY_PER_HOSPITAL                   10

#define ENABLE_LOGGING                          1

#define DEBUG_MAX_DAYS                          250

#define MAX_NUM_OF_LOOPS_TO_LOG                 250

#define MAX_SPEED                               2

#define MIN_SPEED                               1

#define MIN_INITIALLY_INFECTED                  10

#define PERCENT_OF_AFFECTED_WITH_SYMPTOMS       60

#define DEFAULT_SLEEP_TIME                      10

#define PERCENT_OF_HIGH_SPEED                   10

#define HIGH_SPEED_POSSIBLE                     10

#define INF_MIN_DEATH_DAYS                      21

#define INF_MAX_DEATH_DAYS                      56

#define MIN_DAYS_TO_RECOVER                     28

#define MAX_RECOVERY_PER_DAY                    5

#define PERCENT_CHANCE_RCVRY_FROM_NO_TREATMNT   30

#define PERCENT_CHANCE_RCVRY_FROM_QRNTN         45

#define PERCENT_CHANCE_RCVRY_FROM_HOSPTZN       70

#define MAX_TESTING_CAP                         2

#define MIN_PERCENT_OF_NEG_RESULTS              40

#define PERCENT_TEST_POSTIVE_HOSPITALIZED       80

#define HOSPITAL_RADIUS                         3

#define NORMAL_DEATH_THRESHOLD                  ((MIN_PROB_OF_BETTER_IMMUNITY + ((MAX_PROB_OF_BETTER_IMMUNITY - MIN_PROB_OF_BETTER_IMMUNITY) / 2)) - \
                                                (MIN_PROB_OF_EARLY_NORMAL_DEATH + ((MAX_PROB_OF_EARLY_NORMAL_DEATH - MIN_PROB_OF_EARLY_NORMAL_DEATH) / 2)) - \
                                                INVERSE_DEATH_CONSTANT)

#endif /* _CVD19SSIM_CORE_DATA_DEFS_H */
