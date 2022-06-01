asmlinkage int sys_hello(int x, int y);
asmlinkage ssize_t ksys_swrite(unsigned int fd, char __user *buf, size_t count);
asmlinkage ssize_t ksys_sread(unsigned int fd, char __user *buf, size_t count);