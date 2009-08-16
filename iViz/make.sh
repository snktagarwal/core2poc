gcc -g -c core_info.c -o core_info.o
gcc -g -c test.c -o test.o
gcc -g -c create_script.c -o create_script.o
gcc -g -c bst_score_sheet.c -o bst_score_sheet.o
gcc -g -c score.c -o score.o
gcc -g -c ga.c -o ga.o
gcc -g core_info.o ga.o create_script.o bst_score_sheet.o  score.o test.o -o output -lm
