#!/bin/bash

touch src/overview.c

echo "" > src/overview.c

results=$(cd src && ls)
for f in $results
do
    echo -n '#include "' >> src/overview.c
    echo -n "${f}" >> src/overview.c
    echo '"' >> src/overview.c
done