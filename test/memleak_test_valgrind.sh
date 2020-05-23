valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind_test_report.txt \
         ./cvd19ssim > out.txt
         