Final Days of Goldfinger
Author: Kaysar Abdullah
Limits: 1s, 512 MB
link: https://toph.co/p/final-days-of-goldfinger

We see agent Bond once again being called in time of a great need. The vile criminal Auric Goldfinger has stolen a metric tonnes of gold off the U.S military gold deposit right under their nose. Agent Bond has been tracking Goldfinger for a long time after the foul villain has made his mark by establishing the world’s largest underground gold smuggling network, but this time Goldfinger has left enough clues to be tracked to his hideout. There is no saving for Goldfinger now! Once he finally faces agent Bond no matter how many bodyguard Goldfinger has hired and how many golden fortress he has made, nothing can stop from bringing him to justice.

Goldfinger has made his hideout in a large abandoned oil processing factory. The entire factory is composed of several structures, towers and such, lined in a straight line from left to right. Agent Bond doesn’t really know which structure he will find Goldfinger in, but he is sure that agent Bond will always move from one structure’s ceiling to the ceiling of the structure immediately to it’s right. Agent Bond plans to be dropped on one of the structure by a helicopter, from which he will keep moving right by jumping from ceiling to ceiling until he finds Goldfinger.

The structures are serially numbered, the leftmost being 1, where structure i have a height Hi. Agent Bond will lose some potential energy to climb the next structure i+1 if it’s height Hi+1 is greater than Hi, and he will gain some potential energy if the next structure has lower height instead. The amount of energy he gains or loses is equal to the absolute difference in Hi and Hi+1. So what happens if his energy goes below zero? Well, that’s what Goldfinger would want too because Bond will die. But clever agent Bond is well aware of it, so what he can do is before he lands on the factory he will drink some of his favourite wine to gain some starting potential energy, enough to carry with him on his endeavour. Agent Bond doesn’t want to drink too much wine though, just enough to get the energy to get from his starting position to his target structure. Let’s call this minimum needed energy the optimum energy.

Now agent Bond has collected the list of height of all the structures in the factory and in the order that they currently are and plans to do some dry runs. Some of the heights are also negative, but you don’t need to think much about it though since agent Bond knows what he is doing. He has also hired you to write a program that will do some tasks on the data and answer some of his queries. What agent Bond asks you to do is described below:

Task Type 1:

i h which means he asks you to change the height of the ith building to h.

Task Type 2:

l r Now this one is a bit complicated! You have to tell him the maximum among all the optimum energy he would need for every possible i, j such that l ≤ i ≤ j ≤ r, and he starts from the structure i and would end up finding Goldfinger in structure j without dying.

The feasibility of this mission now lies on your shoulder, my friend. Do not let agent Bond down or else you will disappoint the entire world.

Input

First line of the input is T (1 ≤ T ≤ 10) which describes the number of test cases. For each test case the first line contains two integer N (1<= N <= 105) and Q (1<= Q <= 105), where N is the number of structures in the factory and Q is number of tasks agent Bond asks you to do. The next line contains N integers, ith of which describes the height Hi (-109 ≤ Hi ≤ 109) of ith structure.

Then follow Q more lines where each line contains three integers each. If the first integer is 1, use the next two integers i (1≤ i ≤ N) and h (-109 ≤ h ≤ 109) to carry out the Task Type 1. If the first integer is 2 instead, use the next two integers l and r (1 ≤ l ≤ r ≤ N) to answer Task Type 2.

Output

For each test case print a line with the format: “Case T:“, where T is test case number. Then for each of the Task Type 2 asked in the Tth test case, print the answer in a new line.

Samples

Input	Output
1
7 4
-10 6 5 -4 -3 8 -9
2 1 7
1 6 5
2 1 7
2 2 6
Case 1:
18
16
9

Explanation:

In the sample data we only deal with one test case. Here there are three tasks of type 2 and one task of type 1.

For the first task 2 1 7, there are total of 21 possible scenarios where agent Bond will start at some structure and end at some other. For example one of them would be where agent Bond starts from the 2nd structure and ends up in the last (7th) one, and for this journey he would need an optimum energy of 2. But we can see that for the journey that starts from 1st structure and ends at the 6th he would need an optimum energy of 18 to reach the target, and this is the maximum among all the possible scenarios and thus is the answer to the first task.
