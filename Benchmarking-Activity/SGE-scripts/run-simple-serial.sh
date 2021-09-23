#!/bin/bash

## Specifies the interpreting shell for the job.
#$ -S /bin/bash

## Specifies that all environment variables active within the qsub utility be exported to the context of the job.
#$ -V

## Specifies the parallel environment if it is needed

## Execute the job from the current working directory.
#$ -cwd 

## The  name  of  the  job.
#$ -N EP_A

##send an email when the job ends
#$ -m e

##email addrees notification
#$ -M Your_email


## In this line you have to write the command that will execute your application.
./ep.A.x



