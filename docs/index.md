# Welcome

Welcome to axem's tutorial on a modern 
[Development Environment](https://axemsolutions.io/dem_doc/development_environments/) using the DEM 
tool!  
Before beginning, we recommend that you first read the DEM 
[documentation](https://axemsolutions.io/dem_doc/) for a comprehensive understanding.  
In this tutorial you'll learn how to create, install, and manage containerized Development 
Environments on Linux, and use them with [VS Code](https://code.visualstudio.com/). 

> DEM v0.6.0 or later is needed to follow this tutorial.

!!! note

    Currently the DEM only works on Linux, so this tutorial is for Linux only. 
    You should be able to follow along with WSL.

    Tested on:

    - Ubuntu 22.04
    - Debian 11

## Tutorial Content

The tutorial covers the following topics:

1. How to install and manage predefined containerized Development Environments provided by axem
2. How to use a containerized Development Environment with VS Code
3. How to create a new Development Environment from the containerized tools of your choice

By completing this tutorial, you should be able to set up a working Development Environment, which
can be used to create embedded applications.

!!! tip

    If you get stuck at any step, you can check out the 
    [example repo](https://github.com/axem-solutions/example), which contains a complete reference 
    project.

    Also, feel free to reach out to us on [Discord](https://discord.com/invite/Nv6hSzXruK) if you 
    have any questions or need help.

## Example Project

In this tutorial, we will create a basic embedded project – blinking LEDs with an 
[STM32F103](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html) on a 
NUCLEO-F103RB board.  

The project skeleton will be generated with the STM32CubeMX tool, which will allow us to use the HAL 
provided by ST. The example project's Development Environment will consist of the following tools:

- Build system: [make](https://www.gnu.org/software/make/#documentation)
- Toolchain: [gnu-arm-none-eabi](https://gcc.gnu.org/onlinedocs/)
- Debugger: [stlink-org](https://github.com/stlink-org/stlink)
- Test environment: [CppUTest](http://cpputest.github.io/)

For demonstration purposes, we'll be using VS Code as the editor. If you'd like to use these tool 
images with another editor and need some help, feel free to send us a message.