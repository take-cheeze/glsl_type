#ifndef _CHEEZE__VECTOR_HXX_
#define _CHEEZE__VECTOR_HXX_

#include <array>
#include <functional>

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
#define PP_className(n) BOOST_PP_CAT(base_vec, n)
#define PP_member(r, d, i, e) \
		BOOST_PP_IF(BOOST_PP_LESS(i, d), \
			value_type const& e() const { return (*this)[i]; } \
			value_type& e() { return (*this)[i]; } \
			value_type& e(value_type const& v) { (*this)[i] = v; } \
		, )
#define PP_initArg(z, i, text) (BOOST_PP_CAT(text, i))
#define PP_initAssign(z, i, text) (*this)[i] = BOOST_PP_CAT(text, i);
#define PP_operator(op, func) \
	class_name& operator op(class_name const& x) { \
		boost::transform(*this, x.begin() \
		, this->begin(), std::func<value_type>()); \
		return *this; \
	} \
	class_name& operator op(value_type const& x) { \
		boost::for_each(*this, [x](value_type& v) { v op x; }); \
		return *this; \
	}
#define PP_base_vec(dummy, n, text) \
		template<class T> \
		struct PP_className(n) \
			: public std::array<T, n> \
			, public boost::addable<PP_className(n)<T>> \
			, public boost::subtractable<PP_className(n)<T>> \
			, public boost::multipliable<PP_className(n)<T>> \
			, public boost::dividable<PP_className(n)<T>> \
			, public boost::modable<PP_className(n)<T>> \
			, public boost::addable<PP_className(n)<T>, T> \
			, public boost::subtractable<PP_className(n)<T>, T> \
			, public boost::multipliable<PP_className(n)<T>, T> \
			, public boost::dividable<PP_className(n)<T>, T> \
			, public boost::modable<PP_className(n)<T>, T> \
			, public boost::equality_comparable<PP_className(n)<T>, T>\
		{ \
			typedef T value_type; \
			typedef PP_className(n)<T> class_name; \
			 \
			PP_className(n)() { boost::fill(*this, value_type()); } \
			PP_className(n)(value_type const& v) { boost::fill(*this, v); } \
			PP_className(n)BOOST_PP_SEQ_TO_TUPLE( \
				BOOST_PP_REPEAT(n, PP_initArg, value_type const& v)) \
			{ \
				BOOST_PP_REPEAT(n, PP_initAssign, v) \
			} \
			 \
			BOOST_PP_SEQ_FOR_EACH_I(PP_member, n, (x)(y)(z)(w)) \
			BOOST_PP_SEQ_FOR_EACH_I(PP_member, n, (r)(g)(b)(a)) \
			BOOST_PP_SEQ_FOR_EACH_I(PP_member, n, (s)(t)(p)(q)) \
			 \
			class_name& operator =(value_type const& x) { \
				boost::fill(*this, x); \
				return *this; \
			} \
			bool operator ==(value_type const& x) const { \
				return boost::count(*this, x) == n; \
			} \
			 \
			PP_operator(+=, plus) \
			PP_operator(-=, minus) \
			PP_operator(*=, multiplies) \
			PP_operator(/=, divides) \
			PP_operator(%=, modulus) \
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
