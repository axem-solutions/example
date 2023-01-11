#!/bin/bash

echo "Running unit tests ..."

echo $(pwd)
docker run --rm -v "$(pwd)":/work --name cpputest_container cpputest /bin/sh -c "cd app/test; make"

