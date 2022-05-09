# parallelized-Sorting-
After applying our code on 100k number file .c we find the effect of parallelization(Open MP) on saving time 
Serial	      36.445003 Sec
4 threads	    1.89 Sec
8 threads	    0.65 Sec
12 threads 	  0.53 Sec
24 threads	  0.496347 Sec

we see the effect of using openmp and paralleling our code very clear in this code as the serial took elapsed wall time equal to 36.5 seconds while using 4 threads make it 1.98 seconds which much better.
we also see that increasing  the threads makes only slightly difference as using 8,12 and 24 threads 
