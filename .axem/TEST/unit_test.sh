#!/bin/bash

echo "Running unit tests ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")
dem run "${dev_env}" --rm -v $(pwd):/work axemsolutions/cpputest "/bin/sh -c \"cd app/test; make\""