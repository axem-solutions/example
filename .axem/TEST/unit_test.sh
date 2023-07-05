#!/bin/bash

echo "Running unit tests ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")

if [[ "${PROJECT_DIR}" == "" ]]; then  
  echo "Dev running unit tests ..."
  dem run "${dev_env}" "test framework" "$(pwd)" "/bin/sh -c \"cd app/test; make\""
else
  echo "CI running unit tests ..."
  dem run "${dev_env}" "test framework" "$(PROJECT_DIR)" "/bin/sh -c \"cd app/test; make\""
fi


