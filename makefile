CC = gcc
EMCC = emcc
LIBS = $(shell pkg-config --cflags --libs sdl2 sdl2_image sdl2_mixer sdl2_ttf)
INCLUDE = -I./include
SRCS = $(wildcard src/*.c dialogs/*.c *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = game
WEB_TARGET = game_web
WEB_FLAGS = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 \
			--preload-file ./res/red2.png \
			--preload-file ./res/click.mp3 \
			--preload-file ./res/side.png \
			--preload-file ./res/blue.png \
			--preload-file ./res/kaishu.ttf \
			--preload-file ./res/bgm.mp3 \
			--preload-file ./res/click.wav \
			--preload-file ./res/white.png \
			--preload-file ./res/red.png \



$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o:%.c
	$(CC) -c $< -o $@ $(INCLUDE)

$(WEB_TARGET): 
	$(EMCC) -o game.html $(SRCS) $(WEB_FLAGS)

dump:
	echo $(SRCS)
	echo $(OBJS)

run: 
	./game

clean:
	rm -f $(OBJS) $(TARGET)

