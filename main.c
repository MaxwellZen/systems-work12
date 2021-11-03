#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main() {
	char dirname[50] = ".";
	struct stat a;
	struct dirent *entry;
	long long filesizes;
	DIR *b = opendir(dirname);
	if (!b) {
		printf("Directory not opened successfully\n");
		return 0;
	}
	char dirs[5000] = "Directories:\n", files[5000] = "Regular files:\n", add[5000];
	while ((entry = readdir(b))) {
		if (entry->d_type == 8) {
			stat(entry->d_name, &a);
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
