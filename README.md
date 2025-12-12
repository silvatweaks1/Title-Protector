<h1 align="center">
  <span style="color:#4ade80">Title Protector</span>
</h1>

<p align="center" style="color:#7f7f7f">
  Minimal window-title detection layer · Last update: 12/12/2025
</p>

---

## Overview

Title Protector is a lightweight defensive layer that checks active window titles and terminates the application if a blocked title is detected.

This is not a robust protection method. It is intended only as an additional layer.

---

## How It Works

- Monitors the titles of currently opened windows  
- Compares them against a configurable blocklist  
- Terminates the application when a match is found  

Example blocklist:

```txt
x64dbg
dnSpy
IDA
ILSpy
Process Hacker
Cheat Engine
```

---

## Configuration

The blocklist is fully editable.  
No external dependencies.  
Simple and lightweight by design.

---

## Preview

<p align="center">
  <img src="preview.gif" width="420">
</p>

---

<p align="center" style="color:#5f5f5f">
  SilvaTweaks
</p>
