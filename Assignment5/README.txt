# Christopher Kelley and Bradford Smith
# CS 511 Assignment 5
# 11/24/2015
# "We pledge our honor that we have abided by the Stevens Honor System."
################################################################################

Structure:
  main.erl
    The main loop
  system.erl
    Generic functionality
  watcher.erl
    The watcher process
  sensor.erl
    The sensor process

Building and running:
  The following shell scripts provide the necessary functions:
    ./build.sh
      compiles all .erl files
    ./clean.sh
      removes all .beam files
    ./re.sh
      cleans then compiles
    ./run.sh <numSensors>
      Runs the main loop with 'numSensors' number of sensors
    ./rerun.sh <numSensors>
      does re then runs with 'numSensors' number of sensors
    ./submit.sh
      cleans and tars all files

The program can be run by using ./rerun.sh <numSensors> or using ./build.sh then
./run <numSensors> or by using ./build.sh and running main:main(<numSensors>).
from the erl shell.

We also decided to write our own random function in system:rand because Erlang's
random:seed(now()) did not seem sufficiently random for the speed we started our
processes. The seeds would be too close and all the sensors would get the same
numbers.

