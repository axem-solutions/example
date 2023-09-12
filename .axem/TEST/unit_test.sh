#!/bin/bash

echo "Running unit tests ..."

docker_image_reg_name=$(jq -e '."testframework"' .axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it! \n Download: ${docker_image_reg_name}" 
	docker pull ${docker_image_reg_name} .	
    
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi

if [[ "${PROJECT_DIR}" == "" ]]; then  
  docker run --rm -v "$(pwd)":/work --name testframework_container ${docker_image_reg_name} /bin/sh -c "cd app/test; make"
else
  docker run --rm -v "${PROJECT_DIR}":/work --name testframework_container ${docker_image_reg_name} /bin/sh -c "cd app/test; make"
fi


