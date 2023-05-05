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

    docker run --privileged --rm -v "$(pwd)":/work axemsolutions/stlink_org /bin/sh -c "cd build; st-flash write tutorial.bin 0x8000000"

- `--prvileged`: Give access to the USB devices.  
:warning: Only use this flag for testing purposes. The safe way is to only give access for the 
actual ST-Link USB device.
- `--rm`: We can remove the container right after writing to the flash.
- `-v "$(pwd)":/work`: Mount the root directory of you project to `/work` in the container. 
- `axemsolutions/stlink_org`: The tool image to run in the container.
- `/bin/sh -c "cd build; st-flash write tutorial.bin 0x8000000"`: The command to execute in the 
container.