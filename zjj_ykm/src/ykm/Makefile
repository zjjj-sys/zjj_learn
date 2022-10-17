include ../Makefile.param

COMM_INC	:= ../commonLib
COMM_LIB	:= ../commonLib
INC			:= ../include



BOOST_DIR       = ../../platform/$(PLAT)/boost
BOOST_INC       = $(BOOST_DIR)/include
BOOST_LIB       = $(BOOST_DIR)/lib

OPENSSL_DIR 	= ../../platform/$(PLAT)/openssl
OPENSSL_INC		= $(OPENSSL_DIR)/include
OPENSSL_LIB		= $(OPENSSL_DIR)/lib



P2P_DIR			= ../../platform/$(PLAT)/PPPP
P2P_INC			= $(P2P_DIR)/include
P2P_LIB			= $(P2P_DIR)/lib


JSON_CPP_DIR		= ../../platform/$(PLAT)/jsonCpp
JSON_CPP_INC		= $(JSON_CPP_DIR)/include
JSON_CPP_LIB		= $(JSON_CPP_DIR)/lib


MQTT_DIR		= ../../platform/$(PLAT)/mosquitto
MQTT_DIR_INC		= $(MQTT_DIR)/include
MQTT_DIR_LIB		= $(MQTT_DIR)/lib


CURL_DIR		= ../../platform/$(PLAT)/curl
CURL_DIR_INC		= $(CURL_DIR)/include
CURL_DIR_LIB		= $(CURL_DIR)/lib

TOR_DIR 	= ../
SRC_DIR 	= $(TOR_DIR)src
RTSPNET_DIR		= $(TOR_DIR)src/net
RTSPBASE_DIR	= $(TOR_DIR)src/base

ifeq ($(PLAT),x86)

endif


ifeq ($(PLAT),HI3516DV100)

	
endif

ifeq ($(PLAT),HI3518EV200)

	
endif

ifeq ($(PLAT),HI3518EV100)

endif



INC_PATH   :=   -I $(COMM_INC) -I $(INC) -I $(BOOST_INC) -I $(MQTT_DIR_INC) -I $(JSON_CPP_INC) -I $(OPENSSL_INC) -I $(RTSPBASE_DIR) -I $(RTSPNET_DIR)
LIB	       :=   -L$(BOOST_LIB) -L$(COMM_LIB) -L$(MQTT_DIR_LIB)  -L$(JSON_CPP_LIB) -L$(OPENSSL_LIB) -L$(CURL_DIR_LIB)   -lcommon  -lboost_serialization -ljsoncpp -lcrypto -lssl  -lrt -lpthread


CFLAGS		:= $(OPTIMIZE_OPTION) -Wall -fmessage-length=0  
CFLAGS		+= $(INC_PATH) -D$(PLAT) -DLINUX
CXXFLAGS	:= -std=c++11 $(OPTIMIZE_OPTION) -Wall -fmessage-length=0
CXXFLAGS	+= $(INC_PATH) -D$(PLAT) -DLINUX

ifeq ($(PLAT),HI3516EV200)
CFLAGS          += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE
CXXFLAGS        += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE
endif

ifeq ($(PLAT),HI3518EV300)
CFLAGS          += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE
CXXFLAGS        += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE
endif

ifeq ($(PLAT),HI3516CV500)
#CFLAGS          += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE -DCONFIG_ENABLE_SVP
#CXXFLAGS        += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4  -fno-aggressive-loop-optimizations -ldl -ffunction-sections -fdata-sections  -fstack-protector-strong -fPIC  -Wno-error=implicit-function-declaration -DUSER_BIT_32 -DKERNEL_BIT_32  -D_GNU_SOURCE -DCONFIG_ENABLE_SVP

CFLAGS 		+= -DCONFIG_SUPPORT_GUI_OPERATION
CXXFLAGS	+= -DCONFIG_SUPPORT_GUI_OPERATION

endif



RTSP_OBJS_PATH 	:= ../objs


SRC_BASE		= $(shell find ../src/base/ -name "*.cpp")
SRC_NET			= $(shell find ../src/net/ -name "*.cpp")


SRC_BASE_NODIR			= $(notdir $(wildcard $(SRC_BASE)))
SRC_NET_NODIR			= $(notdir $(wildcard $(SRC_NET)))


OBJS_BASE			= $(patsubst %.cpp,$(RTSP_OBJS_PATH)/%.o,$(SRC_BASE_NODIR))
OBJS_NET			= $(patsubst %.cpp,$(RTSP_OBJS_PATH)/%.o,$(SRC_NET_NODIR))


SRCS		:= $(wildcard *.c) 
OBJS		:= $(SRCS:%.c=%.o)

SRCS_CPP	:= $(wildcard *.cpp) 
OBJS_CPP	:= $(SRCS_CPP:%.cpp=%.o)



TARGET	:= ykm
.PHONY	: clean all

all: MKAE_DIR $(TARGET) 

MKAE_DIR:
	@-mkdir -p $(RTSP_OBJS_PATH)

	

$(TARGET): $(OBJS) $(OBJS_CPP) $(OBJS_BASE) $(OBJS_NET)
	$(CXX) -o $@ $^ $(LIB)

$(RTSP_OBJS_PATH)/%.o : $(SRC_DIR)/base/%.cpp
	$(CXX) -c -std=c++11 -o $@ $< $(CXXFLAGS)
$(RTSP_OBJS_PATH)/%.o : $(SRC_DIR)/net/%.cpp
	$(CXX) -c -std=c++11 -o $@ $< $(CXXFLAGS)


strip:
	$(STRIP) $(TARGET)
	cp  $(TARGET) ../bin
install:
	cp $(TARGET) ../bin

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJS)
	@rm -f $(OBJS_CPP)
	@rm -rf $(RTSP_OBJS_PATH)

