#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define genf(msg) fprintf(fp, "%s\n", msg);

int main(int argc, char **argv)
{
	FILE *fp   = NULL;
	FILE *fp_m = NULL;

	char buffer[FILENAME_MAX];
	char full_path[FILENAME_MAX + 256];

	char *option, *file_name;

	if (argc == 3) {
		option = argv[1];
		file_name = argv[2];
	}
	else if (argc == 2) {
		option = "";
		file_name = argv[1];
	}
	else {
		printf("Usage:\n"
			   "    %s <new_file_name>\n"
			   "    Enter a name for the file that will be created.\n"
			   "\nOptions:\n"
			   "\t-f\t\tforces the file to be created, overwriting if it exists.\n",
			   argv[0]);
		return 0;
	}

	getcwd(buffer, FILENAME_MAX);
	snprintf(full_path, sizeof(full_path), "%s/%s.c", buffer, file_name);

	if (access(file_name, F_OK) == 0 && strcmp(option, "-f") != 0) {
		printf("File already exists, choose a different name\n");
		return 1;
	}

	fp = fopen(full_path, "w");
	if (fp == NULL) {
		printf("Failed to create file\n");
		return -1;
	}

	fp_m = fopen("Makefile", "w");
	if (fp_m == NULL) {
		printf("Failed to create Makefile\n");
		fclose(fp);
		return -1;
	}

	genf(		"/* This code has been generated"				);
	genf( 		" * by a generator. 2024 ABN"	 				);
	genf( 		" */ "								);
	genf( 		"#include <stdio.h>"						);
	genf( 		"#include <stdlib.h>"						);
	genf( 		"#include <string.h>"						);
	genf( 		""								);
	genf( 		"int main(int argc, char **argv)"				);
	genf( 		"{"								);
	genf( 		"\t(void)argc;"							);
	genf( 		"\t(void)argv;"							);
	genf( 		"\tprintf(\"Hello, World!\\nGenerated successfully!\\n\");"	);
	genf( 		""								);
	genf( 		"\treturn 0;"							);
	genf( 		"}"								);

	/* Generates the makefile as well */
	char makefile[] = {
		"CODEDIRS = . lib\n"
		"INCDIRS = . ./include/\n"
		"\n"
		"CC = gcc\n"
		"OPT = -O0\n"
		"DEPFLAGS = -MP -MD\n"
		"CFLAGS = -Wall -Wextra -g $(foreach D,$(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)\n"
		"\n"
		"CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))\n"
		"OBJECTS = $(patsubst %.c,%.o, $(CFILES))\n"
		"DEPFILES = $(patsubst %.c,%.d,$(CFILES))\n"
		"\n"
		"all: $(BINARY)\n"
		"\t@$(info Compiling and creating the Makefile)\n"
		"\n"
		"$(BINARY): $(OBJECTS)\n"
		"\t@$(CC) -o $@ $^\n"
		"\n"
		"%.o:%.c\n"
		"\t@$(CC) $(CFLAGS) -c -o $@ $<\n"
		"\n"
		"clean:\n"
		"\t@rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)\n"
		"\n"
		"deepclean:\n"
		"\t@$(info removing Makefile and .c files)\n"
		"\t@rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)\n"
		"\t@rm -rf *.c\n"
		"\t@rm -rf Makefile\n"
		"\n"
		"distribute: clean\n"
		"\t@tar -zcvf dist.tgz *\n"
		"\n"
		"diff:\n"
		"\t@$(info The status of the repository, and the volume of per-file changes:)\n"
		"\t@git status\n"
		"\t@git diff --stat\n"
		"\n"
		".PHONY: all deepclean clean diff distribute\n"
		"\n"
		"-include $(DEPFILES)"
	};
	fprintf(fp_m, "BINARY = %s\n%s", file_name, makefile);

	fclose(fp);
	fclose(fp_m);

	printf("[done] generated %s.c\n"
		   "[done] generated Makefile\n"
		   "\n"
		   "Usage:\n"
			"\tmake\t\t\t this compiles the program.\n"
			"\tmake clean\t\t this cleans up the project.\n"
			"\tmake distribute\t\t will make a .tgz package and clean.\n"
			"\n\tmake deepclean\t\t deletes everything generated.\n"
		   "\n"
		   " - ABN 2024\n", file_name);
	return 0;
}

