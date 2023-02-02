#!/bin/bash

echo "Running unit tests ..."

docker_image_reg_name=$(jq -e '."cpputest"' axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it create cpputest docker image"  
  echo "Cpputest: ${docker_image_reg_name}" 
  pushd axem/TEST
	docker build -t ${docker_image_reg_name} .	
  popd
  
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi

echo $(pwd)
docker run --rm -v "$(pwd)":/work --name cpputest_container cpputest /bin/sh -c "cd app/test; make"

