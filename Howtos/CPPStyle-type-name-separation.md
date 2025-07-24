# Proposal: Visually Separate Type and Variable Name with a Tab

## 📌 Goal

Introduce a simple formatting convention for variable declarations in C++ code:

> Use **a tab** (or equivalent visual spacing) between the **type** and the **variable name**.

### ✅ Motivation

- **Enhance readability**: Clean visual separation between types and variable names improves skimmability, especially when working with long or templated types.
- **Improve maintainability**: Even when full alignment is lost over time, this rule preserves a consistent visual structure.
- **Aid parsing** (by humans and tools): The separation helps developers quickly scan for types or instances in dense declarations.

---

## ✍️ Style Example

Instead of this:

```cpp
std::unique_ptr<Impl> pImpl;  // Pointer to implementation
int n;
MyCustomLongTemplateType<> myVar;
```

Prefer this:

```cpp
std::unique_ptr<Impl>         pImpl;   // Pointer to implementation
int                           n;
MyCustomLongTemplateType<>    myVar;
```

Or, after some evolution:

```cpp
std::unique_ptr<ImplV2>       pImpl;   // Pointer to implementation
int                           n;
MyCustomLongTemplateType<xy>  myVar;
```

Even if the spacing is no longer aligned perfectly, the consistent tab (or wide space) maintains clarity.

---

## ✅ How to Accomplish This

### 🛠 Tooling Support

- Can be **automated** with custom formatting scripts, IDE macros, or potential extensions to `clang-format`.
- Smart IDEs and AI-based tools can easily identify type/name boundaries via the AST and insert spacing accordingly.
- Teams can agree to use a consistent `.editorconfig` or IDE settings (e.g., tabs rendered as 4 spaces).

### 🔄 Diff Tools

- Most modern diff tools support **ignoring whitespace differences**:
  - `git diff -w`
  - Visual Studio Code diff viewer
  - Beyond Compare, Meld, etc.

---

## ❌ Responses to Common Objections

| Objection | Response |
|----------|----------|
| **“Edits break alignment”** | This isn’t about *perfect* alignment — just visual separation. Even when types/names change, the spacing still improves clarity. |
| **“Tabs render inconsistently”** | That’s a **configuration issue**, not a design flaw. Teams already enforce tab width in `.editorconfig`. |
| **“Tooling doesn’t support this”** | Tooling can. Formatters like `clang-format` or `clang-tidy` could support this with minor tweaks. IDE extensions or AI-based formatting already make it easy. |
| **“Creates noisy diffs”** | Diffs can **ignore whitespace**. This is a non-issue if proper tools and practices are used. |

---

## 💬 Summary

This proposal encourages a formatting convention where:
- A **tab or consistent visual gap** separates the type from the variable name.
- It's **not about alignment**, but about improving **readability, structure, and parsing**.
- It works **even when spacing shifts**, unlike strict alignment-based formatting.
- It can be **supported with tooling**, **respects diffs**, and improves **code clarity** for humans.

---

## 📘 Suggested Rule (Style Guide Format)

> **Type-Name Separation Rule**  
> When declaring variables, use a **tab character** (or equivalent visual gap) after the type and before the variable name:
> 
> ```cpp
> std::shared_ptr<Widget>       widget;
> std::vector<std::string>      names;
> MyCustomTypeWithParams<>      config;
> ```
> 
> - Not strict alignment; just separation.
> - Keeps variable declarations visually clear.
> - Tooling/formatters may optionally enforce this.