	///////////////////////////////////////////////////////////////////
//  magic.h - header file to provide with macro of ioctl()       //
//                                   				 //
//  version - 1.0	                                         //
//  Author - Vishal Verma , Syracuse University, vvverma@syr.edu //
///////////////////////////////////////////////////////////////////

/*================================================================
Header for-							
------------	user_datto.c
------------	datto_char.c
================================================================*/


#ifndef MAGIC_H
#define MAGIC_H
#define IOC_MAGIC   'X'
#define IOC_NOP _IO(IOC_MAGIC,0)
#define IOC_RD  _IOR(IOC_MAGIC,1,int)
#define IOC_WR  _IOW(IOC_MAGIC,2,int)
#endif
