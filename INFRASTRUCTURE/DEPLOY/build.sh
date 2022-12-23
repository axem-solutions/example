#!/bin/bash

echo "Build ..."

docker_image_reg_name=$(jq -e '."build"' INFRASTRUCTURE/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it create build docker image"  
  echo "Build: ${docker_image_reg_name}" 
  pushd INFRASTRUCTURE/build
	docker build -t ${docker_image_reg_name} .	
  popd
  
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi

echo $(pwd)
docker run --rm -ti -v "$(pwd)":/work ${docker_image_reg_name} /bin/sh -c "ls -la; make"




