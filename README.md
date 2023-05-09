# Example project for dem

The purpose of this project is to demonstrate the usage of the dem tool: https://github.com/axem-solutions/dem
This repo contain integration to the VS Code editor.

1. Clone this and the dem repository.
2. Enter the dem directory.
3. Download the Development Environment for this project, by executing:
`python -m dem pull demo`
4. Validate that all the tools are available:
`python -m dem info demo`
5. Now you should be able to work with the example project. 

The following VS Code tasks are available:
  * build: build the project
  * deploy: load the binary to the target
  * test: run the test cases

Debugging is also supported. For this you need to reopen the project in container:
  * Issue the "reopen in container" VS code command. -> The VS Code enters to remote development mode.
  * Now you can simply press F5 and the debug starts.
