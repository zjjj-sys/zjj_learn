include ../../../../src/Makefile.param 








INC_PATH       :=  -I $(OPENSSL_INC)

CFLAGS		:= -O2 -Wall -fmessage-length=0 -fPIC 
CFLAGS		+= $(INC_PATH) -D$(PLAT) $(CPU_FLAG)
CXXFLAGS	:= -O2 -Wall -fmessage-length=0 -fPIC
CXXFLAGS	+= $(INC_PATH) -D$(PLAT) $(CPU_FLAG)

SRCS		:= $(wildcard *.c) 
OBJS		:= $(SRCS:%.c=%.o)

SRCS_CPP	:= $(wildcard *.cpp) 
OBJS_CPP	:= $(SRCS_CPP:%.cpp=%.o)



TARGET	:= libVoiceRecog.a
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


