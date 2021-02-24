# Csources
A generic repository for c source codes

Note that all the functions that i used come from the book "The c programming language" or are written by myself

The game works in the following way, to communicate, instead of the letters of the alphabet, the positions of the corresponding letters are used, for example "1511" is "ok". The problem lies in the fact that there are no spaces between the letters, and therefore not even between the various numbers, consequently 1511 can be translated with 4 solutions: "aeaa", "aek", "oaa" and "ok".

So the purpose of the function (ntoaMS2020) is to calculate all the possible solutions and then let the user choose the best one.

The function (ntoaMS2020) in turn calls the function (put) which generates a binary tree in which each branch from the root to the termination is a solution, and then the function (toprintt) which runs through the tree to extract the solutions.

The tree is structured as follows:
- take the first digit
       if the next digit * 10 + the digit already taken is <= 26, then (2 possibilities) and then the right branch is created with the starting digit and the left branch with the next digit * 10 + the digit already taken.

otherwise, only the right branch is generated

In any case I have attached a graphic example of the tree.

Let me know if you like the algorithm and also if the code is well written (I'm still learning C).

I am aware that there is probably a better algorithm, both in terms of performance and logic.

Thanks anyway for reading this page! 
