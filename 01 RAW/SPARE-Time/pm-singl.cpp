typedef std::string String;

class PM {

};

class PMSingle {
	public:
		virtual void match( const String& S, bool callBack (int) ) = 0;
};