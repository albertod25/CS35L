REFLECTION:
Overall, the implementation of multithreading for this application was
relatively easy. I believe this was possible because I took the time before 
even looking at the main.c source code, to practice with the pthread library to
see how exactly I could go about breaking the code. I realize that I would need
to write a for loop to create all the threads, another for loop to wait for all
the threads to join, and finally create a function that each thread would go
and execute. I realize that the section where the original programmer wrote
/* For each pixel */ would be a prime candidate for multithreading.

I also ran into the issue of having some variables that my new function needed 
to access being out of scope. For now, I decided to make these variables
global. Although a simple solution, this caused a considerable amount of pain
on my part because I forgot to delete some lines in the main() function where I
re-defined those same variables but in a smaller scope.

Another problem I ran into was not noticing how algorithm I broke into threads
would print out some data points about the pixels it just processed. I realized
there was no guarantee if the threads would print out these data points in the
correct order, thus breaking the check performed by the $make clean check
command. Once again, I decided to create a global 3D array of floating point
numbers to keep track of these data points. Then, instead of printing out the
data points in the threaded algorithm itself, it would print out the data in
the main() function right after joining all the threads.

RESULTS:
1 thread
real    0m47.573s
user    0m47.561s
sys     0m0.001s

2 threads
real    0m23.936s
user    0m47.603s
sys     0m0.004s

4 threads
real    0m12.232s
user    0m48.217s
sys     0m0.005s

8 threads
real    0m6.463s
user    0m50.159s
sys     0m0.005s

No errors were thrown when comparing these images with baseline image.
(Exact output of ($ make clean check) available in make-log.txt)

CONCLUSION:
Multithreading for this application was a great success. With more threads we
were able to nearly halve the real time for each jump. More precisely, with 2^n
threads available, we can approximately reduce the real time by a factor of
(1/2)^n. While real time gets better however, we also see that sys time
increases as we add more threads. The rate at which it grows seems a little
confusing for now, but with a few more experiments we should be able to find
the point of diminishing returns.

It was also meantioned in the assignment specs that the SEASnet Linux Server 
that we ran this on is a multicore machine. It would be interesting to see how
the results differ on my own machine and if the points of diminishing returns
are the same.
