#!/bin/bash

echo "Running unit tests ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")
dem run "${dev_env}" "test framework" "$(pwd)" "/bin/sh -c \"cd app/test; make\""