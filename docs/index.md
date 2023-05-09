# Welcome

Welcome to axem's tutorial on a modern Development Environment using the dem tool. In this tutorial, 
you'll learn how to set up and manage a containerized Development Environment on Linux, create a new 
Development Environment, and use it with VS Code. 

!!! note

    This tutorial is for Linux only. 

## Tutorial Content

The tutorial covers the following topics:

1. How to set up and manage a containerized Development Environment on your PC
2. How to create a new Development Environment
3. How to use the containerized Development Environment with VS Code

At the end of the tutorial you should be able to set up a working Development Environment and dive 
into writing the embedded software.

!!! tip

    If you get stuck at any step, you can check out the 
    [example repo](https://github.com/axem-solutions/example), which is a complete reference 
    project.

## Example Project

In this tutorial, we will create a basic embedded project – blinking LEDs on an STM32F103 on a 
NUCLEO-F103RB board. You can use the processor of your choice, but then you'll need to handle the 
hardware-specific parts by yourself.

The project skeleton will be generated with the STM32CubeMX tool, which will allow us to use the HAL 
provided by ST. The following tools will be used for the example project's Development Environment:

- Build system: [make](https://www.gnu.org/software/make/#documentation)
- Toolchain: [gnu-arm-none-eabi](https://gcc.gnu.org/onlinedocs/)
- Debugger and deployer: [stlink-org](https://github.com/stlink-org/stlink)
- Test environment: [CppUTest](http://cpputest.github.io/)

For demonstration purposes, we'll be using VS Code as the editor. If you'd like to use these tool 
images with another editor, feel free to send us a message.