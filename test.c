#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zip.h"
#include "unzip.h"


int main(int argc, char** argv)
{
	int ret;

	/// zip file
	zipFile zf;

	zf = zipOpen64("test.zip", 0);
	if (zf == NULL) {
		fprintf(stderr, "zipOpen64 error\n");
		return 1;
	}

	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour = \
	zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;

	ret = zipOpenNewFileInZip(zf, "dir/1.txt", &zi, NULL,0,NULL,0,NULL, Z_DEFLATED, 1);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipOpenNewFileInZip error\n");
		return 1;
	}
	ret = zipWriteInFileInZip(zf, "12345", 6);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipWriteInFileInZip error\n");
		return 1;
	}
	ret = zipCloseFileInZip(zf);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipCloseFileInZip error\n");
		return 1;
	}

	ret = zipOpenNewFileInZip(zf, "2.txt", &zi, NULL,0,NULL,0,NULL, Z_DEFLATED, 1);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipOpenNewFileInZip error\n");
		return 1;
	}
	ret = zipWriteInFileInZip(zf, "测试", 6);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipWriteInFileInZip error\n");
		return 1;
	}
	ret = zipCloseFileInZip(zf);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipCloseFileInZip error\n");
		return 1;
	}

	
	ret = zipClose(zf, NULL);
	if (ret != ZIP_OK) {
		fprintf(stderr, "zipClose error\n");
		return 1;
	}


	/// unzip file
	unzFile uf;
	unz_global_info64 gi;
	unz_file_info64 file_info;

	uf = unzOpen64("test.zip");
	if (uf == NULL) {
		fprintf(stderr, "unzOpen64 error\n");
		return 1;
	}

	ret = unzGetGlobalInfo64(uf, &gi);
	if (ret != UNZ_OK) {
		fprintf(stderr, "unzGetGlobalInfo64 error\n");
		return 1;
	}

	char filename[64];
	char buf[1024];
	int len;
	unzGoToFirstFile(uf);
	while(1) {
		ret = unzGetCurrentFileInfo64(uf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
		if (ret != UNZ_OK) {
			fprintf(stderr, "unzGetCurrentFileInfo64 error\n");
			return 1;
		}
		printf("filename = %s\n", filename);

		ret = unzOpenCurrentFile(uf);
		if (ret != UNZ_OK) {
			fprintf(stderr, "unzOpenCurrentFile error\n");
			return 1;
		}
		do {
			memset(buf, 0, 1024);
			len = unzReadCurrentFile(uf, buf, 1023);
			if (len < 0) {
				fprintf(stderr, "unzReadCurrentFile error\n");
				return 1;
			}
			if (len > 0) {
				printf("%s", buf);
			}
		} while(len > 0);
		printf("\n");

		unzCloseCurrentFile(uf);

		ret = unzGoToNextFile(uf);
		if (ret == UNZ_END_OF_LIST_OF_FILE) {
			break;
		}
		if (ret != UNZ_OK) {
			fprintf(stderr, "unzGoToNextFile error\n");
			return 1;
		}
	}

	unzClose(uf);

	return 0;
}

