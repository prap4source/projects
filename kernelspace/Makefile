KDIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
obj-m := modproj.o
modproj-objs := main.o
ccflags-y += -DDEBUG
EXTRA_CFLAGS += -I$(M)/../include_c/
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
