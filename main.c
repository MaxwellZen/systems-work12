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
	if (!stat(dirname, &a)) printf("Directory opened successfully\n");
	else {
		printf("Directory not opened successfully\n");
		return 0;
	}
	printf("Information for Directory: %s\n", dirname);
	printf("Total Directory Size: %lld Bytes\n", a.st_size);
	DIR *b = opendir(dirname);
	struct dirent *entry;
	char dirs[5000] = "Directories:\n", files[5000] = "Regular files:\n";
	while ((entry = readdir(b))) {
		if (entry->d_type == 8) {
			strcat(files, "\t");
			strcat(files, entry->d_name);
			strcat(files, "\n");
		} else if (entry->d_type==4) {
			strcat(dirs, "\t");
			strcat(dirs, entry->d_name);
			strcat(dirs, "\n");
		}
	}
	printf("%s", dirs);
	printf("%s", files);
	return 0;
}
