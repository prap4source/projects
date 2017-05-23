KDIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
obj-m := modproj.o
modproj-objs := main.o
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
