# Welcome

This is a tutorial to demonstrate axem's vision of a modern Development Environment, with the help 
of the dem tool. Going through these steps you are going to find solutions for some of the greatest
challenges of embedded development.

!!! note

    The tutorial is for Linux only. 

## The content

The tutorial covers the following topics:

1. How to set up and manage a Development Environment for your PC to use containerized tools?
2. How to containerize a tool?
3. How to use the containerized Development Environment with VS code?

At the end of the tutorial you should be able to set up a working Development Environment and dive 
into writing the embedded software.

!!! tip

    If you get stuck at any step, you can check the 
    [example repo](https://github.com/axem-solutions/example), which is a complete reference 
    project.

## The example project

In this tutorial we create the typical embedded *hello world* project - blinking LEDs on the board. 

- The target is an STM32F103 on a NUCLEO-F103RB board.
- The project skeleton gets generated with the STM32CubeMX tool, so the HAL provided by ST can be 
used.
- The following tools are used for the example project's Development Environment:
    - Build system: [make](https://www.gnu.org/software/make/#documentation)
    - Toolchain: [gnu-arm-none-eabi](https://gcc.gnu.org/onlinedocs/)
    - Debugger and deployer: [stlink-org](https://github.com/stlink-org/stlink)
    - Test environment: [CppUTest](http://cpputest.github.io/)
- We us the VSCode as editor for demonstration. If you would like to use the above tool images with 
an other editor, feel free to send us a message.