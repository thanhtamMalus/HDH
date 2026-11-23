#!/bin/bash

# a
mkdir -p "PNG" "JPG"

SOURCE="/home/malus/Lab02/OS_LAB2_IMG"
# b
count_png=$(ls "$SOURCE"/*.png "$SOURCE"/*.PNG | wc -l)
mv "$SOURCE"/*.png PNG
mv "$SOURCE"/*.PNG PNG
echo "So luong anh PNG: $count_png"

# c
count_jpg=$(ls "$SOURCE"/*.jpg "$SOURCE"/*.JPG "$SOURCE"/*.jpeg | wc -l)
mv "$SOURCE"/*.jpg JPG
mv "$SOURCE"/*.JPG JPG
mv "$SOURCE"/*.jpeg JPG
echo "So luong anh JPG: $count_jpg"