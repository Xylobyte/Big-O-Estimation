# Blackbox Project

### CSE/IT 122

### Algorithms & Data Structures

In this project, you will be given ablack boxof seven functions. You are to find their runtime
complexity by testing each function with a variety of input sizes.

After gathering the necessary data from each function in the blackbox, you will plot the points
using gnuplot and then determine the complexity for each mystery algorithm.

It is advisable to begin testing your algorithms using very small input sizes – remember that
n!algorithms can increase runtime to over a minute on a standard machine withn≥ 13 – and
increase from there.

**Make sure to read the "Steps of this Project" and the submission guidelines at the end of this
document! If you have any questions about anything, including the math and math notation,
please see the instructor or a TA/tutor.**

## 1 Math and Notation

A set is a collection of "things." For example, **Z** is the set of integers; it can be written as
**Z** ={... ,−3,−2,−1, 0, 1, 2, 3,.. .}.

**R** is the set of real numbers and **Z** +is the set of positive integers. Any set of positive numbers does
not include 0; thus **Z** +={1, 2, 3, 4,.. .}. The "∈" symbol meansis an element of; for example, 5 ∈ **Z**
(read:5 is an element of the integersor5 is an integer)

Thus,d∈ **R** ≥^0 means thatdis a real number greater or equal to 0.

## 2 Big O Notation and Time Complexity

Big O Notation is used to describe the limiting behavior of a functionf(n), typically asngrows to in-
finity, in terms of elementary functions. If we find a simple function,g, that accurately approximates
ffor largen, we write:f(n) =O(g(n)). The formal criteria for this relationship is:

```
nlim→∞
```
```
f(n)
g(n)
=c∈ R ≥^0 (1)
```

```
That is, asngrows larger and larger,gf((nn))begins to converge toward some (non-negative) real
number. Essentially, iff(n)does not grow so that the above fraction diverges to infinity, we
considerf(n) =O(g(n)). Consider the following function:
```
```
f(n) = 3 n^2 − 10 n+ 51 (2)
```
We claim thatf(n) =O(n^2 ), which we demonstrate with the following table:

```
n f(n) n^3 n^2 n
10 251 1000 100 10
100 29051 1000000 10000 100
1000 2990051 1000000000 1000000 1000
10000 299900051 1000000000000 1000000000 10000
```
```
Noticen^2 remains on approximately the same order asf(n), which suggests thatf(n) =O(n^2 ).
```
```
n f(n)/n^3 f(n)/n^2 f(n)/n
10 0.251 2.51 25.
100 0.029051 2.9051 290.
1000 0.002990051 2.990051 2990.
10000 0.000299900051 2.99900051 29990.
```
Because bothf(nn 3 )andfn(n 2 )eventually converge, we can say thatf(n) =O(n^3 )andf(n) =O(n^2 ).
We also could writef(n) =O(n^4 ),f(n) =O(n!), or any other functiong(n)which grows faster
thann^2. However, for the purpose of this project, we identify theslowest-growingg(n)such that
f(n) =O(g(n)); in this instance, we chooseg(n) =n^2.

```
An alternative criteria we can meet to definef(n) =O(g(n))is by choosingwitnesses,c∈ R +and
k 0 ∈ Z +, such thatf(n)<c·g(n)for alln≥k 0. For example, we can choosek 0 =6 andc=3 to
demonstratef(n) =O(n^2 ), because 3 n^2 > 3 n^2 − 10 n+ 51 , for alln≥6. This criteria, while slightly
less rigorous than the limit definition, allows us to classify functions without calculus.
```
```
In computer science, we use Big O notation to classify algorithms by how they respond to changes
in input size: a function which isf 1 (n) =O(log(n))will run much faster thanf 2 (n) =O(n^2 )for
the same value ofn.
```
```
Consider a machine that can perform 109 operations per second. Then for the same input,n= 1000 ,
the time various algorithms would take to execute is:
```
```
Algorithm Run Time (n=1000)
O(log(n)) 6.9 nanoseconds
O(n) 1.0 microseconds
O(nlog(n)) 6.9 microseconds
O(n^2 ) 1 millisecond
O(n^5 ) 12 days
O( 2 n) 2.5· 10274 universe age
O(n!) 9.3· 102540 universe age
```

## 3 Creating Random Test Data

```
In this project, you need to generate a variety of lists in three basic orders: sorted, reverse-sorted,
and shuffled.
```
```
As a review, the first two methods are relatively simple:
```
1 /* generate a sorted list */
2 unsigned long i;
3 unsigned long *list = malloc(list_size * sizeof(unsigned long));
4
5 for(i = 0; i < list_size; i++){
6 *(list+i) = i;
7 }

```
Note thatlist_sizemay be any pre-defined constant up to18, 446, 744, 073, 709, 551, 615( 264 − 1 ),
the maximum value for anunsigned longinteger. (Note:list_sizeis still a variable! You can make
it a#defineconstant, but do you really want to re-compile every time you are running your script?)
```
```
Quickly generating a pseudo-random list, with no repeat elements, is slightly more difficult. What
is often done in situations like this is to first generate a sorted list, and then shuffle the list; the
whole process is completed inO(n)time. For example, using C’srand()pseudo-random number
generator, you shuffle like this:
```
1 /* *list is a sorted list, of size list_size */
2 srandom(time(NULL));
3
4 /* step back from the end of the list */
5 for(i= list_size - 1; i > 0; i--){
6 /* pick a random element between 0 and i to swap */
7 j = random() % (i+1);
8 swap(a+1, a+j);
9 }

```
However, you will encounter a problem when you begin to use large values forlist_size. The
rand()function generates a value between 0 andRAND_MAX, which is usually 32767 ( 215 − 1 )on a
32-bit machine or 2147483647 ( 231 − 1 )on a 64-bit machine; iflist_size>RAND_MAX, you are no
longer truly shuffling the list. Instead you have to come up with an alternative way to generate a
random number which is potentially as large as 2^64 −1.
```

1 /* random_number: generates a pseudo-random
2 long unsigned between 0 and 2^64 - 1
3 seed random() with srandom(time(NULL)) before you call this */
4 unsigned long random_number(void){
5
6 unsigned long n, p, r;
7 int i;
8
9 n = 0;
10 for(i = 0; p = 1; i < 8; i++, p *= 256){
11
12 /* we have p = 256^i */
13 /* random value between 0 and 255 */
14 r = random() % 256;
15
16 /* add this pseudo-random byte to n */
17 n += r * p;
18
19 }/* repeat 8 times, so we have 64 pseudo-random bits */
20
21 return n;
22 }

```
Usingrandom_number()allows your originalO(n)shuffling algorithm to run without a hitch,
which enables you the capacity to generate massive pseudo-random lists.
```
## 4 Timing in C

```
In this project, you will analyze a number of mystery algorithms to determine their order of
complexity. Naturally, this process necessitates some way for you to assess the runtime of various
functions depending on their input size, preferably with higher accuracy than your kitchen timer.
To get around this, you will utilize a number of functions withtime.hto help us take a decent
guess as to how long a given process took to run.
```
```
time.hcontains several useful data types when it comes to dealing with your machine’s internal
clock. In this project, you will use theclock_ttype to keep track of the amount of CPU ticks which
elapse during a function’s runtime.
```
```
Consider the following:
```

1 #include <stdio.h>
2 #include <time.h>
3
4 int main(void){
5
6 unsigned long list_size = 18446744073709551615;
7 int msec;
8 clock_t time_elapsed;
9 unsigned long *list = shuffle_list(list_size);
10
11 time_elapsed = clock();
12
13 /*test something here; e.g. */
14 /* function_3(list, list_size); */
15
16 time_elapsed = clock() - time_elapsed;
17 msec = time_elapsed * 1000 / CLOCKS_PER_SEC;
18
19 printf("Time taken: %d.%03d seconds\n", msec/1000, msec%1000);
20 printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);
21
22 return 0;
23
24 }

```
The preceding code offers you two ways to monitor the time which passes while you test an
algorithm, by milliseconds or by CPU ticks. Timing to the millisecond offers you a degree of
accuracy sufficient to test most algorithms provided in this exercise, but some which run particularly
quickly, even for largen, may require measurement on the ticks-scale. Notice that you only time
the mystery algorithm – shuffling occurs before you begin timing.
```

## 5 Interfacing with Blackbox

```
As a part of this project, you are provided with two files –blackbox.h, andblackbox.ocompiled
on 64-bit Linux – which are available on Canvas (blackbox.tar.gz) and have been prepared for
you to perform analysis on.blackbox.hcontains the prototypes of the seven functions you will be
working with, so naturally you will need to#includeit inside yourmain. You can use aMakefile
to easily compile your code, as follows:
```
```
CC = gcc
CFLAGS = -g -Wall
```
```
all: main.o blackbox.o
$(CC) $(CFLAGS) -o main main.o blackbox.o
```
```
main.o: main.c
$(CC) $(CFLAGS) -c -o main.o main.c
```
```
clean:
rm *.o
```
```
When you have compiled your code this way, you will be able to debug yourowncode, but you
will not be able to step within any of the functions contained withinblackbox.o. The only way you
can interface with these functions is to invoke them, and structure your timing data about these
function calls. The argument of these functions is anunsigned longinteger,n, which specifies the
input size for the algorithm hidden within.
```
1 #include <time.h>
2 #include <stdio.h>
3 #include <stdlib.h>
4
5 /* IMPORTANT: n is the size of the list for function_3 and function_6 */
6
7 void function_1(unsigned long n);
8 void function_2(unsigned long n);
9 void function_3(unsigned long *list, unsigned long n);
10 void function_4(unsigned long n);
11 void function_5(unsigned long n);
12 void function_6(unsigned long *list, unsigned long n);
13 void function_7(unsigned long n);

```
Notice that two of the functions withinblackbox.hrequire you to provide a*list, of sizen, which
allows you to provide sorted, reverse sorted and shuffled lists to the given algorithm. This gives
you the opportunity to examine these different algorithms for best case, worst case and average
case time complexity. Also note that these algorithms will not take care of freeing your lists for you;
because you will allocate them dynamically, you will need to manage your memory accordingly.
```
```
In this project, you will test a given sample size roughly three times – you will notice that the
amount of CPU ticks (or seconds, if you prefer) which go by will change slightly between trials.
```

```
Your machine is not the most accurate method of timing available, but it will do for the purposes of
this assignment. You will also test as few as five different values ofnfor each function (you may
always test additional sizes ofnif it will help you determine complexity). You should test each
value ofnat least three times to get an average runtime for that value ofn. For the functions that
take in a list, you should time and analyze sorted, reverse-sorted, and shuffled lists separately. This
means that you should use five different values ofn, and three trials pernvalue for each type of
list.
```
## 6 Using gnuplot to Visualize Data

```
After you have collected sufficient timing data, you can use the program gnuplot to graphically
determine the complexity order of the algorithms. Despite its name, gnuplot is not distributed under
the GNU general public license; it is, however, available for free athttp://www.gnuplot.info/.
You invoke gnuplot using the commandgnuplot:
```
1 $ gnuplot
2 G N U P L O T
3 Version 5.2 patchlevel 2 last modified 2017-11-
4
5 Copyright (c) 1986-1993, 1998, 2004, 2007-
6 Thomas Williams, Colin Kelley and many others
7
8 gnuplot home: [http://www.gnuplot.info](http://www.gnuplot.info)
9 faq, bugs, etc: type "help FAQ"
10 immediate help: type "help" (plot window: hit'h')
11
12 Terminal type set to'qt'
13 gnuplot>

```
You now have a gnuplot terminal. To quit gnuplot typequit. Gnuplot offers many helpful features,
such as plotting sets of points by parsing through external files. In order to visualize your data,
specify a*.txtfile containing your runtime information as such:
```
```
1 gnuplot> plot'plot.txt' using 1:
```
```
This directs gnuplot to graph the points contained inplot.txt, using column 1 as thex-axis
(independent) data and column 2 as they-axis(dependent) data. The fileplot.txtis available on
Canvas. The format of the file is space separated data.
```
```
Notice that the plot’s default data is’plot.txt’; gnuplot has controls to make the graph more
informative. To find even more sophisticated means of modifying the baseline plot, see the manuals
available athttp://www.gnuplot.info/help.html.
```
```
This plot resembles a quadratic plot – you can verify this using gnuplot’s fitting function. Recall
that, by our non-calculus definition off(n) =O(g(n)), our goal is (loosely) to find a witnesscsuch
thatf(n)≤c·g(n)for largen. Because of this, you will use gnuplot to determine a decent value
```

```
forcand superimpose the resulting curve on your graph. Defineg(x)as:
```
```
1 gnuplot> g(x) = c * x**
```
```
Where the ** binary operator denotes exponentiation. Gnuplot also contains standard functions
such aslog(), which are useful in considering algorithms which areO(log(n))orO(nlog(n)). You
can manipulate the functiong(x)in a number of ways using gnuplot. One way is to use the fit
command:
```
1 gnuplot> fit g(x)'plot.txt' using 1:2 via c
2 iter chisq delta/lim lambda c
3 0 9.7286465425e+18 0.00e+00 1.40e+09 1.000000e+
4 1 2.7024029350e+17 -3.50e+06 1.40e+08 1.692820e-
5 2 1.1916089502e+12 -2.27e+10 1.40e+07 3.470030e-
6 3 1.1495914241e+11 -9.37e+05 1.40e+06 3.138413e-
7 4 1.1495914198e+11 -3.75e-04 1.40e+05 3.138407e-
8 iter chisq delta/lim lambda c
9
10 After 4 iterations the fit converged.
11 final sum of squares of residuals : 1.14959e+
12 rel. change during last iteration : -3.74605e-
13
14 degrees of freedom (FIT_NDF) : 4
15 rms of residuals (FIT_STDFIT) = sqrt(WSSR/ndf) : 169528
16 variance of residuals (reduced chisquare) = WSSR/ndf : 2.87398e+
17
18 Final set of parameters Asymptotic Standard Error
19 ======================= ==========================
20 c = 0.00313841 +/- 5.418e-05 (1.726%)


```
You arrive at a value ofc=0.00313841. Notice also the Asymptotic Standard Error of1.726%, which
indicates the error of our solution curve compared to the data. In this case a very good fit. You now
plot the fitted functiong(x)and the original points together:
```
1 gnuplot> set xlabel 'n'
2 gnuplot> set ylabel 'CPU ticks'
3 gnuplot> set title'O(n^2) algorithm'
4 gnuplot> plot'plot.txt' using 1:2 title'Points', \
5 g(x) title 'Quadratic Fit'

```
Given the relatively small error value, and the visual representation of our quadratic curve against
the data points, you can confidently assert that the algorithm in question is in the complexity class
ofO(n^2 ).
```
## 7 Saving your plots as pdf files

```
To save your plot as a pdf file do the following:
```
```
1.Determine what the terminal type is set to. You will use this later to set the terminal back to
its default.
```
```
1 gnuplot> show terminal
2
3 terminal type is qt 0 font "Sans,9"
```

```
In this case the terminal isqt, ignore the 0.
```
2. Plot the desired graph. Make sure it is what you wish to print.

3.Set the output to a filename (set output ’filename’). The file will be located in the directory
you started gnuplot from.

```
1 gnuplot> set output 'plot.ps'
```
4.Run the commandset terminal postscript. Everything plotted after this point will be
written in PostScript format to the output file specified in the previous step.

```
1 gnuplot> set terminal postscript
2
3 Terminal type is now'postscript'
4 Options are'landscape enhanced defaultplex \
5 leveldefault monochrome colortext \
6 dashlength 1.0 linewidth 1.0 pointscale 1.0 butt noclip \
7 nobackground \
8 palfuncparam 2000,0.003 \
9 "Helvetica" 14 fontscale 1.0'
```
```
There is no need to change the defaults.
```
5.Run the commandreplot. This will replot the plot created in the second step, but now the
plot will be written to the output file.

```
1 gnuplot> replot
```
6. Reset the terminal back to the original terminal type.

```
1 gnuplot> set terminal qt
2
3 Terminal type is now'qt'
4 Options are'0 font "Sans,9"'
```
7. Repeat the above steps for all plots.
8. Exit gnuplot.

9.You now need to convert the postscript files to pdf. You can use the commandps2pdfwhich
comes with Ghostscript.

```
1 $ ps2pdf plot.ps plot.pdf
```
```
Or you can use an online tool athttp://www.ps2pdf.com/convert.htm.
```

## 8 Plotting Factorials with gnuplot

```
Plotting the factorial function in gnuplot can be problematic. To plot factorials with gnuplot you
can define your own function for factorial or use the gamma function asgamma(n+ 1 ) =n!
```
```
The gamma function is a built in function. Try the following from a gnuplot session to see how to
do this and the difference between the two functions:
```
1 gnuplot> set yrange[0:6000]
2 gnuplot> set xrange[1:7]
3 gnuplot> fac(x) = (int(x) == 0)? 1.0 : int(x) * fac(int(x) - 1.0)
4 gnuplot> plot fac(x)


1 gnuplot> set yrange[0:6000]
2 gnuplot> set xrange[1:7]
3 gnuplot> plot gamma(x + 1)

## 9 Steps of this Project

```
In accordance with the scientific method, in this case with Computer Science flavor added, here is a
rough outline and a few tips:
```
1. Understand what Big O notation and time complexity are before you start!
2. **Question:** What runtime complexity does each function in the blackbox have?
3. **Automation (CS):** Write a program that interfaces with the blackbox: it should call the
    functions with differentn-values and record the runtime of each call.

```
Protip 1:Command-line arguments and for-loops are your friends! (Seriously! It takes a lot
more time for you to edit your code to use differentn-values than it does for you to program
them as command line arguments and call your program multiple times.)
```
```
Protip 2:Don’t start with command-line arguments and for-loops! Make sure your timer
works correctly first.
```

```
Protip 3:Automation does not have to finish before everything else. Get afeelfor the functions
with some timing, then try to further automate your testing process.
```
4. **Experiment:** Test each function forn-values (for list functions,nis the list size!) as you deem
    appropriate:

```
(a) Hypothesis: Start with low values fornand increase slowly (or quickly, depending
on the function). Get afeelfor the runtime under different circumstances. Formulate a
hypothesis for runtime complexity – mayben^2 , orn!, or 2n?
(b) Prediction: You do not have to run your program for hours! Find values ofnfor which
the function completes between a few milliseconds and a few seconds. This is possible
for all of them.
(c) Testing: When you find a range ofn-values to run the function with, repeat the same
values at least three times to make sure the runtime does not vary largely! You want
several sets of runtime data for each function toprovethat it is a certain complexity ,
just like in chemistry, biology, or physics labs.
```
```
For lists:You have to test each list function with each sorted, reverse-sorted, and shuffled
lists of various sizes! This means that each list function should have complexity testing
and analysis for each type of list.
(d) Analysis: Analyze your data with gnuplot as described above. Include the Asymptotic
Standard Error,cvalues, and graphs in your report.
```
5. **Report:** Make sure to include Asymptotic Standard Error,cvalues, and graphs in your report!
    To be clear, list functions have three different sets of complexity, error,cvalues, and graphs –
    one for each type of list (sorted, reverse-sorted, shuffled).

## 10 Submission

After you have analyzed the data and compiled the results, turn in this:

- summary.pdf: Write up a summary. Include each function’s algorithmic complexity, and
    support these findings with yourcvalues, Asymptotic Standard Error, and graphical figures.
- Code: Include your*.cfiles demonstrating shuffling and testing code.
- Valgrind script: Your code must execute with no memory leaks. Demonstrate this with a
    valgrind script.

Tarball your pdf files,*.cfiles,*.hfiles, Makefile, and valgrind script into a file named
cse122_firstname_lastname_project_big0.tar.gzand upload to Canvas before the due date.


