#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <ioctl_cmds.h>

void ioctl_set_msg(int file_desc, char *message)
{
	int ret;

	printf("In function: %s\nmsg: %s\nfd: %d\n", __func__, message, file_desc);
	ret = ioctl(file_desc, IOCTL_SET_MSG, message);

	if (ret < 0) {
		printf("%s failed:%d\n", __func__, ret);
		exit(-1);
	}
}

void ioctl_get_msg(int file_desc)
{
	int ret_val;
	char message[BUF_LEN];

	ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);

	if (ret_val < 0) {
		printf("%s failed: %d\n", __func__, ret_val);
		exit(-1);
	}

	printf("%s message: %s\n", __func__, message);
}

void ioctl_get_nth_byte(int file_desc, int byte_number)
{
	int i;
	char c;

	printf("%s message: ", __func__);

	c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, byte_number);

	if (c < 0) {
		printf("%s failed at the byte number: %d\n", __func__, i);
		exit(-1);
	}

	printf("%c\n", c);
}

int main(int argc, char *argv[])
{
	int fd;
	char *msg = "Message passed by ioctl\n";

	printf("msg to kernel via ioctl: %s\n", msg);

	fd = open(DEVICE_FILE_NAME, 0);
	if (fd < 0) {
		printf("Sadly, the file can not be opened.\n");
		exit(-1);
	}

	ioctl_set_msg(fd, msg);
	ioctl_get_nth_byte(fd, 5);
	ioctl_get_msg(fd);

	close(fd);
	return 0;
}
