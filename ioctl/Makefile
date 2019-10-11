SRC_DIR = src
EXTRA_CFLAGS = -I$(PWD)/includes/

TARGET_APP = app
APP_SRC := $(SRC_DIR)/app.c

ifneq ($(KERNELRELEASE),) 
   obj-m := $(SRC_DIR)/ioctl-module.o
else 

KERNELDIR ?= /lib/modules/$(shell uname -r)/build 

PWD := $(shell pwd)

all: km app

km: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

app: $(APP_SRC)
	$(CC) $(CFLAGS) $^ $(EXTRA_CFLAGS) -o $@  

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm $(TARGET_APP)

endif 
