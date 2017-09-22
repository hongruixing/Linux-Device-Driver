#! /bin/sh
if [ $# -eq 0 ]
  then
    echo "$0 <name of module> <name of the userapp C Code>"
	exit 1
fi

fpath="$(pwd)/UserApp/$2.c"
outpath="$(pwd)/UserApp/$2.o"
sudo dmesg -c > /dev/null

make	
if [ "$?" != 0 ]; then
	echo"[Error] make failed" 1>&2
	exit 1
fi


sudo rmmod $1
if [ "$?" != 0 ]; then
	echo"[Error] rmmod failed" 1>&2
	exit 1
fi
echo 
echo "======Module removed $1 removed successfully============="
echo 

sudo insmod $1.ko
if [ "$?" != 0 ]; then
        echo"[Error] insmod fsiled" 
        exit 1
fi
echo 
echo "====Module inserted $1 removed successfully===================="
echo 
gnome-terminal --window-with-profile=device -e dmesg
echo 
echo "Dmesg started...."
echo 

echo $fpath

gcc $fpath -o $outpath
echo 
echo "==User program compiled=============================="
echo 
sudo ./UserApp/$2.o


