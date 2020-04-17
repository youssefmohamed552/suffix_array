Name: Youssef Hussein
Class: CSC284
Assignment: 5

The program takes a string and then converts it to a suffix array

the program runs on the sample test case
 

it seems to run on most of the cases of the large and medium and small but not all of them. for somereason it's not running well on the other test cases but it doesn't seem to perform the expected out come where it seems to be off by a couple in the sorting. Unfortunaltly there doesn't seem to be a consistent problem so I wansn't able to undertand where the problem is comming from.

build and run:
# mkdir build
# cmake ..
# make
# ./exec < <input_file> > <output_file>


timing:
small:

193 microsecs 
108 microsecs 
108 microsecs 
213 microsecs 
97 microsecs 
203 microsecs 
99 microsecs 
223 microsecs 
154 microsecs 
195 microsecs 
119 microsecs 
99 microsecs 
89 microsecs 
99 microsecs 
206 microsecs 
217 microsecs 
190 microsecs 
93 microsecs 
102 microsecs 
127 microsecs 
191 microsecs 
102 microsecs 
136 microsecs 
112 microsecs 
101 microsecs 


medium:


738 microsecs 
18023 microsecs 
19759 microsecs 
7574 microsecs 
18319 microsecs 
10663 microsecs 
768 microsecs 
20168 microsecs 
7692 microsecs 
10702 microsecs 
18718 microsecs 
13889 microsecs 
19122 microsecs 
21362 microsecs 
17781 microsecs 
5717 microsecs 
4649 microsecs 
15581 microsecs 
9269 microsecs 
1920 microsecs 
204 microsecs 
15522 microsecs 
7070 microsecs 
1866 microsecs 
17513 microsecs 


large:


594 microsecs 
1586494 microsecs 
1204040 microsecs 
1317328 microsecs 
16103 microsecs 
984660 microsecs 
245847 microsecs 
1542338 microsecs 
1415229 microsecs 
1483691 microsecs 
716292 microsecs 
1296009 microsecs 
1397270 microsecs 
26488 microsecs 
1676672 microsecs 
303214 microsecs 
829599 microsecs 
587390 microsecs 
239299 microsecs 
910270 microsecs 
536981 microsecs 
1219832 microsecs 
304324 microsecs 
1687999 microsecs 
972321 microsecs 
