# Design and Implementation of a Micro Operating System Over an ARM Architecture Processor.

## Abstract

As students, we are often propelled towards a high level programming throughout the four years of the computer science degree. Java for the highest language and C for the lowest language. However, all the languages were used atop an Operating System with the libraries that it comprises. It was very curious along these years to be able to deal with the hardware and get a better grasp of how Operating System really works under the hood. My choice was therefore to dedicate my bachelor thesis to design and implement my own educational Operating System.
The goal of this Bachelor Thesis is to implement a mini-OS from the ground up avoiding as much as possible the use of external libraries. That way, we will go on to implement our own boot-loader, hardware initialization, standard I/O library, graphical library, etc.
The device used for designing and implementing the operating system is the Rasp- berry Pi model B+, which CPU uses the ARM architecture. The reason for this choice was to use a cheap and convenient device for the task. The Raspberry Pi costs around 30e and boots from an SD card that can be easily placed and removed. The boot time is also virtually instantaneous, which comes very handy at the time of the implementation.

## Installation

In order to be able to compile the project, an ARM cross-compiler is needed. Then, follow the step described below:
- Download require file for a proper booting of the OS and store them in the *boot* directoy
```bash
make bootfiles
```
- Compile the kernel
```bash
make gcc
```

Or to execute both at once, simply execute:
```bash
make all
```

You can then proceed to place the content of the *boot* folder into the root of your SD card, place the SD card in the Raspberry-Pi, power it up and enjoy!


## Credits

Jérôme Grossé

