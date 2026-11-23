#!/bin/sh

#name=""
#id=""
echo "Nhap ten cua ban:"
read name
echo "Nhap ma so sinh vien cua ban:"
read id
if [ "$name" = "Thanh Tam" ] && [ $id -eq 25521638 ]
then
    echo "Hello"
else
    echo "Acess Denied"
fi
exit 0