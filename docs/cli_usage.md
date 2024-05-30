# CLI Usage

!!! note
    Assuming the Tutorial Dev Env is set as the default one. You can check if it is set as the default
    by running the `dem info Tutorial` command.

    If the Tutorial Dev Env is not set as the default, you can set it by running the following 
    command: `dem set-default Tutorial`. 

    If you don't want to set the Tutorial Dev Env as the default, you must use the `run` command 
    like this: `dem run Tutorial <task>`.

## Building the software

To build the software, run the following command from the root directory of your project:

    dem run build

This command is a Dev Env specific alias for 
`docker run --rm -v "$(pwd)":/work axemsolutions/make_gnu-arm:13.2 make`:

- `--rm`: Removes the container right after the build is finished.
- `-v "$(pwd)":/work`: Mounts the root directory of your project to `/work` in the container.
- `axemsolutions/make_gnu-arm:13.2`: The tool image to run in the container.
- `make`: The command to execute in the container.

## Running the tests

To run the tests, use this command:

    dem run test

This command is a Dev Env specific alias for 
`docker run --rm -v "$(pwd)":/work axemsolutions/cpputest /bin/sh -c "cd app/test; make"`:

- `--rm`: Removes the container right after the test cases have run.
- `-v "$(pwd)":/work`: Mounts the root directory of your project to `/work` in the container.
- `axemsolutions/cpputest`: The tool image to run in the container.
- `/bin/sh -c "cd app/test; make"`: The command to execute in the container.

## Deploying to target

First connect the Nucleo board to your PC, then run the following command:

    dem run deploy

This command is a Dev Env specific alias for
`docker run --privileged --rm -v "$(pwd)":/work axemsolutions/stlink-org:1.8.0 /bin/sh -c "cd build; 
st-flash write tutorial.bin 0x8000000"`:

- `--privileged`: Give access to the USB devices.  
- `--rm`: Removes the container after writing to the flash.
- `-v "$(pwd)":/work`: Mounts the root directory of you project to `/work` in the container. 
- `axemsolutions/stlink-org`: The tool image to run in the container.
- `/bin/sh -c "cd build; st-flash write tutorial.bin 0x8000000"`: The command to execute in the 
container.

## Debugging

GDB is based on a client-server architecture. The client is in the axemsolutions/make_gnu-arm image,
and the server is in the axemsolutions/stlink_org image. Therefore, you need both containers 
running.

Since you have two separate containers, you need a way to let them communicate with each other. 
Normally, the GDB client and server communicate over TCP/IP, so you need to create a network for 
them.

To create a bridged network called `gdb-net`, run the following command:

    docker network create gdb-net

In the next step, you need to start the GDB server with access to this gdb-net.

!!! warning

    The Nucleo board must be connected before starting the GDB server.

Run this command:

    dem run gdb-server

This command is a Dev Env specific alias for 
`docker run -it --privileged --rm --network=gdb-net axemsolutions/stlink-org:1.8.0`:

- `-it`: Starts an interactive shell, which is useful to see what's going on in the container.
- `--privileged`: Give access to the USB devices.  
- `--rm`: We can remove the container after the debug session.
- `--network=gdb-net`: Connect to the gdb-net network.
- `axemsolutions/stlink-org`: The tool image to run in the container.

Open another terminal and run the GDB client.

    dem run gdb-client

This command is a Dev Env specific alias for
`docker run -it --rm -v "$(pwd)":/work --network=gdb-net axemsolutions/make_gnu-arm:13.2`:

- `-it`: With an interactive shell. We would like to use the GDB as a CLI application from this 
terminal.
- `--rm`: We can remove the container after the debug session.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `--network=gdb-net`: Connect to the gdb-net network.
- `axemsolutions/make_gnu-arm`: The tool image to run in the container.

Now get back to the GDB server's terminal and get its IP address.

    hostname -I
    
Start the server provided by stlink-org. If the command is successful, it will print `Listening at 
*:{port}` - note this port number.

    st-util

For the GDB client, follow these steps:

1. Start the GDB client with the elf file as the parameter.

    ```
    arm-none-eabi-gdb build/tutorial.elf
    ```

2. You should see GDB's own shell.
3. Connect to the server by providing its IP address and the noted port number for the GDB client.

    ```
    target remote {server ip:port}
    (for example: target remote 172.24.0.2:4242)
    ```

4. Load the binary to the NUCLEO.

    ```
    load
    ```

5. Now you should be able to debug.