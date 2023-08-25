#include <stdio.h> // IO Operations
#include <stdlib.h> // Exit statuses are defined in this
#include <dirent.h> // needed for running operations like open, close, read directory

int main(void) {

	DIR* d; // directory stream variable
	struct dirent* entry; // directory entry structure
	int content_count = 0;

	d = opendir("."); // Open directory stream at the specified directory (in this case current directory)

	if (d) // if opendir() did not return NULL
	{
		while ((entry = readdir(d)) != NULL) // As long as there are entries to print
		{
			// If d_type is not a part of posix but glibc, otherwise can filter for files
			// using (entry->d_type == DT_REG) (For regular files)
			content_count++;
			printf("%s\n", entry->d_name);
		}

		if (closedir(d) == -1)
		{
			printf("Cannot close directory!\n");
			return EXIT_FAILURE;
		}

		printf("--------------------\n");
		printf("Number of contents in the directory: %d\n", content_count);

		return EXIT_SUCCESS; // Successfully closed directory stream
	}

	printf("Cannot read the given directory!\n");
	return EXIT_FAILURE;
}
