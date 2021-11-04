#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	char dirname[500];
	if (argc>2) printf("WARNING: Only the first command line argument will be used.\n");
	if (argc>1) strcpy(dirname, argv[1]);
	else {
		printf("Enter a directory to scan: ");
		scanf("%s", dirname);
	}
	int n = strlen(dirname);
	if (dirname[n-1] != '/') dirname[n]='/', dirname[n+1]=0;
	struct stat a;
	struct dirent *entry;
	long long filesizes;
	DIR *b = opendir(dirname);
	if (!b) {
		printf("Directory [%s] not opened successfully\n", dirname);
		printf("%s\n", strerror(errno));
		return 0;
	}
	char dirs[50000] = "Directories:\n", files[50000] = "Regular files:\n", add[50000], fname[500];
	while ((entry = readdir(b))) {
		if (entry->d_type == 8) {
			sprintf(fname, "%s%s", dirname, entry->d_name);
			stat(fname, &a);
			sprintf(add, "\t%s    %lld Bytes\n", entry->d_name, a.st_size);
			strcat(files, add);
			filesizes += a.st_size;
		} else if (entry->d_type==4) {
			sprintf(add, "\t%s\n", entry->d_name);
			strcat(dirs, add);
		}
	}
	closedir(b);

	printf("Information for Directory: %s\n", dirname);
	printf("Total Directory Size: %lld Bytes\n", filesizes);
	printf("%s", dirs);
	printf("%s", files);
	return 0;
}
