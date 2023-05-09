# CLI usage

From the command line the tools can be used the same way in a container as on the native host. Here
I would like to give examples for the most common tasks a Development Environment needs to handle.

## Building the software

Run the following command from the root directory of your project:

    docker run --rm -v "$(pwd)":/work axemsolutions/make_gnu_arm make

Now let's break down this command: 

- `--rm`: We can remove the container right after the build finished.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `axemsolutions/make_gnu_arm`: The tool image to run in the container.
- `make`: The command to execute in the container.

## Running the tests

    docker run --rm -v "$(pwd)":/work axemsolutions/cpputest /bin/sh -c "cd app/test; make"

- `--rm`: We can remove the container right after the test cases ran.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `axemsolutions/cpputest`: The tool image to run in the container.
- `/bin/sh -c "cd app/test; make"`: The command to execute in the container.

## Deploy to target

Connect the Nucleo board to your PC.

    docker run --privileged --rm -v "$(pwd)":/work axemsolutions/stlink_org /bin/sh -c "cd build; 
    st-flash write tutorial.bin 0x8000000"

- `--prvileged`: Give access to the USB devices.  
:warning: Only use this flag for testing purposes. The safe way is to only give access for the 
actual ST-Link USB device.
- `--rm`: We can remove the container right after writing to the flash.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `axemsolutions/stlink_org`: The tool image to run in the container.
- `/bin/sh -c "cd build; st-flash write tutorial.bin 0x8000000"`: The command to execute in the 
container.

## Debugging

GDB is based on a client-server architecture. The client is in the axemsolutions/make_gnu_arm image,
the serve is in the axemsolutions/stlink_org image. Meaning, we need both containers running. 

Since we have two separate containers, we need a way to let them communicate with each other. 
Normally, the GDB client and server commuicate over TCP/IP, so we need to create a network for them.

    docker network create gdb-net

This command will create a bridged network called `gdb-net`. In the next step, we need to start the 
GDB server with access to this gdb-net.

    docker run -it --privileged --rm --network=gdb-net axemsolutions/stlink_org

- `-it`: With an interactive shell. Useful to see what's going on in the container.
- `--prvileged`: Give access to the USB devices.  
:warning: Only use this flag for testing purposes. The safe way is to only give access for the 
actual ST-Link USB device.
- `--rm`: We can remove the container after the debug session.
- `--network=gdb-net`: Connect to the gdb-net network.
- `axemsolutions/stlink_org`: The tool image to run in the container.

Open another terminal and run the GDB client.

    docker run -it --rm -v "$(pwd)":/work --network=gdb-net axemsolutions/make_gnu_arm

- `-it`: With an interactive shell. We would like to use the GDB as a CLI application from this 
terminal.
- `--rm`: We can remove the container after the debug session.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `--network=gdb-net`: Connect to the gdb-net network.
- `axemsolutions/make_gnu_arm`: The tool image to run in the container.

Now get back to the GDB server's terminal and get its IP address.

    hostname -I
    
Start the server provided by stlink-org. 

    st-util

For the GDB client, follow these steps:

1. Start the GDB client with the elf file as parameter.

    ```
    arm-none-eabi-gdb build/tutorial.elf
    ```

2. You should see GDB's own shell.
3. Connect to the server by providing its IP address for the GDB client.

    ```
    target remote {server ip}
    ```

4. Load the binary to the NUCLEO.

    ```
    load
    ```

5. Now you should be able to debug.