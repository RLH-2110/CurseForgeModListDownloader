CC=gcc
CCFLAGS = -ansi -pedantic -MMD -MP -lcurl

OUTPUT = curseDwl

CFILES= $(wildcard *.c) $(wildcard argParse/*.c) $(wildcard malloc/*.c) $(wildcard comp/fs/*.c)
OFILES= $(patsubst %.c,objs/%.o,$(CFILES))

# OS FLAGS
ifeq ($(OS),Windows_NT)
    CCFLAGS += -D OS_WINDOS # I know the w is missing, I just like to call it WinDos
$(info    detected windows)

else
	CCFLAGS += -D OS_POSIX
$(info    detected OTHER (defaults to POSIX implementation))

endif


$(OUTPUT): $(OFILES)
	$(CC) -o $(OUTPUT) $^ $(CCFLAGS) 

objs/%.o: %.c
	@mkdir -p $(dir $@) 
	$(CC) -c -o $@ $< $(CCFLAGS) 

clean:
	rm -f $(OUTPUT)
	rm -rdf objs

all: $(OUTPUT)

.PHONY: clean all

-include $(OFILES:.o=.d)