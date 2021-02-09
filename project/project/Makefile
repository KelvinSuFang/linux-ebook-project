CROSSCOMPILE := arm-linux-

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/include -L/home/wudebao/work/freetype/arm_freetype/freetype-2.4.10/arm_build/lib -I/home/wudebao/work/freetype/arm_freetype/freetype-2.4.10/arm_build/include -I$(PWD)/include -L/home/wudebao/work/freetype/arm_freetype/freetype-2.4.10/arm_build/lib


LDFLAGS := -lm -lfreetype

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS := main.o \
			display/disp_manager.o        \
			display/fb.o                  \
			encoding/ascii.o              \
			encoding/utf-16be.o           \
			encoding/encoding_manager.o   \
			encoding/utf-8.o              \
			encoding/utf-16le.o           \
			draw/draw.o                   \
			fonts/ascii.o                 \
			fonts/gbk.o                   \
			fonts/freetype.o              \
			fonts/fonts_manager.o

all: $(OBJS)
	$(CC) $(LDFLAGS) -o show_file $^

clean:
	rm -f show_file
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

