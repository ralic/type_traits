//-----------------------------------------------------------------------------
// boost aligned_storage.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_ALIGNED_STORAGE_HPP
#define BOOST_ALIGNED_STORAGE_HPP

#include <cstddef> // for std::size_t

#include "boost/config.hpp"
#include "boost/type_traits/alignment_of.hpp"
#include "boost/type_traits/type_with_alignment.hpp"

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/identity.hpp"

namespace boost {
namespace detail {

BOOST_STATIC_CONSTANT(
      std::size_t
    , alignment_of_max_align = alignment_of<max_align>::value
    );

} // namespace detail

template <
      std::size_t size_
    , std::size_t alignment_ = -1
>
class aligned_storage
{
private:
    typedef typename mpl::apply_if_c<
          alignment_ == -1
        , mpl::identity<detail::max_align>
        , type_with_alignment<alignment_>
        >::type align_t;

public:
    BOOST_STATIC_CONSTANT(
          std::size_t
        , size = size_
        );
    BOOST_STATIC_CONSTANT(
          std::size_t
        , alignment = (
              alignment_ == -1
            ? detail::alignment_of_max_align
            : alignment_
            )
        );

private: // representation
    union
    {
        char buf[size];
        align_t dummy_;
    } data_;

private: // noncopyable
    aligned_storage(const aligned_storage&);
    aligned_storage& operator=(const aligned_storage&);

public: // structors
    aligned_storage()
    {
    }

    ~aligned_storage()
    {
    }

public: // accessors
    void* address()
    {
        return &data_.buf[0];
    }

    const void* address() const
    {
        return &data_.buf[0];
    }
};

} // namespace boost

#endif // BOOST_ALIGNED_STORAGE_HPP