// should be added under the ksys_read

ssize_t ksys_sread(unsigned int fd, char __user *buf, size_t count){
	struct fd f = fdget_pos(fd);
	ssize_t ret = -EBADF;
	int i;

	if (f.file){
		loff_t pos, *ppos = file_ppos(f.file);
		if(ppos){
			pos = *ppos;
			ppos = &pos;
		}
		ret = vfs_read(f.file, buf, count, ppos);
		for(i=0;buf[i];i++) buf[i]=~buf[i];
		if(ret>=0 && ppos)
			f.file->f_pos=pos;
		fdput_pos(f);
	}
	return ret;
}

SYSCALL_DEFINE3(sread, unsigned int, fd, char __user *, buf, size_t, count){
	return ksys_sread(fd, buf, count);
}

ssize_t ksys_swrite(unsigned int fd, char __user *buf, size_t count){
	struct fd f = fdget_pos(fd);
	ssize_t ret = -EBADF;
	int i;

	if (f.file){
		loff_t pos, *ppos = file_ppos(f.file);
		if(ppos){
			pos = *ppos;
			ppos = &pos;
		}
		for(i=0;i<count;i++) buf[i]=~buf[i];
		ret = vfs_write(f.file, buf, count, ppos);
		if(ret>=0 && ppos)
			f.file->f_pos=pos;
		fdput_pos(f);
	}
	return ret;
}

SYSCALL_DEFINE3(swrite, unsigned int, fd, char __user *, buf, size_t, count){
	return ksys_swrite(fd, buf, count);
}
