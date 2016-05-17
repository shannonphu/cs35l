The general way I wrote my program was by making a
struct to hold my parameters in that I wanted to pass
into the function my threads were executing. I made a
struct that would hold the start and end boundary of
which part of the image I wanted that thread to process.
After creating the threads based on how many the user
wanted, I joined them and made the last thread created
have a callback function to print out the result
of all the processed pixels which were stored into a
2-D array of rgb values (part of another struct I made).

Some issues I ran into were actually when nthreads was
set to 1 or 2. Surprisingly my program works for more
threads (except 19). I got 1 thread to work, but 2 threads
still does not give the correct processed image. 19
threads also does not give the correct image. But other
numbers of threads should work when I tested it on
lnxsrv02. Another issue I ran into was for some reason
In the function where I print out the resulting rgb
values for each pixel, before the function returns I
must print to stderr a line with the value of some local
variables or else my program will always encounter a
segmentation fault. But I fixed this because I realized
my function was a void * function and did not return
anything so I just added a return NULL and this
problem was resolved.

The speedup was obvious though after timing and comparing
when 1, 2, 4, and 8 threads were made. If more threads
like up to 18 where created then the speed up was even
greater.
