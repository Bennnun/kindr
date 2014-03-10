/*
 * Copyright (c) 2013, Christian Gehring, Hannes Sommer, Paul Furgale, Remo Diethelm
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Christian Gehring, Hannes Sommer, Paul Furgale,
 * Remo Diethelm BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef KINDR_POSITIONS_POSITIONBASE_HPP_
#define KINDR_POSITIONS_POSITIONBASE_HPP_


#include "kindr/common/common.hpp"

namespace kindr {
//! Generic position interface
/*! \ingroup positions
 */
namespace positions {
//! Internal stuff (only for developers)
namespace internal {

/*! \brief Addition traits for positions
 *  \class AdditionTraits
 *  (only for advanced users)
 */
template<typename LeftAndRight_>
class AdditionTraits {
 public:
//  inline static LeftAndRight_ add(const LeftAndRight_& lhs, const LeftAndRight_& rhs);
//  inline static LeftAndRight_ subtract(const LeftAndRight_& lhs, const LeftAndRight_& rhs);
};

/*! \brief Multiplication traits for positions
 *  \class MultiplicationTraits
 *  (only for advanced users)
 */
template<typename Position_, typename ScalarPrimType_>
class MultiplicationTraits {
 public:
//  inline static Position_ multiply(const Position_& lhs, Scalar rhs);
//  inline static Position_ divide(const Position_& lhs, Scalar rhs);
};

/*! \class get_scalar
 *  \brief Gets the primitive of the position.
 */
template<typename Position_>
class get_scalar {
 public:
//  typedef PrimType Scalar;
};

} // namespace internal

/*! \class PositionBase
 * \brief Interface for a position.
 *
 * This class defines the generic interface for a position.
 * More precisely an interface to store and access the coordinates of a position of a point is provided.
 * \tparam Derived_ the derived class that should implement the position.
 * \ingroup positions
 *
 */
template<typename Derived_>
class PositionBase {
 public:
  /*! \brief Default constructor.
   *
    *  Creates a position with zero coefficients.
    */
  PositionBase() = default;

  /*! \brief Constructor from derived position.
   *
   *  This constructor has been deleted because the abstract class does not contain any data.
   */
  PositionBase(const Derived_&) = delete; // on purpose!!

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  operator Derived_& () {
    return static_cast<Derived_&>(*this);
  }

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  operator const Derived_& () const {
    return static_cast<const Derived_&>(*this);
  }

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  const Derived_& derived() const {
    return static_cast<const Derived_&>(*this);
  }


  /*! \brief Sets the position to zero.
   *  \returns reference
   */
  Derived_& setZero();

  /*! \brief Addition of two positions.
   *  \returns sum of the two positions.
   */
  template<typename OtherDerived_>
  Derived_ operator +(const PositionBase<OtherDerived_>& other) const {
    return internal::AdditionTraits<PositionBase<Derived_>>::add(this->derived(), other.derived());
  }

  /*! \brief Subtraction of two positions.
   *  \returns result of the subtraction of the two positions.
   */
  template<typename OtherDerived_>
  Derived_ operator -(const PositionBase<OtherDerived_>& other) const {
    return internal::AdditionTraits<PositionBase<Derived_>>::subtract(this->derived(), other.derived());
  }

  /*! \brief Multiplication of a position with a scalar.
   *  \returns product of a position and a scalar.
   */
  template<typename FactorPrimType_>
  Derived_ operator *(FactorPrimType_ factor) const {
    return internal::MultiplicationTraits<PositionBase<Derived_>, FactorPrimType_>::multiply(this->derived(), factor);
  }

  /*! \brief Division of a position by a scalar.
   *  \returns division of a position by a scalar.
   */
  template<typename DivisorPrimType_>
  Derived_ operator /(DivisorPrimType_ divisor) const {
    return internal::MultiplicationTraits<PositionBase<Derived_>, DivisorPrimType_>::divide(this->derived(), divisor);
  }

  /*! \brief Addition and assignment.
   *  \returns reference.
   */
  template<typename OtherDerived_>
  Derived_& operator +=(const PositionBase<OtherDerived_>& other);

  /*! \brief Subtraction and assignment.
   *  \returns reference.
   */
  template<typename OtherDerived_>
  Derived_& operator -=(const PositionBase<OtherDerived_>& other);

  /*! \brief Multiplication and assignment.
   *  \returns reference.
   */
  template<typename FactorPrimType_>
  Derived_& operator *=(FactorPrimType_ factor);

  /*! \brief Division and assignment.
   *  \returns reference.
   */
  template<typename DivisorPrimType_>
  Derived_& operator /=(DivisorPrimType_ divisor);
};


template<typename Position_, typename FactorPrimType_>
Position_ operator *(FactorPrimType_ factor, const PositionBase<Position_>& position) {
  return position*factor;
}


/*! \class Position3Base
 * \brief Interface for a position in 3D-space.
 *
 * This class defines the generic interface for a position in 3D-space.
 * More precisely an interface to store and access the three coordinates of a position of a point is provided.

 * \tparam Derived_ the derived class that should implement the position.
 *
 *  \ingroup positions
 */
template<typename Derived_>
class Position3Base : public PositionBase<Derived_> {
 public:
  /*! \brief The primitive type of a position coordinate.
   */
  typedef typename internal::get_scalar<Derived_>::Scalar Scalar;

  /*! \returns the x-coordinate of the 3D-position
   */
  inline Scalar x() const;

  /*! \returns the x-coordinate of the 3D-position
   */
  inline Scalar& x();

  /*! \returns the y-coordinate of the 3D-position
   */
  inline Scalar y() const;

  /*! \returns the y-coordinate of the 3D-position
   */
  inline Scalar& y();

  /*! \returns the z-coordinate of the 3D-position
   */
  inline Scalar z() const;

  /*! \returns the z-coordinate of the 3D-position
   */
  inline Scalar& z();
};


namespace internal {

template<typename LeftAndRight_>
class AdditionTraits<PositionBase<LeftAndRight_>> {
 public:
  /*! \returns the sum of two positions
   * \param lhs left-hand side
   * \param rhs right-hand side
   */
  inline static LeftAndRight_ add(const PositionBase<LeftAndRight_>& lhs, const PositionBase<LeftAndRight_>& rhs) {
    return LeftAndRight_(lhs.derived().toBase() + rhs.derived().toBase());
  }
  /*! \returns the subtraction of two positions
   * \param lhs left-hand side
   * \param rhs right-hand side
   */
  inline static LeftAndRight_ subtract(const PositionBase<LeftAndRight_>& lhs, const PositionBase<LeftAndRight_>& rhs) {
    return LeftAndRight_(lhs.derived().toBase() - rhs.derived().toBase());
  }
};

template<typename Position_, typename ScalarPrimType_>
class MultiplicationTraits<PositionBase<Position_>, ScalarPrimType_> {
 public:
  /*! \returns the product of a position and a scalar
   * \param lhs left-hand side (position)
   * \param rhs right-hand side (scalar)
   */
  inline static Position_ multiply(const PositionBase<Position_>& position, ScalarPrimType_ factor) {
    return Position_(position.derived().toBase() * static_cast<typename get_scalar<Position_>::Scalar>(factor));
  }
  /*! \returns the division of a position by a scalar
   * \param lhs left-hand side (position)
   * \param rhs right-hand side (scalar)
   */
  inline static Position_ divide(const PositionBase<Position_>& position, ScalarPrimType_ divisor) {
    return Position_(position.derived().toBase() / static_cast<typename get_scalar<Position_>::Scalar>(divisor));
  }
};

} // namespace internal

} // namespace positions
} // namespace kindr


#endif /* KINDR_POSITIONS_POSITIONBASE_HPP_ */
