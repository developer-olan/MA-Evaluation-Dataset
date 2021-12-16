char alphabetNormalize( const char a );
char alphabetDenormalize( const char a );

const int ALPHABETSIZE = (CHAR_MAX);

typedef std::string String;

class PMMultiple {
	public:
		virtual void match( const String& S,
		bool callBack (int, const std::set<String>&) ) = 0;
};

typedef int State;

const State FIRSTSTATE = 0;
const State INVALIDSTATE = -1;

template<class T> class PMAC : public PMMultiple {
	public:
		PMAC( const std::set<String>& P );
		PMAC( const PMAC& M );
		
		virtual void match( const String& S,
		bool callBack (int, const std::set<String>&) );
		bool c_inv() const;
		
		template<class T2> friend std::ostream& operator<<( std::ostream&
		os, const PMAC<T2>& r );
	private:
		T machine;
};

template<class T> PMAC<T>::PMAC( const std::set<String>& P ) : machine( P
	) {
	assert( c_inv() );
}

template<class T> PMAC<T>::PMAC( const PMAC& M ) : machine( M.machine ) {
	assert( c_inv() );
}

template<class T> void PMAC<T>::match( const String& S, bool callBack
	(int, const std::set<String>&) ) {
	assert( c_inv() );
	auto State q = FIRSTSTATE;
	auto int j = 0;
	
	if( !machine.output( q ).empty() ) {
		if( !callBack( j, machine.output( q ) ) ) {
			assert( c_inv() );
			return;
		}
	}
	
	auto int Slen = S.length();
	
	while( j < Slen ) {
		q = machine.transition( q, S[j] );
		assert( q != INVALIDSTATE );
		j++;
		
		if( !machine.output( q ).empty() ) {
			if( !callBack( j, machine.output( q ) ) ) {
			assert( c_inv() );
			return;
			}
		}
	}
	
	assert( c_inv() );
}

template<class T> bool PMAC<T>::c_inv() const {
	return( machine.c_inv() );
}

template<class T> std::ostream& operator<<( std::ostream& os, const
	PMAC<T>& r ) {
	assert( r.c_inv() );
	os << "PMAC<T> = (\n" << r.machine << ")\n";
	return( os );
}