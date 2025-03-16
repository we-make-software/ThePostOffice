# Kernel version
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

EXTRA_CFLAGS += -I../TheMailConditioner -I../ExpiryWorkBase

KBUILD_EXTRA_SYMBOLS := ../TheMailConditioner/Module.symvers ../ExpiryWorkBase/Module.symvers


obj-m := ThePostOffice.o
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules



clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean


start:
	make all
	sudo insmod ThePostOffice.ko

stop:
	sudo rmmod ThePostOffice.ko
	make clean
