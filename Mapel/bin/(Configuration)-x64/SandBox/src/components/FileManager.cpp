#include "FileManager.h"

FileManager::FileManager(){

}

FileManager::~FileManager(){
	
}

int FileManager::scanFile(const char* path, char **content) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Error can not load file! %s \n", strerror(errno));
		Sleep(1000);
		return 0;
	}

	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	rewind(file);
	
	*content = new char[size];
	int lastIndexPosition = 0;
	int length = 0;
	long nextSize = 1;
	while (!feof(file) && nextSize > 0) {
		nextSize = size - lastIndexPosition;
		lastIndexPosition += readLine(file, nextSize, (*content + lastIndexPosition)) + 1;
		++length;
	}
	nextSize = size - lastIndexPosition;
	//content[size] = '\0';
	fclose(file);
	return length;
}

int FileManager::readLine(FILE *file, int length, char *retVal) {
	if (!feof(file)) {
		for (int i = 0; i < length; ++i) {
			char buffer = fgetc(file);
			retVal[i] = buffer;
			if (buffer == '\n') {
				return i;
			}else if (buffer == 9) {
				for (int j = i; j < (i + 7); ++j) {
					retVal[j] = ' ';
				}
				i += 6;
			}
		}
	}
}
