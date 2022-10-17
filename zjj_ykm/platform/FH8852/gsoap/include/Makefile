include ./Makefile.param







INC_PATH       :=  -I $(GSOAP_INC)

ifeq ($(PLAT),x86)

endif


ifeq ($(PLAT),MSC313E)
CPU_FLAG    := -march=armv7-a  -fPIC -DPIC
#OPENSSL_DIR := /ext_disk/work/software/openssl-1.0.2n-MStar/install

endif

ifeq ($(PLAT),HI3516CV300)
CPU_FLAG        :=-mcpu=arm926ej-s -mno-unaligned-access -fno-aggressive-loop-optimizations -ffunction-sections -fdata-sections -fstack-protector
endif

ifeq ($(PLAT),HI3518EV200)

endif

ifeq ($(PLAT),HI3518EV100)

endif


ifeq ($(PLAT),HI3518EV200)
	
endif



OPENSSL_INC	:= ../../openssl/include/


INC_PATH       :=  -I $(OPENSSL_INC)

CFLAGS		:= -Os -Wall -fmessage-length=0 -fPIC  -DWITH_DOM -DWITH_OPENSSL
CFLAGS		+= $(INC_PATH) -D$(PLAT) $(CPU_FLAG)
CXXFLAGS	:= -Os -Wall -fmessage-length=0 -fPIC  -DWITH_DOM -DWITH_OPENSSL
CXXFLAGS	+= $(INC_PATH) -D$(PLAT) $(CPU_FLAG)

SRCS		:= $(wildcard *.c) 
OBJS		:= $(SRCS:%.c=%.o)

SRCS_CPP	:= $(wildcard *.cpp) 
OBJS_CPP	:= $(SRCS_CPP:%.cpp=%.o)



TARGET	:= libonvif.a
.PHONY	: clean all

all: $(TARGET) 
	
$(TARGET): $(OBJS) $(OBJS_CPP)
#	$(CC) -shared -o $@ $^
#	cp $@ libcommon.so.strip
#	$(STRIP) libcommon.so.strip
	$(AR) -rcs $@ $^ 

strip:
#$(STRIP) $(TARGET)

install:
	 cp $(TARGET) $(INSTALL_DIR)/bin


clean:
	@rm -f $(TARGET)
	@rm -f $(OBJS)
	@rm -f $(OBJS_CPP)


