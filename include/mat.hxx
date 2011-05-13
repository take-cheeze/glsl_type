#ifndef _CHEEZE__MATRIX_HXX_
#define _CHEEZE__MATRIX_HXX_

#include <vec.hxx>


namespace cheeze {

	namespace detail {
		template<class T, size_t N>
		struct base_mat : public std::array<T, N> {
			typedef T value_type;
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
