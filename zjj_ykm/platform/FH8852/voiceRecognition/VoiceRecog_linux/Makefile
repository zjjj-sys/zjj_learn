include ./Makefile.param


CFLAGS := -I./
CXXFLAGS := -I./
LFLAGS := -lpthread

SRCS:=$(wildcard *.c)
#SRCS+=buffer.c \
circleQueue.c \
common.c \
kiss_fft.c \
kiss_fftr.c \
linux.c \
my_poolAlloc.c \
my_vector.c \
rs_emon.c \
signalAnalyserTimeMatch2.c \
tinycthread.c \
util.c \
voiceRecognizer.c \
voiceRecog.c

OBJS:=$(SRCS:%.c=%.o)
TARGET:=libVoiceRecog.a


all:$(TARGET)


$(TARGET):$(OBJS)
	$(AR) -crs  $@ $^

#%.o:%.c
#	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	@rm $(OBJS) $(TARGET) -rf

	
