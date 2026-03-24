all:
	cc -oass assware.c -O0 -static

run: all
	./ass

clean:
	rm ass
