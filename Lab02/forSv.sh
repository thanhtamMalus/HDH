#!/bin/sh

#name=""
#id=""
echo "Nhap ten cua ban:"
read name
echo "Nhap ma so sinh vien cua ban:"
read id
for i in 1 2 3 4 5
do

    if [ "$name" = "Thanh Tam" ] && [ $id -eq 25521638 ]
    then
        echo "Chuc mung thang lon=)))"
        break
        exit 0
    fi
    echo "Nhap ten cua ban:"
    read name
    echo "Nhap ma so sinh vien cua ban:"
    read id

done
echo "Access Denied"
exit 0