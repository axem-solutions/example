#!/bin/bash

echo "Build ..."

#docker run -v /home/deveushu/Documents/Test_C:/app axem:latest 
echo $(pwd)
#ls -la $(pwd)/../_dummy_project
#docker run --rm -ti -v "$(pwd)":/work sttest:v1.0.0 /bin/sh -c "ls -la; make"

docker network create -d bridge my-net

docker run -ti -d -v "$(pwd)":/work --privileged --network=my-net --name stlink_org_container stlink_org:latest /bin/sh -c "st-util"
docker run -ti -d -v "$(pwd)":/work --network=my-net --name make_gnu_arm_container sttest:v1.0.0 


#"cd app; gcc main.c -o indocker; ./indocker"



