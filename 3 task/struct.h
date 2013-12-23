#define CLUSTER_SIZE 8192
#define CLUSTER_COUNT_FAT 1048576
#define EOC 0xOFFFFFFF
#define NOT_USED 0
#define ELEMENT_COUNT_IN_CATALOG 256

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