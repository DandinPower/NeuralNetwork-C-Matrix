all:
	gcc mnist.c include/matrix.h src/matrix.c include/vector.h src/vector.c include/libs.h src/libs.c include/loss.h src/loss.c include/activation.h src/activation.c -lm
	./a.out