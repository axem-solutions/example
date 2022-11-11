#!/bin/bash

echo "Build ..."

#docker run -v /home/deveushu/Documents/Test_C:/app axem:latest 
echo $(pwd)
#ls -la $(pwd)/../_dummy_project
docker run --rm -ti -v "$(pwd)":/work --name make_gnu_arm_container make_gnu_arm /bin/sh -c "ls -la; make"

#"cd app; gcc main.c -o indocker; ./indocker"



