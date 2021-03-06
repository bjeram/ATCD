
//=============================================================================
/**
 *  @file    be_union_fwd.cpp
 *
 *  $Id$
 *
 *  Extension of class AST_UnionFwd that provides additional means for C++
 *  mapping of a union.
 *
 *
 *  @author Jeff Parsons
 */
//=============================================================================

#include "be_union_fwd.h"
#include "be_visitor.h"
#include "ast_union.h"

be_union_fwd::be_union_fwd (AST_Union *dummy,
                            UTL_ScopedName *n)
  : COMMON_Base (),
    AST_Decl (AST_Decl::NT_union_fwd,
              n),
    AST_Type (AST_Decl::NT_union_fwd,
              n),
    AST_StructureFwd (dummy,
                      n),
    AST_UnionFwd (dummy,
                  n),
    be_decl (AST_Decl::NT_union_fwd,
             n),
    be_type (AST_Decl::NT_union_fwd,
             n),
    be_structure_fwd (dummy,
                      n)
{
}

be_union_fwd::~be_union_fwd (void)
{
}

void
be_union_fwd::destroy (void)
{
  this->be_structure_fwd::destroy ();
}

int
be_union_fwd::accept (be_visitor *visitor)
{
  return visitor->visit_union_fwd (this);
}



IMPL_NARROW_FROM_DECL (be_union_fwd)
