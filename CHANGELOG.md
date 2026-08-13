# 更新日志 / Changelog

---

## 0.0.4 — 2026-08-13

### 新增 / Added

- 所有 AST 节点实现 `codegen` 方法，支持自主生成 LLVM IR
- `FunctionDecl::codegen` 使用纯 LLVM C API 重写
- 完整编译流程串联：词法分析 → 语法分析 → IR 生成 → 输出 `output.ll`
- 项目配置改用相对路径引用 LLVM 库（`$(ProjectDir)..\third_party\...`）

### 变更 / Changed

- 移除所有 LLVM C++ API 依赖，统一使用 `llvm-c/Core.h`
- 更新源码注释头格式（移除版本号、许可证、路径信息）

---

## 0.0.3 — 2026-08-03

### 新增 / Added

- 集成 LLVM C API，支持生成 `define i32 @main()` 的硬编码 IR
- 输出 `output.ll` 文件

### 变更 / Changed

- 编译流程串联：源码 → Token → AST → IR
- `ast/` 和 `parser/` 模块启用编译

---

## 0.0.2 — 2026-08-02

### 新增 / Added

- 完整语法分析器实现（`Parser`）
- AST 节点定义（`BlockStmt`、`ReturnStmt`、`IntegerLiteral`、`FunctionDecl`）
- 语法分析支持 `func`、`return`、整数、块语句

---

## 0.0.1 — 2026-08-01

### 新增 / Added

- 基础词法分析器（`Lexer`）
- Token 类型定义（`Token`）
- 项目初始结构（`src/` 目录划分）