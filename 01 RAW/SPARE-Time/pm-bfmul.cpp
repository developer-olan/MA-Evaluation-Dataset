int min( const int a, const int b );
int max( const int a, const int b );

const int PLUSINFINITY = INT_MAX;
const int MINUSINFINITY = INT_MIN;

const int TRUE = 1;
const int FALSE = 0;
typedef std::string String;

class PMMultiple {
	public:
		virtual void match( const String& S, bool callBack (int, const
			std::set<String>&) ) = 0;
};

class PMBFMulti : public PMMultiple {
	public:
		PMBFMulti( const std::set<String>& keywords );
		virtual void match( const String& S,
		bool callBack (int, const std::set<String>&) );
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const PMBFMulti&
			r );
private:
const std::set<String> P;
};

PMBFMulti::PMBFMulti( const std::set<String>& keywords ) :
	P( keywords ) {
	assert( c_inv() );
}

bool PMBFMulti::c_inv() const {
	return( true );
}

void PMBFMulti::match( const String& S, bool callBack (int, const
	std::set<String>&) ) {
	assert( c_inv() );
	auto int Slen = S.length();
	auto std::set<String> Matched;
	assert( Matched.empty() );
	
	for( int i = 0; i < Slen; i++ ) {
	
		for( std::set<String>::const_iterator k = P.begin(); k != P.end();
			k++ ) {
			
			auto int pLen = k->length();
			auto int j;
			
			for( j = 0; j < pLen && i >= pLen && k->operator[](k->length() -
				j - 1) == S[i - j]; j++ ) {
			}
			
			if( j == pLen ) {
			
			Matched.insert( *k );
			}
		}
		
		if( !Matched.empty() ) {
			if( !callBack( i, Matched ) ) {
				return;
			}
		
			Matched.clear();
		}
	}
	
	assert( c_inv() );
}

std::ostream& operator<<( std::ostream& os, const PMBFMulti& r ) {
	assert( r.c_inv() );
	os << "PMBFMulti = (\n" << r.P << ")\n";
	return( os );
}