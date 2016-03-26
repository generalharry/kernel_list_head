KERNELDIR=/usr/src/linux-headers-4.2.0-34-generic
PWD:=$(shell pwd)
INSTALLDIR=$(PWD)
CC=gcc

$(warning >>> harry debug build list module)
obj-m := mylist.o


list:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf .*.cmd .tmp_versions *.o *.ko *.mod.c *.markers *.order *.symvers
.PHONY:modules clean
