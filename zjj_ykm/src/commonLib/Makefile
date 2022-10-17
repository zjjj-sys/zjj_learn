include ../Makefile.param


#SDK_DIR		= ../../platform/$(PLAT)/sdk
#SDK_INC		= $(SDK_DIR)/include
#SDK_LIB		= $(SDK_DIR)/lib

BOOST_DIR       = ../../platform/$(PLAT)/boost
BOOST_INC       = $(BOOST_DIR)/include
BOOST_LIB       = $(BOOST_DIR)/lib

#COMM_INC	:= ../commonLib
#COMM_LIB	:= ../commonLib
#INC		:= ../include

OPENSSL_DIR 	= ../../platform/$(PLAT)/openssl
OPENSSL_INC		= $(OPENSSL_DIR)/include
OPENSSL_LIB		= $(OPENSSL_DIR)/lib


JSONCPP_DIR	= ../../platform/$(PLAT)/jsonCpp
JSONCPP_INC	= $(JSONCPP_DIR)/include


ifeq ($(PLAT),x86)

endif


ifeq ($(PLAT),HI3516DV100)

	
endif

ifeq ($(PLAT),HI3518EV200)

	
endif

ifeq ($(PLAT),HI3518EV100)

endif

INC	:= ../include/

INC_PATH   :=   -I $(BOOST_INC)  -I $(INC) -I $(OPENSSL_INC) -I $(JSONCPP_INC)


CFLAGS		:= $(OPTIMIZE_OPTION) -Wall -fmessage-length=0 $(CFLAGS_EXT) 
CFLAGS		+= $(INC_PATH) -D$(PLAT)
CXXFLAGS	:=  $(OPTIMIZE_OPTION)  -Wall -fmessage-length=0 $(CXXFLAGS_EXT) 
CXXFLAGS	+= $(INC_PATH) -D$(PLAT)

SRCS		:= $(wildcard *.c) 
OBJS		:= $(SRCS:%.c=%.o)

SRCS_CPP	:= $(wildcard *.cpp) 
OBJS_CPP	:= $(SRCS_CPP:%.cpp=%.o)





ifeq ($(PLAT),HI3516CV500)
CFLAGS          += -DCONFIG_SUPPORT_WIEGAND_DEV 
CXXFLAGS        += -DCONFIG_SUPPORT_WIEGAND_DEV
endif




ifeq ($(USE_JINMAO_QR),1) 
CXXFLAGS	+= -DCONFIG_SUPPORT_MTD_DEVICE_OPERATION
endif






TARGET	:= libcommon.a 
.PHONY	: clean all

all: $(TARGET) 
	
$(TARGET): $(OBJS) $(OBJS_CPP)
	$(AR) -rcs $@ $^ ./object.$(PLAT)/*.o
strip:
	#$(STRIP) $(TARGET)
install:


clean:
	@rm -f $(TARGET)
	@rm -f $(OBJS)
	@rm -f $(OBJS_CPP)

