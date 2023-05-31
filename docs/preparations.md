To complete this tutorial you need to have the following tools installed. 

## Docker

In this example, we use the Docker Engine as a containerization platform. It will handle the 
required container images.

[:material-link: Installation](https://docs.docker.com/engine/install/)

!!! warning 

    Please follow the installation steps carefully.  
    Also, you need to be able to manage Docker as a non-root user:  
    [Linux post-installation steps](https://docs.docker.com/engine/install/linux-postinstall/)

## Python

You need at least python 3.10 to be able to run the dem.

[:material-link: Installation](https://www.python.org/downloads/)

## DEM

We use our open source command-line tool DEM, to manage the containerized Development Environments.

[:material-link: Installation](https://axemsolutions.io/dem_doc/installation/)

## VSCode

[:material-link: Installation](https://code.visualstudio.com/docs/setup/linux)

In this tutorial, the VSCode editor is used to showcase the benefits of containerized tools when 
developing embedded software. We also provide a separate chapter about how to integrate and utilize 
the containerized tools.

Nevertheless, **all the not VSCode-specific steps can be followed with any other editor**. 

## The base of the example project

We would like to write a very simple application for our target board. When creating software 
applications for embedded systems - even for very simple ones like LED blinking - some additional 
functionality is needed:

- Startup: instructions to bring up the processor to operate on a very basic level.
- Hardware Abstraction Layer: interfaces to communicate with the peripherals. In our case, the GPIO.

Implementing the above functionality is not in the scope of this tutorial, so we use ST's solution 
to generate it, the STM32CubeMX. 

!!! tip

    You can jump to [Development Environment intallation](dev_env.md) if you use the example 
    NUCLEO-F103RB board, and you don't want to write the example application by yourself. 
    Clone the example repo: `git clone https://github.com/axem-solutions/example`

### **Run the STM32CubeMX**

You need to install the STM32CubeMX for your development PC.
[:material-link: Installation](https://www.st.com/en/development-tools/stm32cubemx.html)

!!! note

    For this tutorial version 6.8.1 was used.

### **Generate the skeleton project**

Start the STM32CubeMX application. 

1. Select **ACCESS TO BOARD SELECTOR**.
2. In the new window make sure you are at the **Board Selector** tab. 
    1. In **Commercial Part Number** dropdown menu, select **NUCLEO-F103RB**. 
    2. Select the board from the **Boards List**.
    3. Press **Start Project**
    4. The CubeMX prompts a question to initialize all peripherals with their default mode. 
    Select **Yes**. For this basic task, we only need to modify a few things.
3. On the Pinout & Configuration tab under **Timers** select **TIM1**. We need a timer for the 
blinking.
    1. Select the **Internal Clock** as Clock Source.
    2. Under the timers configuration, on the Parameter Settings tab set the **Prescaler** value to 
    **63999** and the **Counter Period** to **499**. As the default clock routed for this peripheral 
    is 64MHz, we get a ms counter.
    3. On the NVIC Settings tab **enable** the **TIM1 update interrupt**. After 500 counts, an 
    interrupt gets generated so now we have a 0.5s scheduler.
4. On the Project Manager tab:
    1. Set the **Project Name** to `tutorial`.
    2. Set the **Project Location**.
    3. From the **Toolchain / IDE** dropdown, select **Makefile**.
5. Finally you can generate the project skeleton by selecting **GENERATE CODE**.
6. After the generation is complete you can close the STM32CubeMX application.