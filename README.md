# ZIDE 🎨 - AN OPENSOURCE APPLICATION TO CREATE PIXEL ART

## What is ZIDE ?
**Zide** (abbr. Zide Is a Design Environment) is a cross-platform pixel art editor designed to provide artists with a minimalistic, easy-to-use interface. Whether you're creating a simple sprite or an intricate animation, Zide offers all the essential tools you need to bring your art to life.


## [Check out our demo video ✌🏽](https://youtu.be/fCd_rc3UOm4)

# Table of Contents

- [Motivation](#motivation)
- [Features](#features)
# ZIDE 🎨 — Minimal open-source pixel art editor

Zide (Zide Is a Design Environment) is a lightweight, cross-platform pixel art editor focused on creating sprites and simple 2D animations. The project aims to be minimal and approachable while providing the essential pixel-art workflow.

Demo: https://youtu.be/fCd_rc3UOm4

## Contents

- Motivation
- Features
- Installation
- Usage
- Notes & license

## Motivation

Many pixel-art tools are either commercial or targeted at broader image editing workflows. Zide exists to provide an open, focused editor that does pixel art well without extra clutter.

## Features

- Freehand pixel drawing (draw / erase / fill)
- Multiple frames / basic animation timeline
- Pan & zoom controls
- Import color palettes (.gpl)
- Export sprite sheets

Note: Some image links in the original README pointed to external attachment services and were removed for clarity. Feel free to re-add screenshots to `assets/`.

## Installation

Prerequisites

- Git
- A C/C++ toolchain and CMake (the project uses CMake)

Clone

```bash
git clone https://github.com/jeevansridharan/zide.git
cd zide
```

Build (recommended)

This project contains platform-agnostic CMake build files and helper scripts in `scripts/`.

- Using the provided scripts (Unix-like shells):

  ```bash
  ./scripts/rebuild_and_run_app.sh
  # or
  ./scripts/run_app.sh
  ```

- On Windows you can build with CMake directly (PowerShell example):

  ```powershell
  mkdir build; cd build
  cmake ..
  cmake --build . --config Release
  ```

If you prefer, use WSL or Git Bash to run the included shell scripts.

For more details, check `INSTALL.md` and `CMakeLists.txt`.

## Usage

1. Start the app.
2. Create a new project and set sprite dimensions.
3. Draw using the pencil, fill with the bucket, and use undo/redo.
4. Add frames to create animations and export as a sprite sheet.

## Notes & license

- The repository includes third-party vendor code under various open-source licenses (see `vendor/` for per-package license information). Some vendor libraries are MIT-licensed.
- There is no top-level `LICENSE` file in the repository root; if you are the project owner and intend this project to be MIT-licensed, consider adding a top-level `LICENSE` file for clarity.

If you'd like, I can:

- Add screenshots to `assets/` and wire them into this README.
- Create a top-level `LICENSE` file if you confirm the desired license.
