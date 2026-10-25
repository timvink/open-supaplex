CC=emcc

src = $(wildcard ../src/*.c) $(wildcard ../src/sdl2/*.c) $(wildcard ../src/sdl_common/*.c) ../src/null/virtualKeyboard.c ../src/lib/ini/ini.c
obj = $(src:.c=.o)

LDFLAGS = -lSDL2_mixer -lSDL2

CFLAGS = -s USE_SDL=2 -s USE_SDL_MIXER=2 -DHAVE_SDL2

opensupaplex.html: $(obj) shell.html
	$(CC) -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY -O2 --shell-file shell.html -o $@ $(obj) $(LDFLAGS) --preload-file ../resources@/

clean:
	rm $(obj)
