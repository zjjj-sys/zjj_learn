#ifdef  CONFIG_SUPPORT_WIEGAND_DEV

#ifndef __CWIEGAND_CONTROLLER_H__
#define __CWIEGAND_CONTROLLER_H__

class CWiegandController{
public:
	explicit CWiegandController(uint32_t nProductModel);
	virtual ~CWiegandController();
	bool output34bit(uint32_t val);
	bool output26bit(uint32_t val);
private:
	bool output(uint32_t val,uint32_t bits);

private:
	int m_nWiegandDevFd;
	int m_nWiegandOutputGpio_Data0;
	int m_nWiegandOutputGpio_Data1;
	bool m_bInitialized;
};


#endif //__CWIEGAND_CONTROLLER_H__

#endif //#ifdef  CONFIG_SUPPORT_WIEGAND_DEV

