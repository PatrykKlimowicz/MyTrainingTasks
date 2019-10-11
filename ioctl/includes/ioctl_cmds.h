#ifndef __IOCTL_COMMANDS_H_
#define __IOCTL_COMMANDS_H_

#include <linux/ioctl.h>

#define SUCCESS 0
#define BUF_LEN 1024

/**
 * @brief magic number for ioctl 
 * commands group. Similar to major number for chardev,
 * but IOCTL has to know it at the beginning.
 */
#define IOCTL_GROUP_NUM 'k'

/**
 * @brief _IOW macro will create command that can write only
 * major number is created from 'k' character,
 * ID is equal to 1,
 * type of data is char *
 */
#define IOCTL_SET_MSG _IOW(IOCTL_GROUP_NUM, 0, char *)

/**
 * @brief _IOR macro will create command that can read only
 * major number is created from 'k' character,
 * ID is equal to 0,
 * type of data is char *
 */
#define IOCTL_GET_MSG _IOR(IOCTL_GROUP_NUM, 1, char *)

/**
 * @brief _IOWR macro will create command that can write and read
 * major number is created from 'k' character,
 * ID is equal to 2,
 * type of data is int (will be convert to ASCII character)
 */
#define IOCTL_GET_NTH_BYTE _IOWR(IOCTL_GROUP_NUM, 2, int)

/**
 * @brief name of file that is 'bridge' between kernel and user
 * 
 */
#define DEVICE_FILE_NAME "hello"

#endif
