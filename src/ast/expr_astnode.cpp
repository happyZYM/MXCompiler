#include "expr_astnode.h"
#include <stdexcept>
#include "astnode_visitor.h"
#define SetAutoAccept(name)                                              \
  void name::accept(class ASTNodeVisitorBase *visitor) {                 \
    if (auto v = dynamic_cast<ASTNodeVirturalVisitor *>(visitor)) {      \
      v->ActuralVisit(this);                                             \
    } else                                                               \
      throw std::runtime_error("Cannot automatically dispatch visitor"); \
  }
SetAutoAccept(NewArrayExpr_ASTNode);
SetAutoAccept(NewConstructExpr_ASTNode);
SetAutoAccept(NewExpr_ASTNode);
SetAutoAccept(AccessExpr_ASTNode);
SetAutoAccept(IndexExpr_ASTNode);
SetAutoAccept(SuffixExpr_ASTNode);
SetAutoAccept(PrefixExpr_ASTNode);
SetAutoAccept(OppositeExpr_ASTNode);
SetAutoAccept(LNotExpr_ASTNode);
SetAutoAccept(BNotExpr_ASTNode);
SetAutoAccept(MDMExpr_ASTNode);
SetAutoAccept(PMExpr_ASTNode);
SetAutoAccept(RLExpr_ASTNode);
SetAutoAccept(GGLLExpr_ASTNode);
SetAutoAccept(NEExpr_ASTNode);
SetAutoAccept(BAndExpr_ASTNode);
SetAutoAccept(BXorExpr_ASTNode);
SetAutoAccept(BOrExpr_ASTNode);
SetAutoAccept(LAndExpr_ASTNode);
SetAutoAccept(LOrExpr_ASTNode);
SetAutoAccept(TernaryExpr_ASTNode);
SetAutoAccept(AssignExpr_ASTNode);
SetAutoAccept(ThisExpr_ASTNode);
SetAutoAccept(ParenExpr_ASTNode);
SetAutoAccept(IDExpr_ASTNode);
SetAutoAccept(FunctionCallExpr_ASTNode);
SetAutoAccept(FormattedStringExpr_ASTNode);
SetAutoAccept(ConstantExpr_ASTNode);
#undef SetAutoAccept