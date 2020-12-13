# Purpsose of CSE-701

This repository contains the three projects I completed for evaluation in CSE 701 at McMaster Univeristy. As my research interest is in Infectious Disease Modelling, each project was designed around that topic.

## Project 1

The first project was a C program that solved a defined differential equation using the Forward Euler and RK2 methods.

Detailed explanation of the implementation of the program can be found in the corresponding folder.

## Project 2

The second project was a non-object oriented C++ program that simulated an epidemic using the Gillespie Algorithm, first for the SIR model, then for the SEIR model. The program then estimates the initial growth rate `r` and the doubling time for the epidemics by fitting a line to the inital growth phase of the log of the simulated data. The slope of this line is `r` and then the doubling time is calculated using `r`.

This project needs work as at the time of submission, my VScode was not properly providing me with warnings so there are several warnings generated when the code is run.

Detailed explanation of the implementation of the program can be found in the corresponding folder.

## Final Project

The final project was an object-oriented C++ program that fits a very simple SIR model to data for a wave of an epidemic. First, the program takes input from .txt file that contains sample parameter values. This parameter data is then used to simulate an epidemic when you know the values of `R0` and `gamma`. The program then fits a model to the simulated data to check that you get the same parameters back. Next, the program takes input from two other .txt files. One that contains one wave of epidemic data with daily new counts. The other containing the population size of the region the data is from. It then fits the SIR model to the data and outputs the values of `R0` and `gamma` that result in the best fit.

Detailed explanation of the implementation of the program can be found in the corresponding folder.
