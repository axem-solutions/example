# The Development Environment

## Installation

DEM can install ready Development Environments from online sources available for an organization.
After a clean installation you have the axem organization enabled by default. You can list the 
available Development Environments in this org.

    dem list --all --env

For this tutorial we are going to use the **Tutorial** Development Environment. You can get more 
information about it by the following command:

    dem info Tutorial

One of DEM's biggest advantage is that installing a configured Development Environment is only a 
single command. Install the **Tutorial** Development Environment:

    dem pull Tutorial

If you issue the `dem info Tutorial` command again, you will see that the required images are now 
available locally. Running `dem list --local --env` makes the locally installed Development 
Environments get listed, so in our case you should see the Tutorial Development Environment.

Now you are ready to make embedded software!

!!! note

    At this point, you can use the tools as containerized CLI applications. See the 
    [next page](vscode_integration_guide.md) about how to integrate the Development Environment into 
    the VSCode editor.

## A new Development Environment

You can create new Development Environments from containerized tools. The tool images can be 
present:

- locally: `dem list --local --tool`
- in registry: `dem list --all --tool`

As an example let's create an other, alternative Environment for out target with the following
elements:

- Build system: [cmake](https://cmake.org/documentation/)
- Toolchain: [gnu-arm-none-eabi](https://gcc.gnu.org/onlinedocs/)
- Debugger and deployer: [J-Link](https://www.segger.com/products/debug-probes/j-link/#software)
- Test environment: dummy test

### Obtaining the cmake, gnu-arm-none-eabi and J-Link tool images

These tools are available in the axem registry.

### Obtaining the dummy test tool image

You can use your own tools that you containerized by yourself in Development Environments created 
with dem. To see how to do it, we containerize a dummy test tool. (This won't be an actual test 
environment, just a script that prints "test environment" :face_with_hand_over_mouth:.)

Let's create a directory for building the dummy test tool!

    mkdir dummy_test
    cd dummy_test

Create a shell script that will run inside the container.

``` sh title="dummy_test.sh"
#!/bin/sh

echo "test environment"
```

Create a Dockerfile that describe how to build this dummy image.

``` title="Dockerfile"
FROM debian:latest

WORKDIR /work
ADD dummy_test.sh /work
```

Build the Docker container image.

    docker build -t dummy_test:latest .

Try running the script inside a container to convince ourselves everything went as expected.

    docker run dummy_test /bin/sh -c "./dummy_test.sh"

### Create the new Environment

To start the interactive Development Environment creation you need to use the `dem create` command. 

    dem create "Tutorial Alternative"