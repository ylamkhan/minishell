# 🐚 Minishell

**Minishell** is a simple shell implementation developed as part of the **1337 School curriculum**.  
It reproduces the behavior of a UNIX shell like **bash** while teaching fundamental concepts of processes, file descriptors, parsing, and signals.  

---

## 📖 Project Overview

The goal of **minishell** is to create a functional shell that:  
- Parses and executes commands.  
- Handles redirections and pipes.  
- Manages environment variables.  
- Implements a subset of bash built-in commands.  
- Correctly responds to signals.  

This project strengthens knowledge of:  
- **System calls** (`fork`, `execve`, `pipe`, `dup2`, `waitpid`, etc.)  
- **Parsing & tokenization**  
- **Environment & process management**  
- **File descriptors & redirections**  
- **Signal handling** (`SIGINT`, `SIGQUIT`, EOF)  
- **Memory management** in C  

---

## 🚀 Mandatory Features

- ✅ **Prompt** that waits for user input.  
- ✅ **Command execution** (absolute & relative paths).  
- ✅ **Built-in commands**:
  - `echo` with option `-n`  
  - `cd` (with relative & absolute paths)  
  - `pwd` (print current working directory)  
  - `export` (set environment variables)  
  - `unset` (remove environment variables)  
  - `env` (list environment variables)  
  - `exit` (terminate shell)  
- ✅ **Redirections**:
  - `<` Input redirection  
  - `>` Output redirection (truncate)  
  - `>>` Output redirection (append)  
  - `<<` Heredoc (until a delimiter)  
- ✅ **Pipes** (`cmd1 | cmd2 | cmd3`)  
- ✅ **Environment variable expansion** (`$VAR`)  
- ✅ **Exit status** (`$?`)  
- ✅ **Signal handling**:
  - `CTRL+C` → New prompt on newline  
  - `CTRL+D` → Exit shell  
  - `CTRL+\` → Ignored  

---

## 🌟 Bonus Features

- ✅ **Command history** (via GNU readline)  
- ✅ **Wildcards `*`** for pathname expansion  
- ✅ **Logical operators** (`&&`, `||`)  
- ✅ **Parentheses** for priority in commands  
- ✅ **Job control** (background `&`)  
- ✅ **Improved error handling** (syntax errors, invalid redirects, etc.)  

---

## 🛠️ Requirements

- **C language** (C99 standard)  
- **GNU readline library** (for input & history)  
- **Makefile** with rules: `all`, `clean`, `fclean`, `re`  

Install readline (Linux):  
```bash
sudo apt-get install libreadline-dev
