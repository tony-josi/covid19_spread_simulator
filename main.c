#include "inc/cvd19ssim_core.h"

int main() {
    if(cvd19ssim_RUNNER_MAIN() == CVD19SSIM_SUCCESS)
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}
