# Linux Timer Demo

This code demonstrates how to create a periodic timer under Linux,
for example if you need to sample a signal and you don't have any
external interrupts.

The demo calls the function "handler" every 500ms. Just change
its.it_interval.tv_nsec to any other interval. It's in nanoseconds.

## How to compile

make

## How to run

./linux-timer-demo

and it prints out a message every 500ms and checks that the handler
has been really called by this timer.


The code is loosely based on the timer_create() man page.
