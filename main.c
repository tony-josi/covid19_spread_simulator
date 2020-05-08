#include <stdio.h>
#include "inc/cvd19ssim_core.h"

int main() {
    if(cvd19ssim_RUNNER_MAIN() == CVD19SSIM_SUCCESS) {
        printf("SUCCESS\n");
        return EXIT_SUCCESS;
    }

    printf("FAIL\n");

    return EXIT_FAILURE;
}
