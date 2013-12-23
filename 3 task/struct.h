struct FileRecord{
	char name[256];
	long first_cluster;
	long size;
	ushort mode;
	time_t ctime;
	time_t mtime;
	time_t atime;
	ushort uid;
	ushort gid;
	long gen;
}