#ifndef __PIMCONFIG__
#define __PIMCONFIG__

#include "AbstractL3Config.h"
#include <string>

class AbstractInterface;

class PIMConfig : public AbstractL3Config{
	private:
		bool m_pim_sparse;
		unsigned int m_dr_priority;
		unsigned int m_ttl_threshold;
		int validation(DCMENUMS *attr, void *new_value);
	public:
		PIMConfig();
		virtual ~PIMConfig();
		void setpim_sparse(bool pim_sparse);
		bool getpim_sparse();
		void setdr_priority(unsigned int dr_priority);
		unsigned int getdr_priority();
		void setttl_threshold(unsigned int ttl_threshold);
		unsigned int getttl_threshold();
		virtual void dump();
		virtual string getclass_name();
		static PIMConfig* instantiatePIMConfig(AbstractInterface *interface);
		static string getAttributeStr(int attr);
		virtual int update(DCMENUMS *attr, void *value);
};

#endif
