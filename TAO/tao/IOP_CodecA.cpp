// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#include "IOP_CodecC.h"
#include "tao/Null_RefCount_Policy.h"
#include "tao/TypeCode_Constants.h"
#include "tao/Alias_TypeCode.h"
#include "tao/Objref_TypeCode.h"
#include "tao/Struct_TypeCode.h"
#include "tao/CDR.h"
#include "tao/Any.h"
#include "tao/Any_Impl_T.h"
#include "tao/Any_Dual_Impl_T.h"

// TAO_IDL - Generated from
// be\be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> const _tao_fields_IOP_Codec_InvalidTypeForEncoding[] =
  {
    
  };

static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_except,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_Codec_InvalidTypeForEncoding (
    "IDL:omg.org/IOP/Codec/InvalidTypeForEncoding:1.0",
    "InvalidTypeForEncoding",
    _tao_fields_IOP_Codec_InvalidTypeForEncoding,
    0);
  
::CORBA::TypeCode_ptr const IOP::Codec::_tc_InvalidTypeForEncoding =
  &_tao_tc_IOP_Codec_InvalidTypeForEncoding;

// TAO_IDL - Generated from
// be\be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> const _tao_fields_IOP_Codec_FormatMismatch[] =
  {
    
  };

static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_except,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_Codec_FormatMismatch (
    "IDL:omg.org/IOP/Codec/FormatMismatch:1.0",
    "FormatMismatch",
    _tao_fields_IOP_Codec_FormatMismatch,
    0);
  
::CORBA::TypeCode_ptr const IOP::Codec::_tc_FormatMismatch =
  &_tao_tc_IOP_Codec_FormatMismatch;

// TAO_IDL - Generated from
// be\be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> const _tao_fields_IOP_Codec_TypeMismatch[] =
  {
    
  };

static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_except,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_Codec_TypeMismatch (
    "IDL:omg.org/IOP/Codec/TypeMismatch:1.0",
    "TypeMismatch",
    _tao_fields_IOP_Codec_TypeMismatch,
    0);
  
::CORBA::TypeCode_ptr const IOP::Codec::_tc_TypeMismatch =
  &_tao_tc_IOP_Codec_TypeMismatch;

// TAO_IDL - Generated from
// be\be_visitor_typecode/objref_typecode.cpp:73

static TAO::TypeCode::Objref<char const *,
                             CORBA::tk_local_interface,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_Codec (
    "IDL:omg.org/IOP/Codec:1.0",
    "Codec");
  
namespace IOP
{
  ::CORBA::TypeCode_ptr const _tc_Codec =
    &_tao_tc_IOP_Codec;
}



// TAO_IDL - Generated from
// be\be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_IOP_EncodingFormat (
    "IDL:omg.org/IOP/EncodingFormat:1.0",
    "EncodingFormat",
    &::_tao_tc_CORBA::_tc_short);
  
namespace IOP
{
  ::CORBA::TypeCode_ptr const _tc_EncodingFormat =
    &_tao_tc_IOP_EncodingFormat;
}



// TAO_IDL - Generated from
// be\be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> const _tao_fields_IOP_Encoding[] =
  {
    { "format", &IOP::_tc_EncodingFormat },
    { "major_version", &CORBA::_tc_octet },
    { "minor_version", &CORBA::_tc_octet }
    
  };

static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_struct,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_Encoding (
    "IDL:omg.org/IOP/Encoding:1.0",
    "Encoding",
    _tao_fields_IOP_Encoding,
    3);
  
namespace IOP
{
  ::CORBA::TypeCode_ptr const _tc_Encoding =
    &_tao_tc_IOP_Encoding;
}



// TAO_IDL - Generated from
// be\be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> const _tao_fields_IOP_CodecFactory_UnknownEncoding[] =
  {
    
  };

static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_except,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_CodecFactory_UnknownEncoding (
    "IDL:omg.org/IOP/CodecFactory/UnknownEncoding:1.0",
    "UnknownEncoding",
    _tao_fields_IOP_CodecFactory_UnknownEncoding,
    0);
  
::CORBA::TypeCode_ptr const IOP::CodecFactory::_tc_UnknownEncoding =
  &_tao_tc_IOP_CodecFactory_UnknownEncoding;

// TAO_IDL - Generated from
// be\be_visitor_typecode/objref_typecode.cpp:73

static TAO::TypeCode::Objref<char const *,
                             CORBA::tk_local_interface,
                             TAO::Null_RefCount_Policy>
  _tao_tc_IOP_CodecFactory (
    "IDL:omg.org/IOP/CodecFactory:1.0",
    "CodecFactory");
  
namespace IOP
{
  ::CORBA::TypeCode_ptr const _tc_CodecFactory =
    &_tao_tc_IOP_CodecFactory;
}



// TAO_IDL - Generated from
// be\be_visitor_interface/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::Codec>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::Codec>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::Codec>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    IOP::Codec_ptr _tao_elem
  )
{
  IOP::Codec_ptr _tao_objptr =
    IOP::Codec::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

// Non-copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    IOP::Codec_ptr *_tao_elem
  )
{
  TAO::Any_Impl_T<IOP::Codec>::insert (
      _tao_any,
      IOP::Codec::_tao_any_destructor,
      IOP::_tc_Codec,
      *_tao_elem
    );
}

CORBA::Boolean
operator>>= (
    const CORBA::Any &_tao_any,
    IOP::Codec_ptr &_tao_elem
  )
{
  return
    TAO::Any_Impl_T<IOP::Codec>::extract (
        _tao_any,
        IOP::Codec::_tao_any_destructor,
        IOP::_tc_Codec,
        _tao_elem
      );
}

// TAO_IDL - Generated from 
// be\be_visitor_exception/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::InvalidTypeForEncoding>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::InvalidTypeForEncoding>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const IOP::Codec::InvalidTypeForEncoding &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::InvalidTypeForEncoding>::insert_copy (
      _tao_any,
      IOP::Codec::InvalidTypeForEncoding::_tao_any_destructor,
      IOP::Codec::_tc_InvalidTypeForEncoding,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    IOP::Codec::InvalidTypeForEncoding *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::InvalidTypeForEncoding>::insert (
      _tao_any,
      IOP::Codec::InvalidTypeForEncoding::_tao_any_destructor,
      IOP::Codec::_tc_InvalidTypeForEncoding,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    IOP::Codec::InvalidTypeForEncoding *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const IOP::Codec::InvalidTypeForEncoding *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const IOP::Codec::InvalidTypeForEncoding *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<IOP::Codec::InvalidTypeForEncoding>::extract (
        _tao_any,
        IOP::Codec::InvalidTypeForEncoding::_tao_any_destructor,
        IOP::Codec::_tc_InvalidTypeForEncoding,
        _tao_elem
      );
}

// TAO_IDL - Generated from 
// be\be_visitor_exception/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::FormatMismatch>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::FormatMismatch>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const IOP::Codec::FormatMismatch &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::FormatMismatch>::insert_copy (
      _tao_any,
      IOP::Codec::FormatMismatch::_tao_any_destructor,
      IOP::Codec::_tc_FormatMismatch,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    IOP::Codec::FormatMismatch *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::FormatMismatch>::insert (
      _tao_any,
      IOP::Codec::FormatMismatch::_tao_any_destructor,
      IOP::Codec::_tc_FormatMismatch,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    IOP::Codec::FormatMismatch *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const IOP::Codec::FormatMismatch *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const IOP::Codec::FormatMismatch *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<IOP::Codec::FormatMismatch>::extract (
        _tao_any,
        IOP::Codec::FormatMismatch::_tao_any_destructor,
        IOP::Codec::_tc_FormatMismatch,
        _tao_elem
      );
}

// TAO_IDL - Generated from 
// be\be_visitor_exception/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::TypeMismatch>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::Codec::TypeMismatch>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const IOP::Codec::TypeMismatch &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::TypeMismatch>::insert_copy (
      _tao_any,
      IOP::Codec::TypeMismatch::_tao_any_destructor,
      IOP::Codec::_tc_TypeMismatch,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    IOP::Codec::TypeMismatch *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Codec::TypeMismatch>::insert (
      _tao_any,
      IOP::Codec::TypeMismatch::_tao_any_destructor,
      IOP::Codec::_tc_TypeMismatch,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    IOP::Codec::TypeMismatch *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const IOP::Codec::TypeMismatch *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const IOP::Codec::TypeMismatch *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<IOP::Codec::TypeMismatch>::extract (
        _tao_any,
        IOP::Codec::TypeMismatch::_tao_any_destructor,
        IOP::Codec::_tc_TypeMismatch,
        _tao_elem
      );
}

// TAO_IDL - Generated from 
// be\be_visitor_structure/any_op_cs.cpp:54

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const IOP::Encoding &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Encoding>::insert_copy (
      _tao_any,
      IOP::Encoding::_tao_any_destructor,
      IOP::_tc_Encoding,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    IOP::Encoding *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::Encoding>::insert (
      _tao_any,
      IOP::Encoding::_tao_any_destructor,
      IOP::_tc_Encoding,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    IOP::Encoding *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const IOP::Encoding *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const IOP::Encoding *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<IOP::Encoding>::extract (
        _tao_any,
        IOP::Encoding::_tao_any_destructor,
        IOP::_tc_Encoding,
        _tao_elem
      );
}

// TAO_IDL - Generated from
// be\be_visitor_interface/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::CodecFactory>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::CodecFactory>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<IOP::CodecFactory>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    IOP::CodecFactory_ptr _tao_elem
  )
{
  IOP::CodecFactory_ptr _tao_objptr =
    IOP::CodecFactory::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

// Non-copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    IOP::CodecFactory_ptr *_tao_elem
  )
{
  TAO::Any_Impl_T<IOP::CodecFactory>::insert (
      _tao_any,
      IOP::CodecFactory::_tao_any_destructor,
      IOP::_tc_CodecFactory,
      *_tao_elem
    );
}

CORBA::Boolean
operator>>= (
    const CORBA::Any &_tao_any,
    IOP::CodecFactory_ptr &_tao_elem
  )
{
  return
    TAO::Any_Impl_T<IOP::CodecFactory>::extract (
        _tao_any,
        IOP::CodecFactory::_tao_any_destructor,
        IOP::_tc_CodecFactory,
        _tao_elem
      );
}

// TAO_IDL - Generated from 
// be\be_visitor_exception/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::CodecFactory::UnknownEncoding>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Dual_Impl_T<IOP::CodecFactory::UnknownEncoding>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const IOP::CodecFactory::UnknownEncoding &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::CodecFactory::UnknownEncoding>::insert_copy (
      _tao_any,
      IOP::CodecFactory::UnknownEncoding::_tao_any_destructor,
      IOP::CodecFactory::_tc_UnknownEncoding,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    IOP::CodecFactory::UnknownEncoding *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<IOP::CodecFactory::UnknownEncoding>::insert (
      _tao_any,
      IOP::CodecFactory::UnknownEncoding::_tao_any_destructor,
      IOP::CodecFactory::_tc_UnknownEncoding,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    IOP::CodecFactory::UnknownEncoding *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const IOP::CodecFactory::UnknownEncoding *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const IOP::CodecFactory::UnknownEncoding *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<IOP::CodecFactory::UnknownEncoding>::extract (
        _tao_any,
        IOP::CodecFactory::UnknownEncoding::_tao_any_destructor,
        IOP::CodecFactory::_tc_UnknownEncoding,
        _tao_elem
      );
}
