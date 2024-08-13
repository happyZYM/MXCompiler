#include "structural_astnode.h"
#include <stdexcept>
#include "astnode_visitor.h"

#define SetAutoAccept(name)                                              \
  void name::accept(class ASTNodeVisitorBase *visitor) {                 \
    if (auto v = dynamic_cast<ASTNodeVirturalVisitor *>(visitor)) {      \
      v->ActuralVisit(this);                                             \
    } else                                                               \
      throw std::runtime_error("Cannot automatically dispatch visitor"); \
  }

SetAutoAccept(FuncDef_ASTNode);
SetAutoAccept(ClassDef_ASTNode);
SetAutoAccept(Program_ASTNode);
#undef SetAutoAccpet