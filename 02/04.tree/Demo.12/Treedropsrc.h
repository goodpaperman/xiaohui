#ifndef _DROP_SRC
	#define _DROP_SRC
	class CTreeDropSource : public COleDropSource 
	{
	// Constructors
	public:
		virtual SCODE GiveFeedback(DROPEFFECT dropEffect);
		
	};
#endif