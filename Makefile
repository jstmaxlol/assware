all:
	cc -oass assware.c -O0 -static

run: all
	-./ass
	$(MAKE) clean

clean:
	rm ass
