#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <city.h>

#include <string>
#include "misc.h"

#define HASH_CITY		0
#define HASH_MD5		1

int iHashType = 0;
std::string strContent;

void print_usage()
{
	printf("usage: hash [-md5|-city] [content]\n");
}

int main(int argc, char* argv[])
{
	const char* szContent = NULL;
	for(int i=1; i<argc; ++i)
	{
		if(strcmp(argv[i], "-help") == 0)
		{
			print_usage();
			return -1;
		}
		else if(strcmp(argv[i], "-city") == 0)
		{
			iHashType = 0;
		}
		else if(strcmp(argv[i], "-md5") == 0)
		{
			iHashType = 1;
		}
		else
		{
			szContent = argv[i];
		}
	}

	if(szContent == NULL)
	{
		char buffer[4097];
		memset(buffer, 0, 4097);
		int size = 0;
		while((size = read(STDIN_FILENO, buffer, 4096)) > 0)
		{
			strContent.append(buffer);
			memset(buffer, 0, size);
		}
	}
	else
		strContent = std::string(szContent);

	switch(iHashType)
	{
	case HASH_MD5:
		printf("%lu", MD5_uint64(strContent.c_str(), strContent.length()));
		break;
	default:
		printf("%lu", CityHash64(strContent.c_str(), strContent.length()));
		break;
	}

	return 0;
}

