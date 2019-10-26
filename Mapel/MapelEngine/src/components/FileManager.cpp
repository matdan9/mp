#include "FileManager.h"

FileManager::FileManager(){}

FileManager::~FileManager(){}

int FileManager::scanFile(const char* path, char **content) {
	FILE *file = getFile(path);
	long size = getLineLength(file);
	*content = new char[size];
	int lastIndexPosition = 0;
	int length = 0;
	long nextSize = 1;
	while (!feof(file) && nextSize > 0) {
		nextSize = size - lastIndexPosition;
		lastIndexPosition += readLine(file, nextSize, (*content + lastIndexPosition)) + 1;
		++length;
	}
	fclose(file);
	return length;
}

long FileManager::getLineLength(FILE *file) {
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	rewind(file);
	return size;
}

FILE *FileManager::getFile(const char* path) {
	FILE *file = new FILE;
	file = fopen(path, "r");
	if (file == NULL) {
		printf("Error can not load file! %s \n", strerror(errno));
		Sleep(1000);
		throw 0;
	}
	return file;
}

void FileManager::getFile(const char* path, FILE *file) {
	file = fopen(path, "r");
	if (file == NULL) {
		printf("Error can not load file! %s \n", strerror(errno));
		Sleep(1000);
		throw 0;
	}
}

char FileManager::fileExists(char *path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Error can not load file! %s \n", strerror(errno));
		Sleep(1000);
		return 0;
	}
	return 1;
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
