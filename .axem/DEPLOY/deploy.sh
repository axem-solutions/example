#!/bin/bash

echo "Deploying ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")
dem run --privileged "${dev_env}" "deployer" "$(pwd)" "/bin/sh -c \"cd build; st-flash write boardtest.bin 0x8000000\""