#!/bin/sh

echo "Nhap ten cua ban:"
read name
echo "Nhap ma so sinh vien cua ban:"
read id
while [ "$name" != "Thanh Tam" ] || [ $id != 25521638 ]
do
    echo "Nhap lai di ni!!!"
    echo "Nhap ten cua ban:"
    read name
    echo "Nhap ma so sinh vien cua ban:"
    read id
done
echo "Chao $name voi mssv $id"
exit 0