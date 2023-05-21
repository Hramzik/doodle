

set terminal svg enhanced mousing size 1024,768
set output "work/func_test.svg"

set grid xtics ytics

set xlabel 'chain number'
set ylabel 'chain len'
set title "test results"

set boxwidth 0.1


plot\
    "work/func_test_results/size 499/2.txt" \
    using ($1+0.0):2 smooth freq with boxes fs solid 0.5 title "first char", \
    "work/func_test_results/size 499/3.txt" \
    using ($1+0.1):2 smooth freq with boxes fs solid 0.5 title "strlen",\
    "work/func_test_results/size 499/4.txt" \
    using ($1+0.2):2 smooth freq with boxes fs solid 0.5 title "sum char",\
    "work/func_test_results/size 499/5.txt" \
    using ($1-0.1):2 smooth freq with boxes fs solid 0.5 title "rorxor",\
    "work/func_test_results/size 499/6.txt" \
    using ($1-0.2):2 smooth freq with boxes fs solid 0.5 title "rolxor",\
    "work/func_test_results/size 499/7.txt" \
    using ($1+0.3):2 smooth freq with boxes fs solid 0.5 title "crc32"