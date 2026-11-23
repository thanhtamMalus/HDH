#!/bin/sh
echo "Nhap n:"
read n
while [ $n -lt 10 ]
do
echo "Nhap lai n:"
read n
done
sum=0
i=1
while [ $i -le $n ]
do
sum=$((sum+i))
i=$((i+1))
done
echo "Tong tu 1 den $n la: $sum"   