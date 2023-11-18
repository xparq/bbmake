#ifndef _H7G5689FJ42578DT7D245JT88745N45687_
#define _H7G5689FJ42578DT7D245JT88745N45687_

#include <limits>
#include <functional>
//#include <ostream> // The conv. ops. should be enough!
#include <cassert>

namespace sz {

//--------------------------------------------------------------------------------------
template <typename CountType = unsigned>
struct Counter
// Has the same interval and overflow characteristics as CountType
{
private:
	using Self = Counter<CountType>;
public:
	constexpr Counter(CountType from = 0) : count(from) {}

	constexpr CountType get()        const { return count; }
	constexpr operator CountType()   const { return get(); }
	constexpr CountType operator()() const { return get(); }

	constexpr void reset()                      { count = 0; }
	constexpr void set(CountType n)             { count = n; }
	constexpr CountType operator()(CountType n) { set(n); return n; }
	Self&     operator=(CountType n)       { set(n); return *this; }
	Self&     operator=(const Self& other) { set(other.count); return *this; }
	constexpr CountType operator++(int)    { return ++count; }
	constexpr CountType operator++()       { return count++; }
	constexpr CountType operator--(int)    { return --count; }
	constexpr CountType operator--()       { return count--; }
	//auto operator<=>(const Counter<CountType& other) { return count <=> other.count; }
		// Not needed: the ones for CountType would be found via the conv. op.

//protected:
	CountType count;
};


//--------------------------------------------------------------------------------------
template <typename CountType = unsigned>
struct CappedCounter : Counter<CountType>
// Stops at the max. val. on ++, but -- is not guarded (behaves the same as CountType)
// The other modifiers aren't checked either, and maxed() is undefined if count > max.
{
private:
	using Self = CappedCounter<CountType>;
	using Base = Counter<CountType>;
public:
	constexpr
	CappedCounter(CountType max = std::numeric_limits<CountType>::max(),
	              CountType from = 0)
		: Base(from), limit(max) {}

	Self&     operator=(CountType n)       { Base::set(n); return *this; }
	Self&     operator=(const Self& other) { Base::set(other.count); return *this; }
	constexpr void      max(CountType max) { limit = max; }
	constexpr CountType max()        const { return limit; }
	constexpr CountType maxed()      const { return Base::get() == limit; }
	constexpr CountType operator++(int)    { return maxed() ? Base::get() : Base::operator++(0); }
	constexpr CountType operator++()       { return maxed() ? Base::get() : Base::operator++(); }

//protected:
	CountType limit;
};


//--------------------------------------------------------------------------------------
template <typename CountType = unsigned>
struct GuardedCounter : Counter<CountType>
// Overflow-Guarded variant, with a callback and an overflow (carry) flag
// The callback receives the instance, and is expected to clear the overflow flag.
{
private:
	using Self = GuardedCounter<CountType>;
	using Base = Counter<CountType>;
protected:
	constexpr void _guarded_inc() { auto oldcount = Base::get(); Base::operator++(0);
	                                 if (oldcount > Base::get()) { overflowed = true; on_overflow(*this); } }
public:
	using Base::Base; // Use the upstream ctors

	Self&     operator=(Self other)        { Base::set(other.count); return *this; }
	Self&     operator=(const Self& other) { Base::set(other.count); return *this; }
	constexpr CountType operator++(int)    { _guarded_inc(); return Base::get(); }
	constexpr CountType operator++()       { auto oldcount = Base::get(); _guarded_inc(); return oldcount; }

//protected:
	bool overflowed = false;
	std::function<void(Self&)> on_overflow = [](Self&){}; // Another version could just throw instread...
};

} // namespace


//============================================================================
#ifdef UNIT_TEST

#include <cstdint>
#include <iostream>

using namespace sz;
using namespace std;

int main()
{
	Counter<int> x = 1;
	cerr << "Counter<int> x = 1; Should be 1: " << x << "\n";

	//-------------------------------------------------------------------
	GuardedCounter<uint8_t> gc(255);
	gc.on_overflow = [](auto& c) { cerr << "overflowed! " << unsigned(c) << endl; }; // unsigned(c), as <<uint8 is botched in C++! :-/
	gc++;

	//-------------------------------------------------------------------
	if (gc == 0) cerr << "OK, comparison works, too, if this was printed.\n";

	cerr << "Comparison: Counter<>(1) < Counter<>(2) ?\t";
		cerr << boolalpha << ( Counter<>(1) < Counter<>(2) ) << endl;

	//-------------------------------------------------------------------
	cerr << "\nfor (Counter i; i++ <= 10;) ... -> 1 .. 10\n";
		for  (Counter<> i; i++ <= 10;) cerr << i << " ";

	cerr << "\n\nfor (Counter i(8); i < 10; ++i) ... -> 8 .. 9\n";
		for  (Counter<> i(8); i < 10; ++i) cerr << i << " ";

	cerr << "\n\n"
	     << "Capped<>: default max (unsigned): " << CappedCounter<>().max() << "\n";
	cerr << "Capped<uint8_t>: default max: " << (unsigned)CappedCounter<uint8_t>().max() << "\n";
	cerr << "Capped<short>: default max: " << CappedCounter<short>().max() << "\n";
	cerr << "Capped<size_t>: default max: " << CappedCounter<size_t>().max() << "\n";

	cerr << "\nCapped: 0 .. 10!\n\t";
		CappedCounter<> cc(10);
		for (int i = 0; i++ < 20; ++cc)	cerr << cc << (cc.maxed()?"!":"") << " ";

	cerr << "\nCapped: 5 .. 20!\n\t";
		CappedCounter<> cc2(20, 5);
		for (int i = 0; i++ < 20; cc2++) cerr << cc2 << (cc2.maxed()?"!":"") << " ";

	cerr << "\nReuse (reset, recap): 0 .. 13!\n\t";
		cc.reset(); cc.max(13);
		for (int i = 0; i++ < 15; cc++) cerr << cc << (cc.maxed()?"!":"") << " ";

	//-------------------------------------------------------------------
	cerr << "\n\nAssign: operator=(-1u)\n\t";
		cc.operator=(unsigned(-1)); cerr << cc << ", ";
	cerr << "\nAssign: x = -1u\n\t";
		cc = unsigned(-1); cerr << cc << ", ";

	cerr << "\n\nAssign: operator=(-1)\n\t";
	cc.operator=(unsigned(-1)); cerr << cc << ", ";
	cerr << "\nAssign: x = -1\n\t";
		cc = unsigned(-1); cerr << cc << ", ";

	cerr << "\n\nAssign: copy op= cc2 (should be 20)\n\t";
		cc = cc2; cerr << cc << ", ";

	cerr << "\n\nAssign: funcall-op(7)\n\t";
		cerr << cc(7) << "\n";
}

#endif // UNIT_TEST
#endif // _H7G5689FJ42578DT7D245JT88745N45687_
