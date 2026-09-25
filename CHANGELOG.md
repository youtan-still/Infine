# 更新日志 / Changelog

---

## 0.0.7 — 2026-09-25

### 新增 / Added

- 支持在一个源文件中声明多个函数
- 新增 `ProgramDecl` 顶层容器节点，统一管理所有函数声明
- 所有函数共享同一个 `LLVMModuleRef`，生成单一 IR 模块
- 词法/语法分析阶段的异常被捕获，输出错误信息后干净退出（退出码非 0）
- CLI 交互模式默认启用：无参数运行 `Infine` 直接进入命令行界面

### 变更 / Changed

- `Parser::parseProgram()` 改为循环解析所有顶层函数
- `compileSource` 增加 `try-catch`，避免解析失败导致程序崩溃
- 帮助信息中的 `Usage` 改为 `Infine <command> [filename]`

---

## 0.0.6 — 2026-09-05

### 新增 / Added

- 交互式 CLI 模式：无参数运行 `Infine` 进入命令行交互环境
- 支持 `build <filename.ic>` 和 `run <filename.ic>` 命令
- CLI 内置命令：`help`、`exit`、`clear`、`version`、`history`
- `--version` 显示 `Infine 0.0.6`
- 错误信息输出到 `stderr`，文件不存在时给出明确提示

### 变更 / Changed

- 从文件读取源码，替换硬编码字符串
- 重构 `compileSource` 函数，支持直接编译内存中的源码
- 所有对外输出统一使用 `Infine`，不再出现 `ICC` 字样
- 帮助信息中 `Usage` 改为 `Infine <command> [filename]`
- 无参数运行时自动进入 CLI 交互模式

---

## 0.0.5 — 2026-08-18

### 新增 / Added

- 完整编译流程：从 `.ic` 源文件生成 Windows 可执行文件（`.exe`）
- 调用 `llc` 将 LLVM IR 编译为目标文件（`.obj`）
- 调用 `lld-link` 链接生成 `.exe`，支持无运行时依赖（`/nodefaultlib` + `/entry:main`）
- 命令行参数支持：`Infine.exe <源文件.ic>`
- 自动清理临时文件（`output.ll`、`output.obj`）
- 错误处理与友好提示，编译失败返回非 0 退出码

### 变更 / Changed

- 重构 `main.cpp`：移除 LLVM Target C API（避免格式兼容问题），改用稳定的系统工具链调用
- 所有外部工具调用依赖系统 `PATH`，无硬编码路径，便于分发

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