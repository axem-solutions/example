#!/bin/bash

echo "Building ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")
dem run "${dev_env}" "build system" "$(pwd)" "make"