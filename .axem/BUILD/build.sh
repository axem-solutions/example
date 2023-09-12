#!/bin/bash

echo "Building ..."

dev_env=$(jq -e '."dev_env"' .axem/descriptor.json | tr -d \")
dem run "${dev_env}" --rm -v $(pwd):/work axemsolutions/make_gnu_arm make