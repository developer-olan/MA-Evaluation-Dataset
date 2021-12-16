char alphabetNormalize( const char a );
char alphabetDenormalize( const char a );

const int ALPHABETSIZE = (CHAR_MAX);

typedef std::string String;

class PMSingle {
	public:
		virtual void match( const String& S,
		bool callBack (int) ) = 0;
};

template<class MO, class SL, class MI> class PMBM : public PMSingle {
	public:
		PMBM( const String& kw );
		
		virtual void match( const String& S, bool callBack (int) );
		bool c_inv() const;
		template<class MO2, class SL2, class MI2> friend std::ostream&
		operator<<( std::ostream& os, const PMBM<MO2,SL2,MI2> r );
	private:
		String keyword;
		MO mo;
		SL sl;
		MI shifter;
};

template<class MO, class SL, class MI> PMBM<MO,SL,MI>::PMBM( const
	String& kw ) : keyword( kw ), mo( keyword ), sl( keyword ), shifter(
	keyword, mo ) {
	assert( c_inv() );
}

template<class MO, class SL, class MI> void PMBM<MO,SL,MI>::match( const
	 String& S, bool callBack (int) ) {
	assert( c_inv() );
	auto int pLen = keyword.length();
	auto int Slast = S.length() - pLen;
	auto int vBegin = 0;
	
	while( vBegin <= Slast ) {
	
		vBegin = sl.skip( S, vBegin, Slast );
		assert( vBegin <= Slast );
		auto int i;
		for( i = 0; i < pLen && S[vBegin + mo.traverse( i )] ==
			keyword[mo.traverse( i )]; i++ ) {
		}

		if( i == pLen ) {
		
			if( !callBack( vBegin + pLen ) ) {
				return;
			}
		}
		
		vBegin += shifter.shift( i, alphabetNormalize( i >= pLen ? 0 :
		S[vBegin + mo.traverse( i )] ) );
	}
}

template<class MO, class SL, class MI> bool PMBM<MO,SL,MI>::c_inv() const
{
	return( mo.c_inv() && sl.c_inv() && shifter.c_inv() );
}

template<class MO, class SL, class MI> std::ostream& operator<<(
	 std::ostream& os, const PMBM<MO,SL,MI> r ) {
	assert( r.c_inv() );
	os << "PMBM = (\n" << r.keyword << r.mo << r.sl << r.shifter << ")\n";
	return( os );
}
