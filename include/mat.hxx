#ifndef _CHEEZE__MATRIX_HXX_
#define _CHEEZE__MATRIX_HXX_

#include <boost/foreach.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/range/irange.hpp>
#include <boost/static_assert.hpp>

#include <vec.hxx>


namespace cheeze {
    namespace detail {

        template<class T, std::size_t N>
        struct array_mat : public boost::array<T, N> {
            typedef T value_type;
            typedef value_type& reference;
            typedef value_type const& const_reference;
            typedef array_mat<T, N> class_name;

            array_mat() { boost::fill(*this, value_type()); }

            template<class SrcT, std::size_t SrcN>
            array_mat(array_vec<SrcT, SrcN> const& src) {
                std::copy(src.begin(),
                          src.begin() + std::min(this->size(), src.size()),
                          this->begin());
            }
        };

#define CAT BOOST_PP_CAT

#define PP_class_name(n) CAT(base_mat, n)
#define PP_init_arg(z, i, text) (CAT(text, i))
#define PP_init_assign(z, i, text) (*this)[i] = CAT(text, i);

#define PP_member(r, d, i, e)                                           \
        BOOST_PP_IF(BOOST_PP_LESS(i, d),                                \
                    const_reference e() const { return (*this)[i]; }    \
                    value_type& e() { return (*this)[i]; }              \
                    value_type& e(const_reference v) { (*this)[i] = v; } \
                    , )                                                 \

#define PP_operator(r, data, op)                                \
        class_name& operator CAT(op, =)(class_name const& x) {  \
            using namespace boost::lambda;                      \
            boost::transform(*this, x, this->begin(),           \
                             ret<value_type>(_1 op _2));        \
            return *this;                                       \
        }                                                       \
        class_name& operator CAT(op, =)(const_reference x) {    \
            boost::for_each(*this,                              \
                            boost::lambda::_1 CAT(op, =) x);    \
            return *this;                                       \
        }                                                       \

#define PP_base_mat(dummy, N, text)                                     \
        template<class T>                                               \
        struct PP_class_name(N)                                         \
            : public array_mat<T, N>                                    \
            , public boost::additive<PP_class_name(N)<T> >              \
            , public boost::additive<PP_class_name(N)<T>, T>            \
            , public boost::equality_comparable<PP_class_name(N)<T>, T> \
        {                                                               \
            typedef T value_type;                                       \
            typedef T& reference;                                       \
            typedef T const& const_reference;                           \
            typedef PP_class_name(N) class_name;                        \
                                                                        \
            PP_class_name(N)() : array_mat<T, N>() {}                   \
            explicit PP_class_name(N)(typename value_type::const_reference x) { \
                boost::fill(*this, typename value_type::value_type());  \
                BOOST_FOREACH(std::size_t const i, boost::irange(0, std::min<std::size_t>(class_name::static_size, value_type::static_size))) { \
                    (*this)[i][i] = x;                                  \
                }                                                       \
            }                                                           \
            template<class SrcT, std::size_t SrcN>                      \
                PP_class_name(N)(array_mat<SrcT, SrcN> const& src)      \
                : array_mat<T, N>(src) {}                               \
            PP_class_name(N)                                            \
                BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_REPEAT(N, PP_init_arg, const_reference v)) { \
                BOOST_PP_REPEAT(N, PP_init_assign, v)                   \
                    }                                                   \
                                                                        \
            BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (x)(y)(z)(w))         \
                BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (r)(g)(b)(a))     \
                BOOST_PP_SEQ_FOR_EACH_I(PP_member, N, (s)(t)(p)(q))     \
                                                                        \
                class_name& operator =(const_reference x) {             \
                boost::fill(*this, x);                                  \
                return *this;                                           \
            }                                                           \
                                                                        \
            BOOST_PP_SEQ_FOR_EACH(PP_operator, , (+)(-));               \
                                                                        \
            bool operator ==(const_reference x) const {                 \
                return boost::count(*this, x) == this->size();          \
            }                                                           \
            template<class SrcT, std::size_t SrcN>                      \
                array_mat<SrcT, class_name::static_size>                \
                operator *(array_mat<SrcT, SrcN> const& src) const {    \
                BOOST_STATIC_ASSERT(value_type::static_size == SrcN);   \
                                                                        \
                typedef array_mat<SrcT, class_name::static_size> output_type; \
                output_type output;                                     \
                                                                        \
                BOOST_FOREACH(int const i, boost::irange<int>(0, output_type::class_name::static_size)) { \
                    BOOST_FOREACH(int const j, boost::irange<int>(0, output_type::value_type::static_size)) { \
                        BOOST_FOREACH(int const k, boost::irange<int>(0, array_mat<SrcT, SrcN>::value_type::static_size)) { \
                            output[i][j] += (*this)[i][k] * src[k][j];  \
                        }                                               \
                    }                                                   \
                }                                                       \
                return output;                                          \
            }                                                           \
            template<class SrcT, int SrcN>                              \
                array_mat<SrcT, class_name::static_size> operator *=(array_mat<SrcT, SrcN> const& src) { \
                BOOST_STATIC_ASSERT(value_type::static_size == SrcT::value_type::static_size); \
                BOOST_STATIC_ASSERT(class_name::static_size == SrcT::class_name::static_size); \
                                                                        \
                typedef array_mat<SrcT, class_name::static_size> output_type; \
                output_type output;                                     \
                                                                        \
                BOOST_FOREACH(int const i, boost::irange<int>(0, output_type::class_name::static_size)) { \
                    BOOST_FOREACH(int const j, boost::irange<int>(0, output_type::value_type::static_size)) { \
                        BOOST_FOREACH(int const k, boost::irange<int>(0, array_mat<SrcT, SrcN>::value_type::static_size)) { \
                            output[i][j] += (*this)[i][k] * src[k][j];  \
                        }                                               \
                    }                                                   \
                }                                                       \
                std::swap(*this, output);                               \
                return *this;                                           \
            }                                                           \
        };                                                              \

        BOOST_PP_REPEAT_FROM_TO(1, 5, PP_base_mat, T)

#undef PP_base_vec
#undef PP_operator
#undef PP_init_assign
#undef PP_init_arg
#undef PP_member
#undef PP_class_name

    } // namespace detail


    // typedefs
#define MACRO_1(z, N, text) typedef CAT(detail::base_mat, N)< CAT(vec, N) > CAT(mat, N);
    BOOST_PP_REPEAT_FROM_TO(2, 5, MACRO_1, )
#undef MACRO_1

#define A_ELEM BOOST_PP_ARRAY_ELEM
#define MACRO_1(r, N, elem)                                             \
    typedef CAT(detail::base_mat, N)                                    \
        <                                                               \
        CAT(A_ELEM(0, elem), CAT(vec, A_ELEM(1, elem)))                 \
        >                                                               \
        CAT(A_ELEM(0, elem), CAT(mat, CAT(N, CAT(x, A_ELEM(1, elem))))) \
        ;                                                               \
    
#define MACRO_2(z, N, text)                       \
    BOOST_PP_SEQ_FOR_EACH(MACRO_1, N,             \
                          ((2, ( , 2)))           \
                          ((2, ( , 3)))           \
                          ((2, ( , 4)))           \
                          ((2, (d, 2)))           \
                          ((2, (d, 3)))           \
                          ((2, (d, 4)))           \
                          )                       \

    BOOST_PP_REPEAT_FROM_TO(2, 5, MACRO_2, )

#undef MACRO_2
#undef MACRO_1
#undef A_ELEM

#undef CAT

} // namespace cheeze

#endif // _CHEEZE__MATRIX_HXX_
