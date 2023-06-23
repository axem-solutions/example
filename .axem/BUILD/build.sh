#!/bin/bash

echo "Build ..."

docker_image_reg_name=$(jq -e '."build"' .axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it! \n Download: ${docker_image_reg_name}" 
	docker pull ${docker_image_reg_name}
  
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






