CC = gcc
LIBS = $(shell pkg-config --cflags --libs sdl2 sdl2_image sdl2_mixer sdl2_ttf)
INCLUDE = -I./include
SRCS = $(wildcard src/*.c *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = game

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o:%.c
	$(CC) -c $< -o $@ $(INCLUDE)

dump1:
	echo $(SRCS)
	echo $(OBJS)
clean:
	rm -f $(OBJS) $(TARGET)

