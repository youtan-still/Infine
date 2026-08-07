# 更新日志 / Changelog

---
# Infine v0.0.3 — LLVM IR 生成

---

## 中文

这是 Infine 编译器的第三个版本。在 0.0.2 语法分析器和 AST 的基础上，集成了 LLVM C API，能够将 AST 生成为 LLVM IR，并输出 `output.ll` 文件。

**新增内容：**
- LLVM C API 集成
- IR 生成 `define i32 @main()`
- 输出 `output.ll` 文件
- 编译流程串联：源码 → Token → AST → IR

**运行方式：**
双击 `Infine.exe` 或在命令行中运行：`Infine.exe`  
运行后会在当前目录生成 `output.ll` 文件。

**说明：**
0.0.1 版本的克隆与提交教程已作废，请勿参照。  
1.0.0 稳定版发布之前（含 0.0.1），不接受任何外部贡献或 Pull Request。

---

## English

This is the third release of the Infine compiler. Building on the 0.0.2 parser and AST, it integrates the LLVM C API to generate LLVM IR and output an `output.ll` file.

**New in this release:**
- LLVM C API integration
- IR generation for `define i32 @main()`
- `output.ll` file output
- Full compilation pipeline: source → Token → AST → IR

**How to run:**
Double-click `Infine.exe` or run from command line: `Infine.exe`  
After running, `output.ll` will be generated in the current directory.

**Note:**
The 0.0.1 clone and submission tutorial is deprecated. Do not refer to it.  
No external contributions or Pull Requests will be accepted until the 1.0.0 stable release (including 0.0.1).

---

## 0.0.2 — 2026-08-02

### 新增 / Added

- 语法分析器（Parser）完整实现
- 抽象语法树（AST）节点定义
  - `IntegerLiteral` — 整数字面量
  - `ReturnStmt` — return 语句
  - `BlockStmt` — 代码块
  - `FunctionDecl` — 函数声明
- 递归下降解析 `func int main() { return 0; }`
- 输出 AST 结构

### 变更 / Changed

- `main.cpp` 输出信息改为 `Infine Code Compiler 0.0.2`
- 更新日志开始按版本拆分

### 说明 / Notes

**0.0.1 版本的克隆与提交教程已作废，请勿参照。**  
**1.0.0 稳定版发布之前（含 0.0.1），不接受任何外部贡献或 Pull Request。**

---

## 0.0.1 — 2026-07-28

### 新增 / Added

- 词法分析器（Lexer）原型
- 关键字：`func`, `var`, `if`, `else`, `return`, `for`, `while`, `break`, `continue`
- 标识符 / 整数 / 浮点数 / 字符串 / 字符
- 运算符和符号识别
- 行注释 `//` 和块注释 `/* */`
- 行号 / 列号追踪
- 第一个可执行文件 `Infine.exe` (216 KB)

### 说明 / Notes

**0.0.1 版本的克隆与提交教程已作废，请勿参照。**  
**1.0.0 稳定版发布之前（含 0.0.1），不接受任何外部贡献或 Pull Request。**