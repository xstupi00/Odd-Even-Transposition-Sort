#!/bin/bash

################################################################
# File:       test.sh
# Author:		  Šimon Stupinský
# University: Brno University of Technology
# Faculty: 	  Faculty of Information Technology
# Course:	    Parallel and Distributed Algorithms
# Date:		    13.03.2020
# Last change:14.04.2020
# 
# Subscribe:	The test shell script to run Odd-Even Transposition
#             algorithm with random sequence of numbers.
# 
################################################################

#####
# @file    test.sh
# @brief   The test shell script to generate random number sequence of a given length
#          and subsequently builds and runs the program, which implements the Odd-Even
#          Transposition algorithm with this generated numbers. In the end it removes
#          all created files during its execution.
#####

# processing of argument (default value is equal to 10)
if [ $# -lt 1 ];
then
  numbers=10;
else
  numbers=$1;
fi;

# create the file with random number according the given count
dd if=/dev/urandom bs=1 count="$numbers" of=numbers

# compile source code
mpic++ -o ots ots.cpp

# run binary
mpirun -np "$numbers" ots

# clean directory
rm -f ots numbers