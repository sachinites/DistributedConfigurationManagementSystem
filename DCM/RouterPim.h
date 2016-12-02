#ifndef __ROUTERPIM__
#define __ROUTERPIM__

#include "AbstractRouterVRF.h"

class VRF;
class SSMMap;

class RouterPim: public AbstractRouterVRF{
	private:
		string m_rp_address;
		unsigned int m_hello_timer;
		SSMMap *m_ssmmap;
		unsigned int m_max_cache;
		unsigned int m_nbr_timeout;
		unsigned int m_join_prune_interval;
		unsigned int m_inact_interval;
		unsigned int m_prune_w_interval;
		unsigned int m_spt_th;

		void load_rules();
	public:
		RouterPim();
		RouterPim(VRF *vrf);
		virtual ~RouterPim(); 
		void setrp_address(string rp_address);
		void sethello_timer(unsigned int hello_timer);
		string getrp_address();
		unsigned int gethello_timer();
		void setmax_cache(unsigned int max_cache);
		unsigned int getmax_cache();
		void setssmmap(SSMMap *ssmmap);
		void setnbr_timeout(unsigned int nbr_timeout);
		unsigned int getnbr_timeout();
		void setjoin_prune_interval(unsigned int join_prune_interval);
		unsigned int getjoin_prune_interval();
		void setinact_interval(unsigned int inact_interval);
		unsigned int getinact_interval();
		void setprune_w_interval(unsigned int prune_w_interval);
		unsigned int getprune_w_interval();
		void setspt_th(unsigned int spt_th);
		unsigned int getspt_th();
		SSMMap* getssmmap();
		static RouterPim* instantiateRouterPim(VRF *vrf);
		virtual string getclass_name();
		virtual void dump();
		virtual int validation(DCMENUMS *attr, void *new_value);
		virtual int update(DCMENUMS *attr, void *value);
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
		static string getAttributeStr(int attr);
		static void load_enums_for_rest();
		static void load_callpoint_for_rest();
};

#endif /* __ROUTERPIM__ */
