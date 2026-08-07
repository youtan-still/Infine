// -----------------------------------------------------------------------------
// Infine 语言开发工具
// 作者：游潭 (youtan)（AI 辅助生成：Deepseek V4 Flash）
// 版本：0.0.3
// 日期：2026-08-02
// 路径：ICC/src/ast/FunctionDecl.cpp
// -----------------------------------------------------------------------------

#include "FunctionDecl.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>

namespace infine {

    FunctionDecl::FunctionDecl(std::string n, std::string rt,
        std::unique_ptr<BlockStmt> b)
        : name(std::move(n)), returnType(std::move(rt)), body(std::move(b)) {
    }

    std::string FunctionDecl::print() const {
        return "FunctionDecl(" + name + ", " + returnType + ", " +
            (body ? body->print() : "null") + ")";
    }

    llvm::Value* FunctionDecl::codegen(llvm::LLVMContext& context) {
        // 创建 Module
        module = new llvm::Module("Infine", context);

        // 创建函数类型：i32 main()
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(context), {}, false
        );

        // 创建函数
        llvm::Function* func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            name,
            module
        );

        // 创建入口基本块
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
        llvm::IRBuilder<> builder(context);
        builder.SetInsertPoint(entry);

        if (body) {
            body->codegen(context);
        }

        llvm::verifyFunction(*func);
        return func;
    }

} // namespace infine