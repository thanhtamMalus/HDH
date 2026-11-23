#!/bin/sh
echo "Nhap chuoi:"
read str
FILE="./text.txt"

if grep -qF "$str" "$FILE"; then
    echo "-> Kết quả: Chuỗi $str CÓ tồn tại trong file $FILE."
else
    echo "-> Kết quả: Chuỗi $str KHÔNG tồn tại trong file $FILE."
fi