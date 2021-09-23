#!/bin/bash

## Specifies the interpreting shell for the job.
#$ -S /bin/bash

## Specifies that all environment variables active within the qsub utility be exported to the context of the job.
#$ -V

## Execute the job from the current working directory.
#$ -cwd

## Parallel programming environment (mpich) to instantiate and number of computing slots.
#$ -pe mpich 32

## The  name  of  the  job.
#$ -N l5

## Send an email at the start and the end of the job.
#$ -m be

## The email to send the queue manager notifications.
#$ -M email@udl.cat

## The folders to save the standard and error outputs.
#$ -o $HOME/results
#$ -e $HOME/results

##Passes an environment variable to the job
#$ -v  OMP_NUM_THREADS=4

## In this line you have to write the command that will execute your application.
mpiexec -n 3 ./hybrid
