<!-- DARK THEME README -->

<h1 align="center">
  🛡️ <span style="color:#4ade80">Title Protector</span>
</h1>

<p align="center" style="color:#8b8b8b">
  Last update: <b>12/12/2025</b><br>
  A simple protection layer that detects suspicious window titles and closes the application
</p>

---

## 🌑 About

**Title Protector** is a minimal security layer designed to detect windows with suspicious titles — usually associated with analysis tools, reverse engineering, or debugging.

When a forbidden title is detected, the application immediately terminates itself, acting as a simple but useful complementary protection.

> ⚠️ This technique is weak and should not replace real, robust protections. It is only an additional layer.

---

## ⚙️ How It Works

- Monitors currently opened window titles.
- Compares each title against a configurable list.
- If a match is found, the application closes instantly.

Common examples:

```txt
x64dbg
dnSpy
IDA
ILSpy
Process Hacker
Cheat Engine
```

All fully configurable inside the project.

---

## 🧩 Customization

The list of suspicious titles is fully editable.

- Add or remove entries anytime  
- No external dependencies  
- Keeps the project simple and lightweight  

---

## 🖼️ Preview

<p align="center">
  <img src="preview.gif" alt="Preview" width="450">
</p>

---

<p align="center" style="color:#5f5f5f">
  SilvaTweaks ❤
</p>
