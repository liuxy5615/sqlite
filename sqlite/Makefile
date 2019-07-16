#######################################################
## Start it by liuxy 2018-05-28
#######################################################
TARGET = sqlite

CC = gcc
CPP = g++

files := $(wildcard source/*.c)
files := $(filter-out source/main.c, $(files))
CONFIG_PATH = $(shell pwd)

//CFLAGS  += -DMakefle_D=\"$(shell pwd)/../version/gencfg.ini\" 
CFLAGS  += -DMakefle_D=\"/home/hyperion/hyperion_v1/version/gencfg.ini\"
//BIN_DIR = ../../bin/
//OBJS = $(patsubst %.c, %.o,$(wildcard $(files)))

RM := rm -rf

all: $(TARGET)
$(TARGET):$(files)
	$(CC)  $^ -I  include   -fPIC -shared  -lpthread -ldl -o bin/libdbmanager.so $(CFLAGS)
ifneq ($(CI_BUILD), yes)
	cp bin/libdbmanager.so   /usr/lib
	ldconfig
endif
	$(CC)  source/main.c  -I  include  -L./bin -ldbmanager -o bin/db_init $(CFLAGS) 
ifneq ($(CI_BUILD), yes)
	mv bin/db_init   ../version	
endif


.PHONY:clean
clean:
	-$(RM) bin/*.so
	-$(RM) /usr/lib/libdbmanager.so
