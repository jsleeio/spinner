#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CYCLE 	"-\\|/-\\|/"

struct spinner {
	char*	cycle;
	size_t	length;
	size_t	position;
};

struct spinner* spinner_new(void) {
	struct spinner* sp = malloc(sizeof(struct spinner));
	sp->cycle	= CYCLE;
	sp->length	= strlen(CYCLE);
	sp->position	= 0;
	return sp;
}

char spinner_advance(struct spinner* sp) {
	assert(sp != NULL);
	assert(sp->length > 0);
	if (sp->cycle[sp->position] == '\0')
		sp->position = 0;
	char r = sp->cycle[sp->position];
	sp->position++;
	return r;
}

int main(int argc, char** argv) {
	struct spinner* sp = spinner_new();
	char buffer[128];
	size_t nread;
	if (argc > 1)
		fputs(argv[1],stderr);
	fputs("  ", stderr); // compensate for first backspace
	while ((nread = fread(buffer,1,sizeof(buffer),stdin)) > 0) {
		if (ferror(stdin)) {
			fputc('\n', stderr);
			perror(argv[0]);
			exit(1);
		} else if (feof(stdin)) {
			fputc('\n', stderr);
			exit(0);
		}
		fwrite(buffer,1,nread,stdout);
		fputs("\b\b",stderr);
		fputc(spinner_advance(sp),stderr);
		fputc(' ',stderr);
	}
	fputs("\b\b\n", stderr);
	return 0;
}
