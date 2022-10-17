#ifndef __CSOCKET_PAIR_H__
#define __CSOCKET_PAIR_H__




#include "common.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>




class CSocketPairObj{
public:
	CSocketPairObj();
	virtual ~CSocketPairObj();
	int socket(int index);
private:
	int m_arraySocketPair[2];
};


















#endif //__CSOCKET_PAIR_H__

