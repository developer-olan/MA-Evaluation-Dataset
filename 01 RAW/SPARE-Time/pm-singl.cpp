typedef std::string String;

class PM {

};

class PMSingle : public PM {
	public:
		virtual void match( const String& S, bool callBack (int) ) = 0;
};