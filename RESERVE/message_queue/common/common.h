#ifndef __COMMON_H__
#define __COMMON_H__

# include <fcntl.h>
# include <mqueue.h>

# define MQ_PATH_NAME       ("/tmp_mqu")

# define MAX_MQ_MSG_NUM     (10)
# define MAX_MQ_MSG_SIZE    (8192)

#endif
