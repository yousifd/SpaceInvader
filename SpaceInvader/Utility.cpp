#include <cstdio>

#include "Utility.h"

void glCheckError() {
	GLenum err;
	int counter = 0;
	do {
		err = glGetError();
		switch (err) {
		case GL_NO_ERROR:
			printf("OpenGL No Error!\n");
			break;
		case GL_INVALID_ENUM:
			printf("OpenGL Invalid Enum Error!\n");
			break;
		case GL_INVALID_VALUE:
			printf("OpenGL Invalid Value Error!\n");
			break;
		case GL_INVALID_OPERATION:
			printf("OpenGL Invalid Operation Error!\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("OpenGL Invalid Framebuffer Operation Error!\n");
			break;
		case GL_OUT_OF_MEMORY:
			printf("OpenGL Invalid Out of Memory Error!\n");
			break;
		}
		printf("COUNTER: %d\n", counter);
		counter++;
	} while (err != GL_NO_ERROR);
}