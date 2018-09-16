.DEFAULT_GOAL := all

build:
	platformio run

upload:
	platformio run -t upload

monitor:
	platformio device monitor -b 115200 --quiet

all: build upload monitor