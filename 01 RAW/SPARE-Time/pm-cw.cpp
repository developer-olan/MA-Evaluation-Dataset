char alphabetNormalize( const char a );
char alphabetDenormalize( const char a );

const int ALPHABETSIZE = (CHAR_MAX);

typedef std::string String;

typedef int State;

const State FIRSTSTATE = 0;
const State INVALIDSTATE = -1;

template<class T> class StateTo {
	public:
		StateTo( const int size = 0 );
		StateTo( const StateTo<T>& r );
		T& map( const State index );
		const T& operator[]( const State index ) const;
		void setSize( const int s );
		int size() const;
		bool c_inv() const;
		template<class T2> friend std::ostream& operator<<( std::ostream&
		os, const StateTo<T2>& t );
	private:
		std::vector<T> rep;
};

template<class T> inline StateTo<T>::StateTo(const int size) : rep(size) {
	assert(c_inv());
}

template<class T> inline StateTo<T>::StateTo(const StateTo<T>& r) :
	rep(r.rep) {
	assert(c_inv());
}

template<class T> inline T& StateTo<T>::map(const State index) {
	assert(c_inv());
	return(rep[index]);
}

template<class T> inline const T& StateTo<T>::operator[](const State
index) const {
	assert(c_inv());
	return(rep[index]);
}

template<class T> inline void StateTo<T>::setSize(const int s) {
	assert(c_inv());
	rep.resize(s);
	assert(c_inv());
}

template<class T> inline int StateTo<T>::size() const {
	assert(c_inv());
	return(rep.size());
}

template<class T> inline bool StateTo<T>::c_inv() const {
	return(true);
}

template<class T> std::ostream& operator<<(std::ostream& os, const
	StateTo<T>& t) {
	assert(t.c_inv());
	os << "StateTo = (\n" << t.rep << ")\n";
	assert(t.c_inv());
	return(os);
}

template<class T> std::ostream& operator<<( std::ostream& os, const
std::vector<T>& v );

template<class T> std::ostream& operator<<( std::ostream& os, const
std::set<T>& v );

template<class T> inline std::ostream& operator<<(std::ostream& os, const
std::vector<T>& v) {
	os << "Vector = (\n";
	std::vector<T>::const_iterator iter;
	int pos = 0;
	for (iter = v.begin(); iter != v.end(); ++iter, ++pos) {
		os << pos << "->" << *iter << "\n";
	}
	os << ")\n";
	return os;
}

template<class T> inline std::ostream& operator<<(std::ostream& os, const
std::set<T>& v) {
	os << "Set = (\n";
	std::set<T>::const_iterator iter;
	int pos = 0;
	for (iter = v.begin(); iter != v.end(); ++iter, ++pos) {
		os << pos << "->" << *iter << "\n";
	}
	os << ")\n";
	return os;
}

template<class T> class SymbolTo {
	public:
		SymbolTo();
		SymbolTo( const SymbolTo<T>& r );
		
		T& map( const int index );
		const T& operator[]( const int index ) const;
		bool c_inv() const;
		template<class T2> friend std::ostream& operator<<( std::ostream&
			os, const SymbolTo<T2>& t );
	private:
		std::vector<T> rep;
};

template<class T> inline SymbolTo<T>::SymbolTo() : rep(ALPHABETSIZE) {
	assert(c_inv());
}

template<class T> inline SymbolTo<T>::SymbolTo(const SymbolTo<T>& r) :
	rep(r.rep) {
	assert(c_inv());
}

template<class T> inline T& SymbolTo<T>::map(const int index) {
	assert(c_inv());
	return(rep[index]);
}

template<class T> inline const T& SymbolTo<T>::operator[](const int
	index) const {
	assert(c_inv());
	return(rep[index]);
}

template<class T> inline bool SymbolTo<T>::c_inv() const {
	return(rep.size() == ALPHABETSIZE);
}

template<class T> std::ostream& operator<<(std::ostream& os, const
	SymbolTo<T>& t) {
	assert(t.c_inv());
	os << "SymbolTo = (\n" << t.rep << ")\n";
	assert(t.c_inv());
	return(os);
}

template<class T> class Trie {
	public:
		Trie( const std::set<String>& P );
		Trie( const Trie<T>& r );
		
		State image( const State q, const char a ) const;
		State BFTfirst() const;
		State BFTsuccessor( const State q ) const;
		int BFTdepth( const State q ) const;
		int size() const;
		bool c_inv() const;
		template<class T2> friend std::ostream& operator<<( std::ostream&
			os, const Trie<T2>& t );
	private:
		StateTo< SymbolTo< State > > rep;
		StateTo<int> depth;
};

template<class T> inline Trie<T>::Trie(const std::set<String>& P) :
	rep(1), depth(1) {
	assert(!P.empty());
	for (int a = 0; a < ALPHABETSIZE; a++) {
		rep.map(FIRSTSTATE).map(a) = INVALIDSTATE;
	}
	depth.map(FIRSTSTATE) = 0;
	for (std::set<String>::const_iterator i = P.begin(); i != P.end();
	i++) {
		State q = FIRSTSTATE;
		T trav(*i);
		for (String::const_iterator j = i->begin(); j != i->end(); j++) {
			if (image(q,
				alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
				j))])) == INVALIDSTATE) {
				
				State latest = rep.size();
				rep.setSize(latest + 1);
				depth.setSize(latest + 1);
					for (int a = 0; a < ALPHABETSIZE; a++) {
						rep.map(latest).map(a) = INVALIDSTATE;
					}
					
					depth.map(latest) = depth[q] + 1;
					rep.map(q).map(alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
					j))])) = latest;
					
				}
				assert(image(q,
					alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
					j))])) != INVALIDSTATE);
				q = image(q,
					alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
					j))]));
		}
	}
	
	assert(c_inv());
}

template<class T> inline Trie<T>::Trie(const Trie<T>& r) : rep(r.rep),
	depth(r.depth) {
	assert(c_inv());
}

template<class T> inline State Trie<T>::image(const State q, const char
a) const {
	assert(c_inv());
	assert(FIRSTSTATE <= q && q < size());
	assert(0 <= a && a < ALPHABETSIZE);
	return(rep[q][a]);
}

template<class T> inline State Trie<T>::BFTfirst() const {
	assert(c_inv());
	assert(depth[FIRSTSTATE] == 0);
	return(FIRSTSTATE);
}

template<class T> inline State Trie<T>::BFTsuccessor(const State q) const
{
	assert(c_inv());
	if (q == size() - 1) {
	return(INVALIDSTATE);
	}	
	State r;
	for (r = q + 1; r < size(); r++) {
		if (depth[r] == depth[q]) {
		return(r);
		}
	}
	
	for (r = FIRSTSTATE; r < size(); r++) {
		if (depth[r] == depth[q] + 1) {
		return(r);
		}
	}
	
	assert(!"I shouldn't be here");
	return(INVALIDSTATE);
}

template<class T> inline int Trie<T>::BFTdepth(const State q) const {
	assert(c_inv());
	return(depth[q]);
}

template<class T> inline int Trie<T>::size() const {
	assert(c_inv());
	return(rep.size());
}

template<class T> inline bool Trie<T>::c_inv() const {
	return(rep.c_inv() && depth.c_inv() && !depth[FIRSTSTATE] &&
	rep.size() == depth.size());
}

template<class T> std::ostream& operator<<(std::ostream& os, const
Trie<T>& t) {
	assert(t.c_inv());
	os << "Trie<T> = (\n" << t.rep << t.depth << ")\n";
	assert(t.c_inv());
	return(os);
}

template<class T> class Factoracle {
	public:
		Factoracle( const std::set<String>& P );
		Factoracle( const Factoracle<T>& r );
		
		State image( const State q, const char a ) const;
		int size() const;
		bool c_inv() const;
		template<class T2> friend std::ostream& operator<<( std::ostream&
		os, const Factoracle<T2>& t );
	private:
	StateTo<SymbolTo<State>> rep;
};

template<class T> inline Factoracle<T>::Factoracle(const
	std::set<String>& P) : rep(1) {
	assert(!P.empty());
	
	for (int a = 0; a < ALPHABETSIZE; a++) {
		rep.map(FIRSTSTATE).map(a) = INVALIDSTATE;
	}
	
	std::set<String>::const_iterator i = P.begin();
	State q = FIRSTSTATE;
	T trav(*i);
	
	for (String::const_iterator j = i->begin(); j != i->end(); j++) {
		State latest = rep.size();
		rep.setSize(latest + 1);
		
		for (int a = 0; a < ALPHABETSIZE; a++) {
			rep.map(latest).map(a) = INVALIDSTATE;
		}
		
		rep.map(q).map(alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
		j))])) = latest;
		
		assert(image(q,
			alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
			j))])) != INVALIDSTATE);
		q = image(q,
			alphabetNormalize((*i)[trav.traverse(std::distance(i->begin(),
			j))]));
	}
	
	for (int k = 1; k != i->length(); k++) {
		int ilen = i->length();
		int j = k;
		State q = FIRSTSTATE;
		
		while (j != i->length() && image(q,
			alphabetNormalize((*i)[trav.traverse(j)])) != INVALIDSTATE) {
			q = image(q, alphabetNormalize((*i)[trav.traverse(j)]));
			j++;
		}
		
		if (j != i->length()) {
			rep.map(q).map(alphabetNormalize((*i)[trav.traverse(j)])) = j + 1;
		}
	}
	assert(c_inv());
}

template<class T> inline Factoracle<T>::Factoracle(const Factoracle<T>&
	r) : rep(r.rep) {
	assert(c_inv());
}

template<class T> inline State Factoracle<T>::image(const State q, const
	char a) const {
	assert(c_inv());
	assert(FIRSTSTATE <= q && q < size());
	assert(0 <= a && a < ALPHABETSIZE);
	return(rep[q][a]);
}

template<class T> inline int Factoracle<T>::size() const {
	assert(c_inv());
	return(rep.size());
}

template<class T> inline bool Factoracle<T>::c_inv() const {
	return(rep.c_inv());
}

template<class T> std::ostream& operator<<(std::ostream& os, const
	Factoracle<T>& fo) {
	assert(fo.c_inv());
	os << "Factoracle<T> = (\n" << fo.rep << ")\n";
	assert(fo.c_inv());
	return(os);
}

int min( const int a, const int b );
int max( const int a, const int b );

const int PLUSINFINITY = INT_MAX;
const int MINUSINFINITY = INT_MIN;

const int TRUE = 1;
const int FALSE = 0;

class STravFWD {
	public:
		STravFWD( const String& s );
		
		int traverse( const int index ) const;
		int traverseInverse( const int index ) const;
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const STravFWD&
			t );
};

class STravREV {
	public:
		STravREV( const String& s );
		int traverse( int const index ) const;
		int traverseInverse( const int index ) const;
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const STravREV&
			t );
	private:
		STravREV() : len(-1) {}
		const int len;
};

typedef Trie<STravFWD> FTrie;
typedef Trie<STravREV> RTrie;
typedef Factoracle<STravFWD> FFactoracle;
typedef Factoracle<STravREV> RFactoracle;

class CWOutput {
	public:
		CWOutput( const std::set<String>& P, const RTrie& t );
		CWOutput( const CWOutput& r );
		~CWOutput();
		
		int isKeyword( const State q ) const;
		const String& operator[]( const State q ) const;
		bool c_inv() const;
		friend std::ostream& operator<<( std::ostream& os, const CWOutput&
			r );
	private:
		StateTo<String *> rep;
};

class PMMultiple {
	public:
		virtual void match( const String& S,
		bool callBack (int, const std::set<String>&) ) = 0;
};

template<class T, class U> class PMCW : public PMMultiple {
	public:
		PMCW( const std::set<String>& P );
		PMCW( const PMCW<T,U>& r );
		
		virtual void match( const String& S,
		bool callBack (int, const std::set<String>&) );
		bool c_inv() const;
		template<class T2, class U2> friend std::ostream& operator<<(
			std::ostream& os, const PMCW<T2,U2> r );
	private:
		U raut;
		CWOutput out;
		T shift;
};

template<class T, class U> PMCW<T,U>::PMCW( const std::set<String>& P ) :
	raut( P ), out( P, raut ), shift( P, raut, out ) {
	assert( c_inv() );
}

template<class T, class U> PMCW<T,U>::PMCW( const PMCW<T,U>& r ) : raut(
	r.raut ), out( r.out ), shift( r.shift ) {
	assert( c_inv() );
}

template<class T, class U> void PMCW<T,U>::match( const String& S, bool
	 callBack (int, const std::set<String>&) ) {
	assert( c_inv() );
	auto int r = 0, l = -1;
	auto State v = FIRSTSTATE;
	auto int vlen = 0;
	auto char vrtake1 = 0;
	auto std::set<String> O;
	
	if( out.isKeyword( v ) ) {
		O.insert( out[v] );
		if( !callBack( 0, O ) ) {
		return;
		}
		O.clear();
	}
	
	r += shift.shift( raut, alphabetNormalize( (l < 0 ? 0 : S[l]) ), v,
	vlen, vrtake1, alphabetNormalize( S[r] ) );
	auto int Slen = S.length();
	
	while( r <= Slen ) {
	
		l = r - 1;
		v = FIRSTSTATE;
		vlen = 0;
		vrtake1 = 0;
		
		if( out.isKeyword( v ) ) {
			O.insert( out[v] );
		}
		
		while( l >= 0 && raut.image( v, alphabetNormalize( S[l] ) ) !=
			 INVALIDSTATE ) {
			if( v == FIRSTSTATE ) {
				vrtake1 = S[l];
			}
			v = raut.image( v, alphabetNormalize( S[l] ) );
			vlen++;
			l--;
			
			if( out.isKeyword( v ) ) {
			O.insert( out[v] );
			}
		}
		
		if( !O.empty() ) {
			if( !callBack( r, O ) ) {
				return;
			}
			
			O.clear();
		}
		
		assert( shift.shift( raut, alphabetNormalize( (l < 0 ? 0 : S[l]) ),
			v, vlen, alphabetNormalize( vrtake1 ), alphabetNormalize( S[r]
			)) >= 1 );
			
		r += shift.shift( raut, alphabetNormalize( (l < 0 ? 0 : S[l]) ), v,
			vlen, alphabetNormalize( vrtake1 ), alphabetNormalize( S[r] ));
	}
}

template<class T, class U> bool PMCW<T,U>::c_inv() const {
	return( raut.c_inv() && out.c_inv() && shift.c_inv() );
}

template<class T, class U> std::ostream& operator<<( std::ostream& os,
	const PMCW<T,U> r ) {
	assert( r.c_inv() );
	os << "PMCW<T,U> = (\n" << r.raut << r.out << r.shift << ")\n";
	return( os );
}
