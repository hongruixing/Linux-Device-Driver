#define IOC_MAGIC   'X'
#define IOC_NOP _IO(IOC_MAGIC,0)
#define IOC_RD  _IOR(IOC_MAGIC,1,int)
#define IOC_WR  _IOW(IOC_MAGIC,2,int)
//#define IOC_RDWR _IOWR(IOC_MAGIC,3,int)
//#define IOC_MAX  4

