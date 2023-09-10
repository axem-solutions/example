# Development Environment installation

## Installation

DEM can install preconfigured Development Environments from online catalogs. List the available 
catalogs:

    dem list-cat

!!! note 

    You can add or delete catalogs with the `dem add-cat` and `dem del-cat` commands.

After a clean installation, you have the axem organization enabled by default. 
You can list the available Development Environments in all available catalogs:

    dem list --all --env

For this tutorial, we are going to use the **Tutorial** Development Environment. You can get more 
information about it by the following command:

    dem info Tutorial

One of DEM's biggest advantages is that installing a preconfigured Development Environment is only a 
single command. Install the **Tutorial** Development Environment:

    dem pull Tutorial

The DEM will pull the images we saw after the `dem info Tutorial` command:

- `axemsolutions/make_gnu_arm:latest`: contains the make and gnu-arm-none-eabi tools
- `axemsolutions/stlink_org:latest`: contains the stlink-org tool
- `axemsolutions/cpputest:latest`: contains the CppUTest tool

!!! note 

    The images get pulled from an available registry. List the available registries with the 
    `dem list-reg` command. Use the `dem add-reg` and `dem del-reg` commands to add and delete 
    registries.

If you issue the `dem info Tutorial` command again, you will see that the required images are now 
available locally. Running `dem list --local --env` makes the locally installed Development 
Environments get listed, so in our case, you should see the Tutorial Development Environment.

Now you are ready to make embedded software!

!!! note

    At this point, you can use the tools as containerized CLI applications.  

    If you want to learn about how to create a new Development Environment from the containerized 
    tools of your choice, check out the chapter 
    [Learn more: how to create a new Development Environment](create_new_dev_env.md).
