#ifndef _CHEEZE__VECTOR_HXX_
#define _CHEEZE__VECTOR_HXX_

#include <array>
#include <functional>

#include <boost/lambda/lambda.hpp>
#include <boost/operators.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/fill.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/transform.hpp>


namespace cheeze {
	namespace detail {
		template<class T, std::size_t N>
		struct array_vec : public std::array<T, N>
		{
			typedef T value_type;
			typedef value_type& reference;
			typedef value_type const& const_reference;
			enum { size = N };

			array_vec() { boost::fill(*this, value_type()); }

			template<class SrcT, std::size_t SrcN>
			array_vec(array_vec<SrcT, SrcN> const& src)
			{
				std::copy(this->begin()
				, this->begin() + std::min(this->size(), src.size())
				, src.begin());
			}
		};

#define PP_className(n) BOOST_PP_CAT(base_vec, n)
#define PP_member(r, d, i, e) \
	BOOST_PP_IF(BOOST_PP_LESS(i, d), \
		const_reference e() const { return (*this)[i]; } \
		value_type& e() { return (*this)[i]; } \
		value_type& e(const_reference v) { (*this)[i] = v; } \
	, )
#define PP_initArg(z, i, text) (BOOST_PP_CAT(text, i))
#define PP_initAssign(z, i, text) (*this)[i] = BOOST_PP_CAT(text, i);
#define PP_operator(r, data, op) \
	class_name& operator op(class_name const& x) { \
		boost::transform(*this, x.begin() \
		, this->begin(), boost::lambda::_1 op boost::lambda::_2); \
		return *this; \
	} \
	class_name& operator op(const_reference x) { \
		boost::for_each(*this, boost::lambda::_1 op x); \
		return *this; \
	}
#define PP_base_vec(dummy, N, text) \
	template<class T> \
	struct PP_className(N) \
		: public array_vec<T, N> \
		, public boost::addable<PP_className(N)<T>> \
		, public boost::subtractable<PP_className(N)<T>> \
		, public boost::multipliable<PP_className(N)<T>> \
		, public boost::dividable<PP_className(N)<T>> \
		, public boost::modable<PP_className(N)<T>> \
		, public boost::addable<PP_className(N)<T>, T> \
		, public boost::subtractable<PP_className(N)<T>, T> \
		, public boost::multipliable<PP_className(N)<T>, T> \
		, public boost::dividable<PP_className(N)<T>, T> \
		, public boost::modable<PP_className(N)<T>, T> \
		, public boost::equality_comparable<PP_className(N)<T>, T> \
	{ \
		typedef T value_type; \
		typedef value_type& reference; \
		typedef value_type const& const_reference; \
		typedef PP_className(N)<T> class_name; \
		 \
		PP_className(N)() : array_vec<T, N>() {} \
		explicit PP_className(N)(const_reference v) \
		{ boost::fill(*this, v); } \
		template<class SrcT, std::size_t SrcN> \
		PP_className(N)(array_vec<SrcT, SrcN> const& src) \
			: array_vec<T, N>(src) {} \
		PP_className(N)BOOST_PP_SEQ_TO_TUPLE( \
			BOOST_PP_REPEAT(N, PP_initArg, const_reference v)) \
		{ \
			BOOST_PP_REPEAT(N, PP_initAssign, v) \
		} \
		 \
		BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (x)(y)(z)(w)) \
		BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (r)(g)(b)(a)) \
		BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (s)(t)(p)(q)) \
		 \
		class_name& operator =(const_reference x) { \
			boost::fill(*this, x); \
			return *this; \
		} \
		bool operator ==(const_reference x) const { \
			return boost::count(*this, x) == this->size(); \
		} \
		 \
		BOOST_PP_SEQ_FOR_EACH(PP_operator, , (+=)(-=)(*=)(/=)(%=)); \
	};

		BOOST_PP_REPEAT_FROM_TO(2, 5, PP_base_vec, T)

#undef PP_base_vec
#undef PP_operator
#undef PP_initAssign
#undef PP_initArg
#undef PP_member
#undef PP_className
	} // namespace detail

	// typedefs
#define MACRO_1(r, data, elem) \
	typedef BOOST_PP_CAT(detail::base_vec, data) \
	BOOST_PP_CAT(elem, data);
#define MACRO_2(z, n, text) \
	BOOST_PP_SEQ_FOR_EACH(MACRO_1, n, \
		(<float> vec)(<double> dvec) \
		(<bool> bvec)(<int> ivec)(<unsigned> uvec))

	BOOST_PP_REPEAT_FROM_TO(2, 5, MACRO_2, )

#undef MACRO_2
#undef MACRO_1
} // namespace cheeze

#endif // _CHEEZE__VECTOR_HXX_
