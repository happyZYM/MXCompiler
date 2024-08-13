#include "statement_astnode.h"
#include <stdexcept>
#include "astnode_visitor.h"
#define SetAutoAccept(name)                                              \
  void name::accept(class ASTNodeVisitorBase *visitor) {                 \
    if (auto v = dynamic_cast<ASTNodeVirturalVisitor *>(visitor)) {      \
      v->ActuralVisit(this);                                             \
    } else                                                               \
      throw std::runtime_error("Cannot automatically dispatch visitor"); \
  }

SetAutoAccept(EmptyStatement_ASTNode);
SetAutoAccept(DefinitionStatement_ASTNode);
SetAutoAccept(ExprStatement_ASTNode);
SetAutoAccept(IfStatement_ASTNode);
SetAutoAccept(WhileStatement_ASTNode);
SetAutoAccept(ForStatement_ASTNode);
SetAutoAccept(JmpStatement_ASTNode);
SetAutoAccept(SuiteStatement_ASTNode);

#undef SetAutoAccept