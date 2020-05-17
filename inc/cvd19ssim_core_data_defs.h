#ifndef _CVD19SSIM_CORE_DATA_DEFS_H
#define _CVD19SSIM_CORE_DATA_DEFS_H

#define MAX_ALLOWED_POPULATION                  400

#define INIT_POPL_LOWER_LIMIT_DIFF              300

#define ENABLE_LOGGING                          1

#define DEBUG_MAX_DAYS                          300

#define MAX_NUM_OF_LOOPS_TO_LOG                 300

#define LOG_FILE_LINE_BUFF_SIZE                 150

#define LOG_FILE_PATH                           "cvd19.log"

#define MAX_SPREAD_DISTANCE                     10

#define PERCENT_CHANCE_OF_CVD_INF_IN_SPRD_DIST  60

#define MAX_SPEED                               2

#define MIN_SPEED                               1

#define CVD_DEATH_FACTOR                        20

#define MAX_PROB_OF_EARLY_NORMAL_DEATH          60

#define MIN_PROB_OF_EARLY_NORMAL_DEATH          10

#define MAX_PROB_OF_BETTER_IMMUNITY             70

#define MIN_PROB_OF_BETTER_IMMUNITY             30

#define MIN_INITIALLY_INFECTED                  10

#define PERCENT_OF_AFFECTED_WITH_SYMPTOMS       60

#define DEFAULT_SLEEP_TIME                      10

#define STILL_FRAMES_AT_START                   10

#define PERCENT_OF_HIGH_SPEED                   10

#define HIGH_SPEED_POSSIBLE                     10

#define PERCENT                                 100

#define PERCENT_CHANCE_BIRTHS_OCCUR             5

#define PERCENT_CHANCE_DEATHS_OCCUR             5

#define INVERSE_DEATH_CONSTANT                  20

#define INF_MIN_DEATH_DAYS                      21

#define INF_MAX_DEATH_DAYS                      56

#define MIN_DAYS_TO_RECOVER                     28

#define MAX_RECOVERY_PER_DAY                    5

#define PERCENT_CHANCE_RCVRY_FROM_NO_TREATMNT   30

#define PERCENT_CHANCE_RCVRY_FROM_QRNTN         45

#define PERCENT_CHANCE_RCVRY_FROM_HOSPTZN       70

#define MAX_TESTING_CAP                         1

#define MIN_PERCENT_OF_NEG_RESULTS              60

#define PERCENT_TEST_POSTIVE_HOSPITALIZED       80

#define HOSPITAL_RADIUS                         3

#define NORMAL_DEATH_THRESHOLD                  ((MIN_PROB_OF_BETTER_IMMUNITY + ((MAX_PROB_OF_BETTER_IMMUNITY - MIN_PROB_OF_BETTER_IMMUNITY) / 2)) - \
                                                (MIN_PROB_OF_EARLY_NORMAL_DEATH + ((MAX_PROB_OF_EARLY_NORMAL_DEATH - MIN_PROB_OF_EARLY_NORMAL_DEATH) / 2)) - \
                                                INVERSE_DEATH_CONSTANT)

#endif /* _CVD19SSIM_CORE_DATA_DEFS_H */
