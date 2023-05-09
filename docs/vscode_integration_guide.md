# VSCode integration

## Creating tasks

VSCode has a neat feature to run arbitrary tasks within the editor. Assigning the docker commands to
tasks makes it easy to run them without opening the terminal.  
In this section we assign tasks for the CLI commands we used in the 
[CLI usage chapter](cli_usage.md). Open the VSCode command palette and search for *Open User Tasks*.

Add the following task descriptions and replace the {Binary file} with your .bin file.

``` json title="tasks.json"
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build Project",
            "type": "shell",
            "command": "docker run --rm -v \"$(pwd)\":/work axemsolutions/make_gnu_arm make"
        },
        {
            "label": "Deploy to target",
            "type": "shell",
            "command": "docker run --privileged --rm -v \"$(pwd)\":/work axemsolutions/stlink_org /bin/sh -c \"cd build; st-flash write {Binary file} 0x8000000\""
        },
        {
            "label": "Run unit tests",
            "type": "shell",
            "command": "docker run --rm -v \"$(pwd)\":/work axemsolutions/cpputest /bin/sh -c \"cd app/test; make\""
        }
    ]
}
```

Now you can run these commands as tasks. To make them even more easier to start, it is possible to 
assign specific keybindings.  
In the command palette search for *Configure Default Build Task*. From the list select the 
**Build Project** (the label of the task in the tasks.json). You will see that in the tasks.json the
VSCode automatically extended the Build Project task. Now if you press `ctrl+shift+b` the build task
starts.

## Debugging

I would like to show a method for setting up debugging in VSCode. We will use the same method as we
did in the [CLI Debugging chapter](cli_usage.md#debugging), so please read that to understand the 
concept.

### Additional extensions

We are going to need two additional extensions.

1. [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug): This 
provides a front-end for debugging software running on ARM Cortex processors. This plugin feeds the 
commands for the GDB client, over the GDB machine interface. Meaning, the pluging must run alongside
with the GDB client in the same container.
2. [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers): Makes it possible to run the VSCode inside a container.

### Debug configuration

Let's create a launch.json file in the .vscode directory and add the following configuration:

``` json title="launch.json"
{
    "version": "0.2.0",
    "configurations": [
        {
            "cwd": "${workspaceRoot}",
            "executable": "${workspaceRoot}/build/{elf file}",
            "name": "Debug Microcontroller",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "external",
            "gdbTarget": "stlink_org_container:4242",
            "armToolchainPath": "/opt/gcc-arm/bin",
            "device": "STM32F103RB"
        }
    ]
}
```

- "cwd": Current working directory.
- "executable": Change the {elf file} to the actual .elf file in your build directory.
- "name": Name of the configurations.
- "request": Launch the debug session. (Not connecting to an exisiting one.)
- "type": Debug type provided by the Cortex-Debug extension.
- "servertype": External, meaning the GDB server is not managed by the extension. In our case it 
runs in another container.
- "gdbTarget": The address and port of the GDB server. Docker automatically resolve the container 
name to an IP address.
- "armToolchainPath": Path of the gnu-arm-none-eabi toolchain. 
- "device": The target device type.

For more information refer to the 
[extension's wiki page](https://github.com/Marus/cortex-debug/wiki).

We need to tell VSCode to install the Cortex-Debug extension for the dev container environment 
(referenced by the gdb service).

``` json title="devcontainer.json"
{
	"dockerComposeFile": "docker-compose.yml",
	"service": "gdb",
	"workspaceFolder": "/work",
	"customizations": {
		"vscode": {
			"extensions": ["marus25.cortex-debug"]
		}
	}
}
```

### Debug in dev container

The VSCode back-end must run in the GDB client's container, so we can start the debug session with 
simply pressing :material-keyboard-f5:. For this we would like to make the axemsolutions/stlink_org 
image to start its own container the same time VSCode enters dev container mode. To achieve this we
need to create a docker-compose file that defines what containers should run.

``` yaml title="docker-compose.yml"
services:
  gdb-client:
    image: make_gnu_arm
    container_name: make_gnu_arm_container
    networks:
      - gdb-net
    volumes:
      - "..:/work"
    command: /bin/sh -c "while sleep 100; do :; done"

  gdb-server:
    image: stlink_org
    container_name: stlink_org_container
    networks:
      - gdb-net
    volumes:
      - "..:/work"
    privileged: true
    command: /bin/sh -c "st-util"

networks:
  gdb-net:
    driver: bridge
```

### Start the debug session

First, we need to enter the remote dev container mode, by executing the VSCode command: 
**Dev Containers: Reopen in Container**. The VSCode should start all the necessary resources. If the
setup finished, we just need to press :material-keyboard-f5:, and the debug session starts.  
When we finish the debug session we can go back to normal mode, be issuing: 
**Dev Containers: Reopen Folder Locally**.