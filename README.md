AI-WORD-TRACE
=============

A COMP445 Project
-----------------

###Purpose:

The following code plays the *word search game*. Given two words and a dictionary, our program finds a sequence of words in the dictonary, each only one edit apart, that start at the first and end at the second word.

###Method:

Our program finds solutions to the word search game by performing a search. The default operation is A\*, using the [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance) from the current word to the goal as a heuristic. 
To simplify discussion, we say that two strings A and B are *L-Adjacent* if their Levenshtein distance is 1. As such, a correct solution to the word search game is a series of L-Adjacent words.

We use the linux dictionary which can be found in */usr/share/dict/*, a copy of which is supplied in this repo. It is important to note that this is a _near_ english dictionary.

###Results:

Initial results are promissing, and more connections exist than initially believed. That being said, some seemingly simple connections require minutes to calculate, and often all L-Adjacent words will have a larger Levenshtein distance than the first.
The result is that A\* has a hard time finding the goal, and needs to expand many nodes before the Levenshtein distance decreases.

####Example:
	Justin fustin fustic rustic rutic rutin ruin run rue rube ruble rumble jumble


###Contributors:

- Justin Sybrandt
- John Umble