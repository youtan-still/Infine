# 更新日志 / Changelog

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