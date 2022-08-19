#!/bin/bash

echo "Build ..."

#docker run -v /home/deveushu/Documents/Test_C:/app axem:latest 
echo $(pwd)
#ls -la $(pwd)/../_dummy_project
docker run --rm -ti -v "$(pwd)":/work sttest:v1.0.0 /bin/sh -c "ls -la; make"

#"cd app; gcc main.c -o indocker; ./indocker"



