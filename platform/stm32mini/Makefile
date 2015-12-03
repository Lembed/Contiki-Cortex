TARGET=stm32mini

all: stm32mini


CONTIKI=../..

CONTIKI_TARGET_MAIN=contiki-main.c

PROJECT_SOURCEFILES = parity.c 


randgen: randgen.c
	gcc -DNDEBUG -I $(CONTIKI)/cpu/arm/stm32f103/ -I . -I $(CONTIKI)/core  randgen.c -o randgen

randcheck: randcheck.c
	gcc -DNDEBUG -I $(CONTIKI)/cpu/arm/stm32f103/ -I . -I $(CONTIKI)/core  randcheck.c -o randcheck

clean: stm32mini_clean

.PHONY: stm32mini_clean

stm32mini_clean:

include $(CONTIKI)/Makefile.include

