char alphabetNormalize( const char a );
char alphabetDenormalize( const char a );

const int ALPHABETSIZE = (CHAR_MAX);

typedef std::string String;

class PMSingle {
	public:
		virtual void match( const String& S, bool callBack (int) ) = 0;
};

class FailIdx {
	public:
		FailIdx( const String& kw );
		FailIdx( const FailIdx& f );
	
	int operator[]( const int i ) const;
	bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const FailIdx& t
	);
	private:
		std::vector<int> rep;
};

class PMKMP : public PMSingle {
	public:
		PMKMP( const String& kw );
		PMKMP( const PMKMP& r );
		virtual void match( const String& S, bool callBack (int) );
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const PMKMP& t );
	private:
		String keyword;
		FailIdx ff;
};