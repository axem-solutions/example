#!/bin/bash

echo "Deploy ..."

docker_image_reg_name=$(jq -e '."deploy"' axem/descriptor.json | tr -d \")

if [[ "x$(docker image ls --filter reference=${docker_image_reg_name} -q)" == "x" ]]; then  
  echo "Not find it create deploy docker image"  
  echo "Deploy: ${docker_image_reg_name}" 
  pushd axem/DEPLOY
	docker build -t ${docker_image_reg_name} .	
  popd
  
else
  echo "${docker_image_reg_name}" 
  echo "Docker image exist"
  echo "image ID:$(docker image ls --filter reference=${docker_image_reg_name} -q)" 
fi

echo $(pwd)
docker run -it --privileged -v "$(pwd)":/work --name stlink_org_container ${docker_image_reg_name} /bin/bash -c "ls -la; cd build; st-flash write boardtest.bin 0x8000000"


