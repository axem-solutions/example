# CLI usage

You can use the tools from the command line in the same way whether you are on a native host or in a 
container. Below are some examples of the most common tasks that a Development Environment needs to 
handle.

## Building the software

To build the software, run the following command from the root directory of your project:

    docker run --rm -v "$(pwd)":/work axemsolutions/make_gnu_arm make

Here's a breakdown of the command:

- `--rm`: Removes the container right after the build is finished.
- `-v "$(pwd)":/work`: Mounts the root directory of your project to `/work` in the container.
- `axemsolutions/make_gnu_arm`: The tool image to run in the container.
- `make`: The command to execute in the container.

## Running the tests

To run the tests, use this command:

    docker run --rm -v "$(pwd)":/work axemsolutions/cpputest /bin/sh -c "cd app/test; make"

Here's what each part of the command does:

- `--rm`: Removes the container right after the test cases have run.
- `-v "$(pwd)":/work`: Mounts the root directory of your project to `/work` in the container.
- `axemsolutions/cpputest`: The tool image to run in the container.
- `/bin/sh -c "cd app/test; make"`: The command to execute in the container.

## Deploying to target

To deploy to the target, follow these steps:

1. Connect the Nucleo board to your PC.
2. Run the following command:

    docker run --privileged --rm -v "$(pwd)":/work axemsolutions/stlink_org /bin/sh -c "cd build; 
    st-flash write tutorial.bin 0x8000000"

Here's what each part of the command does:

- `--prvileged`: Give access to the USB devices.  
:warning: Only use this flag for testing purposes. The safe way is to only give access for the 
actual ST-Link USB device.
- `--rm`: Removes the container after writing to the flash.
- `-v "$(pwd)":/work`: Mounts the root directory of you project to `/work` in the container. 
- `axemsolutions/stlink_org`: The tool image to run in the container.
- `/bin/sh -c "cd build; st-flash write tutorial.bin 0x8000000"`: The command to execute in the 
container.

## Debugging

GDB is based on a client-server architecture. The client is in the axemsolutions/make_gnu_arm image,
and the server is in the axemsolutions/stlink_org image. Therefore, you need both containers 
running.

Since you have two separate containers, you need a way to let them communicate with each other. 
Normally, the GDB client and server communicate over TCP/IP, so you need to create a network for 
them.

To create a bridged network called `gdb-net`, run the following command:

    docker network create gdb-net

In the next step, you need to start the GDB server with access to this gdb-net. Use this command:

    docker run -it --privileged --rm --network=gdb-net axemsolutions/stlink_org

Here's what each part of the command does:

- `-it`: Starts an interactive shell, which is useful to see what's going on in the container.
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