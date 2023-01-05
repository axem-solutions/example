#!/bin/bash

echo "Deploy ..."

docker_image_reg_name_deploy=$(jq -e '."deploy"' axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name_deploy} -q)" == "x" ]]; then  
  echo "Not find it create deploy docker image"  
  echo "Deploy: ${docker_image_reg_name_deploy}" 
  pushd axem/DEPLOY
	docker build -t ${docker_image_reg_name_deploy} .	
  popd
  
else
  echo "${docker_image_reg_name_deploy}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name_deploy} -q)" 
fi

docker_image_reg_name_build=$(jq -e '."build"' axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name_build} -q)" == "x" ]]; then  
  echo "Not find it create deploy docker image"  
  echo "Deploy: ${docker_image_reg_name_build}" 
  pushd axem/BUILD
	docker build -t ${docker_image_reg_name_build} .	
  popd
  
else
  echo "${docker_image_reg_name_build}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name_build} -q)" 
fi

echo $(pwd)

docker network rm my-net
docker network create -d bridge my-net

docker run -ti -d -v "$(pwd)":/work --privileged --network=my-net ${docker_image_reg_name_deploy} /bin/sh -c "st-util"
docker run -ti -d -v "$(pwd)":/work --network=my-net ${docker_image_reg_name_build} /bin/sh -c "make; arm-none-eabi-gdb build/boardtest.elf"



