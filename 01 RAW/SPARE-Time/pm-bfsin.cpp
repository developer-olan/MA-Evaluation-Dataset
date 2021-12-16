int min( const int a, const int b );
int max( const int a, const int b );

const int PLUSINFINITY = INT_MAX;
const int MINUSINFINITY = INT_MIN;

const int TRUE = 1;
const int FALSE = 0;

typedef std::string String;

class PMSingle {
	public:
		virtual void match( const String& S,
		bool callBack (int) ) = 0;
};

class PMBFSingle : public PMSingle {
	public:
		PMBFSingle( const String& keyword );
		virtual void match( const String& S,
		bool callBack (int) );
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const
			PMBFSingle& r );
	private:
		const String kw;
};

PMBFSingle::PMBFSingle( const String& keyword ) :
	kw( keyword ) {
	assert( c_inv() );
}

bool PMBFSingle::c_inv() const {
	return( true );
}

void PMBFSingle::match( const String& S, bool callBack (int) ) {
	assert( c_inv() );
	
	auto int pLen = kw.length();
	auto int Slast = S.length() - pLen;
	
	for(int i = 0; i <= Slast; i++ ) {
		auto int j;
		
		for( j = 0; j < pLen && kw[j] == S[i + j]; j++ ) {
		
		}
		
		if( j == pLen ) {
		
			if( !callBack( i + pLen ) ) {
				return;
			}
		}
	}
	
	assert( c_inv() );
}

std::ostream& operator<<( std::ostream& os, const PMBFSingle& r ) {
	assert( r.c_inv() );
	os << "PMBFSingle = (\n" << r.kw << ")\n";
	return( os );
}
