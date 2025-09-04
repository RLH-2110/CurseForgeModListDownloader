CC=gcc
CCFLAGS = -ansi -pedantic -MMD -MP

OUTPUT = curseDwl
CFILES= $(wildcard *.c) $(wildcard argParse/*.c) $(wildcard comp/fs/*.c) 

CFILES= $(wildcard *.c) $(wildcard argParse/*.c)
OFILES= $(patsubst %.c,objs/%.o,$(CFILES))

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