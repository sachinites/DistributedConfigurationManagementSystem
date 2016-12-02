#ifndef __L2CRITERIA__
#define __L2CRITERIA__

class AbstractInterface;

class L2Criteria{
	private:
	public:
		L2Criteria();
		virtual ~L2Criteria();
		static bool HasL2Config(AbstractInterface *intf);
};

#endif /* __L2CRITERIA__ */
