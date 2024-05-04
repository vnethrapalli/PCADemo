#!/bin/bash

make pca_serial

# pass in a space-separated flattened 2x2 or 3x3 matrix
if [ $# -eq 4 ]; then
    cd data
    python3 ellipse.py $@
    cd ..
    ./pca_serial
    cd data
    python3 principal_components.py
    cd ..
elif [ $# -eq 9 ]; then
    echo 9
else
    echo "please pass in a space-separated 2x2 or 3x3 matrix (ie. 3 -1 3 1)"
fi

