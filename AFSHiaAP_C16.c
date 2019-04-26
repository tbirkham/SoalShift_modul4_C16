#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/irkham/SISOP/modul4";
char cipher[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
char encpath[999], decpath[999];

void encrypt(char change[])
{
	int n;
	for(n = 0; change[n]!= '\0'; ++n)
	{
		int i, ch = change[n];

		if(ch == '/') continue;

		int length = strlen(cipher);
		for(i = 0; i < length; i++)
		{
			if(ch == cipher[i])
			{
				break;
			}
		}
		
		i += 17;
		if(i > 93) 
		i -= length;

		change[n] = cipher[i];
	}
}

void decrypt(char change[])
{
	int n;
	for(n = 0; change[n] != '\0'; ++n)
	{
		int i, ch = change[n];

		if(ch == '/') continue;

		int length = strlen(cipher);
		for(i = 0; i < length; i++)
		{
			if(ch == cipher[i])
			{
				break;
			}
		}
		
		i -= 17;
		if(i < 0) 
		i += length;

		change[n] = cipher[i];
	}
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];

	// 1
	strcpy(encpath, path);
	if(strcmp(encpath, ".") != 0 && strcmp(encpath, "..") != 0)
	{
		encrypt(encpath);
		sprintf(fpath,"%s%s", dirpath, encpath);
	}
	else
	{
		sprintf(fpath, "%s%s", dirpath, path);
	}
	
	res = lstat(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		// 1
		strcpy(encpath, path); 
		encrypt(encpath);
		sprintf(fpath, "%s%s", dirpath, encpath);
	}
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL)
	{
		struct stat st;
		memset(&st, 0, sizeof(st));

		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

		// 1
		if(strcmp(de->d_name, ".")!= 0 && strcmp(de->d_name, "..")!= 0)
		{
			strcpy(decpath, de->d_name);
			decrypt(decpath);
			res = (filler(buf, decpath, &st, 0));
		}
		else
		{
		res = (filler(buf, de->d_name, &st, 0));	
		}
		if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
