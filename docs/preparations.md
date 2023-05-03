## Docker

In this example we use the Docker Engine as a containerization platform. It will handle the 
required container images.

[:material-link: Installation](https://docs.docker.com/engine/install/)

## Python

You need at least python 3.10 to be able to run the dem.

[:material-link: Installation](https://www.python.org/downloads/)

## dem

We use the open source `dem` command line tool to manage the containerized Development Environment.

[:material-link: Installation and Documentation]()

## VSCode

In this tutorial the VSCode editor is used to showcase the benefits of containerized tools when 
developing embedded software. We also provide a separate chapter about how to integrate and utilyze 
the containerized tools.

Nevertheless, all the not VSCode specific steps can be followed with any other editor. 

## The base of the example project

We would like to write a very simple application for our target bourd. When creating software 
applications for embedded systems - even for very simple ones like LED blinking - some additional 
functionality needed:

- Startup: instructions to bring up the processor to operate on a very basic level.
- Hardware Abstraction Layer: interfaces to communicate with the peripherals. In our case the GPIO.

Implementing the above functionality is not in the scope of this tutorial, so we use ST's solution 
to generate it, the STM32CubeMX. 

!!! note

    You can skip the upcoming part if you use the example NUCLEO-F103RB board, and you don't want to 
    generate the project skeleton. Clone the example repo:
        `git clone https://github.com/axem-solutions/example`

### Run the STM32CubeMX

You need to install the STM32CubeMX for you host PC.
[:material-link: Installation](https://www.st.com/en/development-tools/stm32cubemx.html)

Start the STM32CubeMX application. 

!!! note

    For this tutorial I used version 6.8.1

### Generate the skeleton project

1. Select **ACCESS TO BOARD SELECTOR**.
2. In the new window be sure you are at the **Board Selector** tab. 
    1. In **Commercial Part Number** dropdown menu select **NUCLEO-F103RB**. 
    2. Select the board from the **Boards List**.
    3. Press **Start Project**
3. The CubeMX prompts a question to initialize all peripherals with their default mode. 
Select **Yes**. For this basic task we only need to modify a few things.
4. On the Pinout & Configuration tab under **Timers** select **TIM1**. We need a timer for the 
blinking.
    1. Select the **Internal Clock** as Clock Source.
    2. On the Parameter Settings tab set the **Prescaler** value to **63999** and the 
    **Counter Period** to **499**. As the default clock routed for this peripheral is 64MHz, we get 
    a ms counter.
    3. On the NVIC Settings **enable** the **TIM1 update interrupt**. After 500 counts an interrupt
    gets generated so now we have a 0.5s scheduler.
5. On the Project Manager tab:
    1. Set the **Project Name**.
    2. Set the **Project Location**.
    3. From the **Toolchain / IDE** dropdown select **Makefile**.
5. No more modifications needed, the rest of the settings can remain as default.
6. Finally you can generate the project skeleton by selecting **GENERATE CODE**.