#!/bin/bash

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")

if [[ "${PROJECT_DIR}" == "" ]]; then  
  echo "Dev build ..."
  dem run "${dev_env}" "build system" "$(pwd)" "make"
else
  echo "CI build ..."
  dem run "${dev_env}" "build system" "${PROJECT_DIR}" "make"
fi