build: cipher

cipher: main.c modseed.c seedsum.c
	cc $^ -o $@


