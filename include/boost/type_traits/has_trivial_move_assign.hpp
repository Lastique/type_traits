
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED
#define BOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED

#include <boost/type_traits/intrinsics.hpp>
#include <boost/type_traits/integral_constant.hpp>

#if !defined(BOOST_HAS_TRIVIAL_MOVE_ASSIGN) || defined(BOOST_MSVC) || defined(BOOST_INTEL)
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#ifdef BOOST_MSVC
#include <boost/type_traits/is_reference.hpp>
#endif
#endif

#if defined(__GNUC__) || defined(__clang)
#include <boost/type_traits/is_assignable.hpp>
#include <boost/type_traits/is_volatile.hpp>
#endif

namespace boost {

template <typename T>
struct has_trivial_move_assign : public integral_constant<bool,
#ifdef BOOST_HAS_TRIVIAL_MOVE_ASSIGN
   BOOST_HAS_TRIVIAL_MOVE_ASSIGN(T)
#else
   ::boost::is_pod<T>::value && !::boost::is_const<T>::value && !::boost::is_volatile<T>::value
#endif
   > {};

template <> struct has_trivial_move_assign<void> : public false_type{};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct has_trivial_move_assign<void const> : public false_type{};
template <> struct has_trivial_move_assign<void const volatile> : public false_type{};
template <> struct has_trivial_move_assign<void volatile> : public false_type{};
#endif

} // namespace boost

#endif // BOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED
