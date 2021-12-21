typedef std::string String;

const State FIRSTSTATE = 0;
const State INVALIDSTATE = -1;

class PM {

};

class PMMultiple : public PM{
	public:
		virtual void match( const String& S, bool callBack (int, const
			std::set<String>&) ) = 0;
	};