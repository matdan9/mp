#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <windows.h>


class FileManager
{
public:
	FileManager();
	~FileManager();
	
	int readLine(FILE*, int length, char *content);
	int scanFile(const char*, char **content);
	void getFile(const char*, FILE *);
	FILE *getFile(const char*);
	long getLineLength(FILE *);

private:
	char fileExists(char *);
};