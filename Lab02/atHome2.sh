#!/bin/sh

#cau a
echo "Nhap ho va ten (khong dau):"
read name
mkdir -p "$name"
echo "Da tao thu muc voi ten $name"
chmod 755 "$name"
#cau b
FILE="monhoc.txt"
i=1
while IFS= read -r line || [ -n "$line" ]
do
    cd "$name"
    mkdir -p "$line"
    cd ..
    echo "Da tao thu muc $i voi ten $line"
    i=$((i + 1))
done < "$FILE"