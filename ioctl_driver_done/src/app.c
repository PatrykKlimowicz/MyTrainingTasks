#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>	
#include <sys/ioctl.h>

#include <ioctl_cmds.h>

void ioctl_set_msg(int file_desc, char *message)
{
	int ret;

	ret = ioctl(file_desc, IOCTL_SET_MSG, message);

	if (ret < 0) {
		printf("%s failed:%d\n", __func__, ret);
		exit(-1);
	}
}

void ioctl_get_msg(int file_desc)
{
	int ret;
	char message[100];

	ret = ioctl(file_desc, IOCTL_GET_MSG, message);

	if (ret < 0) {
		printf("%s failed:%d\n", __func__, ret);
		exit(-1);
	}

	printf("%s: %s\n", __func__, message);
}

void ioctl_get_nth_byte(int file_desc, int index)
{
	char c;

	c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, index);
	printf ("%s: %c\n", __func__, c);
}

int main(int argc, char **argv)
{
	int file_desc, ret;
	char *msg = argv[1];

	file_desc = open(DEVICE_FILE_NAME, 0);
	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}

	ioctl_set_msg(file_desc, msg);
	ioctl_get_nth_byte(file_desc, 3);
	ioctl_get_msg(file_desc);

	close(file_desc);
	return 0;
}
