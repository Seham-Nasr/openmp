# openmp programming 
Merge sort algorithm using Multithreading in two cases (2 threads and 4 threads) number of threads can be dynamically added in
the execution command line. clock_gettim() function is used for measuring time.

how you can run the code?
1- compiling using command line as follow:
    $gcc -o mp -fopenmp mergeomp.c
2- run the code as follow:
    case 1 (2 threads):
      $./mp 2
    case 2 (4 threads):
      $./mp 4
      
note: the command lines which used for compiling and running are illustrated  in screenshot folder.
