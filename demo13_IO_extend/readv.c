/*
2020-5-19 12点24分
测试readv函数
*/

#include <stdio.h>
#include <sys/uio.h>

#define BUF_SIZE 	100

int main()
{
	struct iovec vec[2];
	char buf1[BUF_SIZE] = {0};
	char buf2[BUF_SIZE] = {0};

	int str_len;
	vec[0].iov_base = buf1;
	vec[0].iov_len = 3;
	vec[1].iov_base = buf2;
	vec[1].iov_len = 3;

	str_len = readv(1, vec, 2);
	printf("read bytes: %d \n", str_len);
	printf("First message: %s \n", buf1);
	printf("Second message: %s \n", buf2);
	
	return 0;
}

