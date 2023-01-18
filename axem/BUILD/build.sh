#!/bin/bash

echo "Build ..."

docker_image_reg_name=$(jq -e '."build"' axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it create build docker image"  
  echo "Build: ${docker_image_reg_name}" 
  pushd axem/BUILD
	docker build -t ${docker_image_reg_name} .	
  popd
  
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi


if [[ "${PROJECT_DIR}" == "" ]]; then  
  docker run --rm -v "$(pwd)":/work ${docker_image_reg_name} /bin/sh -c "ls -la; make"
  echo "here"
else
  docker run --rm -v "${PROJECT_DIR}":/work ${docker_image_reg_name} /bin/sh -c "ls -la; make"
fi






