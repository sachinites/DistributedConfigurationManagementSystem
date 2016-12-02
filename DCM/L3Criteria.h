#ifndef __L3CRITERIA__
#define __L3CRITERIA__

class AbstractInterface;

class L3Criteria{
	private:
	public:
		L3Criteria();
		virtual ~L3Criteria();
		static bool HasL3Config(AbstractInterface *intf);
};

#endif /* __L3CRITERIA__ */
