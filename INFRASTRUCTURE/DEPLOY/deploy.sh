#!/bin/bash

echo "Deploy ..."

docker_image_reg_name=$(jq -e '."deploy"' INFRASTRUCTURE/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it create deploy docker image"  
  echo "Deploy: ${docker_image_reg_name}" 
  pushd INFRASTRUCTURE/DEPLOY
	docker build -t ${docker_image_reg_name} .	
  popd
  
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi

echo $(pwd)
docker run --rm -ti --device=/dev/ttyACM0 -v "$(pwd)":/work ${docker_image_reg_name} /bin/sh -c "ls -la; cd build; st-flash write boardtest.bin 0x8000000"



