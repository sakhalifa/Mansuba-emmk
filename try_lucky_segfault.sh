#!/bin/bash

for i in {1..10000}
do
    ./project
    if [ $? != 0 ]
    then
        echo "FAIL AT $i!"
        break
    fi
done