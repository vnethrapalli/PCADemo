#!/bin/bash

make pca_serial

# pass in a space-separated flattened 2x2 or 3x3 matrix
if [ $# -eq 4 ]; then
    cd data
    python3 ellipse.py $@
    cd ..
    ./pca_serial 1
    cd data
    python3 principal_components.py
    cd ..
elif [ $# -eq 9 ]; then
    cd data
    python3 ellipsoid.py $@
    cd ..
    ./pca_serial 2
    cd data
    python3 principal_components_3d.py
    cd ..
else
    echo "please pass in a space-separated 2x2 or 3x3 matrix (ie. 3 -1 3 1)"
fi

# clean up intermediate files and compiled files
rm pca_serial.o utils/serial.o 
rm data/ellipse.txt data/components.txt
