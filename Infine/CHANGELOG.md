# 更新日志 / Changelog

---

## 0.0.5 — 2026-08-18

### 新增 / Added

- 完整编译流程：源码 → IR → 目标文件 → 可执行文件
- 支持命令行参数：`Infine.exe <源文件.ic>` 生成 `a.exe`
- 使用 `llc -filetype=obj` 生成 COFF 目标文件
- 使用 `lld-link` 链接生成 Windows 可执行文件
- 错误处理：编译失败时输出错误信息并返回非 0 退出码
- 控制台交互：结束时等待用户按键（防止闪退）

### 变更 / Changed

- 移除 `LLVMTargetMachineEmitToFile` 依赖（改用 `llc` 外部工具）
- 移除所有硬编码路径，依赖系统 PATH 中的 LLVM 工具链

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