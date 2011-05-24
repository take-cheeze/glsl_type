#ifndef _CHEEZE__MATRIX_HXX_
#define _CHEEZE__MATRIX_HXX_

#include <boost/foreach.hpp>
#include <boost/range/irange.hpp>
#include <boost/static_assert.hpp>

#include <vec.hxx>


namespace cheeze {
	namespace detail {
		template<class T, std::size_t N>
		struct base_mat
			: public boost::array<T, N>
			, public boost::addable<base_mat<T, N> >
			, public boost::subtractable<base_mat<T, N> >
			, public boost::multipliable<base_mat<T, N> >
			, public boost::addable<base_mat<T, N>, T>
			, public boost::subtractable<base_mat<T, N>, T>
			, public boost::multipliable<base_mat<T, N>, T>
			, public boost::equality_comparable<base_mat<T, N>, T>
		{
			typedef T value_type;
			typedef value_type& reference;
			typedef value_type const& const_reference;
			typedef base_mat<value_type, N> class_name;
			static int const size = N;

			base_mat() {}

			explicit base_mat(typename value_type::value_type const& x)
			{
				boost::fill(*this, value_type::value_type());
				std::for_each(this->begin()
				, this->begin() + std::min(class_name::size, value_type::size)
				, (*this)[boost::lambda::_1][boost::lambda::_1] = x);
			}
			template<class SrcT, std::size_t SrcN>
			explicit base_mat(array_vec<SrcT, SrcN> const& src)
			{
				boost::fill(*this, src);
			}
			template<class SrcT, std::size_t SrcN>
			base_mat(base_mat<SrcT, SrcN> const& x)
			{
				boost::fill(*this, value_type());
				std::copy(this->begin()
				, this->begin() + std::min(N, SrcN), x.begin());
			}

			// operators
#define PP_operator(r, data, op) \
	class_name& operator op(class_name const& x) { \
		boost::transform(*this, x.begin() \
		, this->begin(), boost::lambda::_1 op boost::lambda::_1); \
		return *this; \
	} \
	class_name& operator op(const_reference x) { \
		boost::for_each(*this, boost::lambda::_1 op x); \
		return *this; \
	}

			BOOST_PP_SEQ_FOR_EACH(PP_operator, , (+=)(-=));

#undef PP_operator

			bool operator ==(const_reference x) const
			{
				return boost::count(*this, x) == this->size();
			}
			template<class SrcT, std::size_t SrcN>
			class_name& operator *=(base_mat<SrcT, SrcN> const& src)
			{
				BOOST_STATIC_ASSERT(SrcN == value_type::size);
				boost::fill(*this, value_type());
				BOOST_FOREACH(int const i, boost::irange(0, class_name::size)) {
					boost::for_each(boost::irange(0, value_type::size), (*this)[i][boost::lambda::_1] += (*this)[i][boost::lambda::_1] * src[boost::lambda::_1][i]);
				}
				return *this;
			}
			class_name& operator *=(class_name const& src)
			{
				using boost::lambda::_1;
				boost::fill(*this, value_type());
				BOOST_FOREACH(int const i, boost::irange(0, class_name::size)) {
					BOOST_FOREACH(int const j, boost::irange(0, value_type::size)) {
						(*this)[i][j] += (*this)[i][j] * src[j][i];
					}
				}
				return *this;
			}
		};
	}

	// typedefs
	typedef detail::base_mat<vec2, 2> mat2; // float
	typedef detail::base_mat<vec3, 3> mat3;
	typedef detail::base_mat<vec4, 4> mat4;

	typedef detail::base_mat<vec2, 2> mat2x2;
	typedef detail::base_mat<vec3, 2> mat2x3;
	typedef detail::base_mat<vec4, 2> mat2x4;

	typedef detail::base_mat<vec2, 3> mat3x2;
	typedef detail::base_mat<vec3, 3> mat3x3;
	typedef detail::base_mat<vec4, 3> mat3x4;

	typedef detail::base_mat<vec2, 4> mat4x2;
	typedef detail::base_mat<vec3, 4> mat4x3;
	typedef detail::base_mat<vec4, 4> mat4x4;

	typedef detail::base_mat<dvec2, 2> dmat2; // double
	typedef detail::base_mat<dvec3, 3> dmat3;
	typedef detail::base_mat<dvec4, 4> dmat4;

	typedef detail::base_mat<dvec2, 2> dmat2x2;
	typedef detail::base_mat<dvec3, 2> dmat2x3;
	typedef detail::base_mat<dvec4, 2> dmat2x4;

	typedef detail::base_mat<dvec2, 3> dmat3x2;
	typedef detail::base_mat<dvec3, 3> dmat3x3;
	typedef detail::base_mat<dvec4, 3> dmat3x4;

	typedef detail::base_mat<dvec2, 4> dmat4x2;
	typedef detail::base_mat<dvec3, 4> dmat4x3;
	typedef detail::base_mat<dvec4, 4> dmat4x4;

} // namespace cheeze

#endif // _CHEEZE__MATRIX_HXX_
