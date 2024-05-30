# VSCode Integration

## Creating tasks

VSCode has a neat feature to run arbitrary tasks within the editor. This makes it easy to execute 
common commands without having to open a separate terminal window. In this section, we will assign 
tasks for the CLI commands that were introduced in the [CLI usage chapter](cli_usage.md). 

To get started, open the `tutorial` project in VSCode and create a new directory called `.vscode` in 
the root if it doesn't already exist. Then add a file called tasks.json to this directory. 
Copy and paste the following task descriptions into the tasks.json file:

``` json title="tasks.json"
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build Project",
            "type": "shell",
            "command": "dem run build",
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Deploy to target",
            "type": "shell",
            "command": "dem run deploy"
        },
        {
            "label": "Run unit tests",
            "type": "shell",
            "command": "dem run test"
        }
    ]
}
```

With these tasks defined, you can now execute them from within VSCode.  
To make the build execution even more convenient, go to the Command Palette and search for 
"Configure Default Build Task". Select the "Build Project" task from the list. This will configure 
VSCode to automatically run the "Build Project" task when you press the key combination 
`Ctrl+Shift+B`.

## Debugging

In this section, you will learn about setting up debugging in VSCode. The same method will be used 
as in the [CLI Debugging chapter](cli_usage.md#debugging).  
The goal is to make VSCode to manage the containers used for debugging, utilizing its feature to run 
inside a container. 

### **Additional extensions**

Before proceeding, note that you need to install two additional extensions in VSCode:

1. [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug): This 
provides a front-end for debugging software running on ARM Cortex processors. The plugin feeds the 
commands for the GDB client, over the GDB machine interface. Meaning, it must run alongside with the 
GDB client in the same container.
2. [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers): 
Makes it possible to run the VSCode inside a container. The container, in which the VSCode back-end
runs, is called a *dev container*.

### **Debug configuration**

First, the Cortex-Debug extension must be configured to work with both the GDB client in the same 
container and the remote GDB server running in the other container.
Create a launch.json file in the .vscode directory and add the following configuration:

``` json title="launch.json"
{
	"version": "0.2.0",
	"configurations": [
			{
				"cwd": "${workspaceRoot}",
				"executable": "${workspaceRoot}/build/tutorial.elf",
				"name": "Debug Microcontroller",
				"request": "launch",
				"type": "cortex-debug",
				"servertype": "external",
				"gdbTarget": "stlink-org_container:4242",
				"armToolchainPath": "/opt/gnu/arm-none-eabi-gnu-toolchain-13.2/bin",
				"device": "STM32F103RB"
			}
	]
}
```

- "cwd": Current working directory.
- "executable": The .elf file.
- "name": Name of the configurations.
- "request": Launch the debug session. (Not connecting to an existing one.)
- "type": Debug type provided by the Cortex-Debug extension.
- "servertype": External, meaning the GDB server is not managed by the extension. In our case it 
runs in another container.
- "gdbTarget": The address and port of the GDB server. Docker automatically resolves the container 
name to an IP address.
- "armToolchainPath": Path of the gnu-arm-none-eabi toolchain. 
- "device": The target device type.

!!! info

    For more information refer to the 
    [Cortex-Debug extension's wiki page](https://github.com/Marus/cortex-debug/wiki).

### **Debug in dev container**

The VSCode needs to be configured to install the Cortex-Debug extension for the dev container 
environment. The dev container in this case runs the axemsolutions/make_gnu-arm:13.2 image, 
referenced as the `gdb-client` service. Create a new directory called `.devcontainer` in the 
project root and add the following file:

``` json title="devcontainer.json"
{
    "dockerComposeFile": "docker-compose.yml",
    "service": "gdb-client",
    "workspaceFolder": "/work",
    "customizations": {
        "vscode": {
            "extensions": ["marus25.cortex-debug", "mcu-debug.debug-tracker-vscode"]
        }
    }
}
```

- "dockerComposeFile": Compose is a tool for running multi-container Docker applications. The 
docker-compose.yml defines how Compose should run the selected images. 
- "service": Which service provides the dev container.
- "workspaceFolder": Directory used as root by VSCode inside the dev container.
- "customizations": Install the Cortex-Debug extension inside the dev container.

The goal is to be able to automatically run the GDB-client and GDB-server containers simultaneously. 
For this, we use the above mentioned Compose tool. Create the docker-compose.yml file in the 
`.devcontainer` directory, to run the axemsolutions/make_gnu_arm and axemsolutions/stlink_org 
containers.

``` yaml title="docker-compose.yml"
services:
  gdb-client:
    image: axemsolutions/make_gnu-arm:13.2
    container_name: make_gnu-arm_container
    networks:
      - gdb-net
    volumes:
      - "..:/work"
    command: /bin/sh -c "while sleep 100; do :; done"

  gdb-server:
    image: axemsolutions/stlink-org:1.8.0
    container_name: stlink-org_container
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

### **Start the debug session**

First, we need to enter the remote dev container mode by executing the VSCode command: 
**Dev Containers: Reopen in Container**. The VSCode should start all the necessary resources. If the
setup finished, we just need to press :material-keyboard-f5:, and the debug session starts.  
After finishing the debug session, we can go back to normal mode by issuing: 
**Dev Containers: Reopen Folder Locally**.