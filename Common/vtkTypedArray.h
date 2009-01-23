/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTypedArray.h
  
-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkTypedArray - Provides a type-specific interface to N-way arrays
//
// .SECTION Description
// vtkTypedArray provides an interface for retrieving and updating data in an
// arbitrary-dimension array.  It derives from vtkArray and is templated on the
// type of value stored in the array.
//
// Methods are provided for retrieving and updating array values based either
// on their array coordinates, or on a 1-dimensional integer index.  The latter
// approach can be used to iterate over the values in an array in arbitrary order,
// which is useful when writing filters that operate efficiently on sparse arrays
// and arrays that can have any number of dimensions.
//
// Special overloaded methods provide simple access for arrays with one, two, or
// three dimensions.
//
// .SECTION See Also
// vtkArray, vtkDenseArray, vtkSparseArray
//
// .SECTION Thanks
// Developed by Timothy M. Shead (tshead@sandia.gov) at Sandia National Laboratories.

#ifndef __vtkTypedArray_h
#define __vtkTypedArray_h

#include "vtkArray.h"
#include "vtkTypeTemplate.h"

class vtkArrayCoordinates;

template<typename T>
class vtkTypedArray : public vtkTypeTemplate<vtkTypedArray<T>, vtkArray>
{
public:
  using vtkArray::GetVariantValue;
  using vtkArray::SetVariantValue;

  void PrintSelf(ostream &os, vtkIndent indent);

  // vtkArray API
  virtual vtkVariant GetVariantValue(const vtkArrayCoordinates& coordinates);
  virtual vtkVariant GetVariantValueN(const vtkIdType n);
  virtual void SetVariantValue(const vtkArrayCoordinates& coordinates, const vtkVariant& value);
  virtual void SetVariantValueN(const vtkIdType n, const vtkVariant& value);

  // Description:
  // Returns the value stored in the array at the given coordinates.
  // Note that the number of dimensions in the supplied coordinates must
  // match the number of dimensions in the array.
  inline const T& GetValue(vtkIdType i);
  inline const T& GetValue(vtkIdType i, vtkIdType j);
  inline const T& GetValue(vtkIdType i, vtkIdType j, vtkIdType k);
  virtual const T& GetValue(const vtkArrayCoordinates& coordinates) = 0;
  
  // Description:
  // Returns the n-th value stored in the array, where n is in the
  // range [0, GetNonNullSize()).  This is useful for efficiently
  // visiting every value in the array.  Note that the order in which
  // values are visited is undefined, but is guaranteed to match the
  // order used by vtkArray::GetCoordinatesN().
  virtual const T& GetValueN(const vtkIdType n) = 0;
  
  // Description:
  // Overwrites the value stored in the array at the given coordinates.
  // Note that the number of dimensions in the supplied coordinates must
  // match the number of dimensions in the array.
  inline void SetValue(vtkIdType i, const T& value);
  inline void SetValue(vtkIdType i, vtkIdType j, const T& value);
  inline void SetValue(vtkIdType i, vtkIdType j, vtkIdType k, const T& value);
  virtual void SetValue(const vtkArrayCoordinates& coordinates, const T& value) = 0;
  
  // Description:
  // Overwrites the n-th value stored in the array, where n is in the
  // range [0, GetNonNullSize()).  This is useful for efficiently
  // visiting every value in the array.  Note that the order in which
  // values are visited is undefined, but is guaranteed to match the
  // order used by vtkArray::GetCoordinatesN().
  virtual void SetValueN(const vtkIdType n, const T& value) = 0;

protected:
  vtkTypedArray() {}
  ~vtkTypedArray() {}

private:
  vtkTypedArray(const vtkTypedArray&); // Not implemented
  void operator=(const vtkTypedArray&); // Not implemented
};

#include "vtkTypedArray.txx"

#endif

