# activate-linux-gtk4

A translucent "Activate Linux" watermark overlay for Wayland desktops — inspired by the Windows activation watermark.

Built with GTK4 and the [gtk4-layer-shell](https://github.com/wmww/gtk4-layer-shell) protocol.

---

## Preview

Displays two lines of text anchored to the bottom-right corner of your screen:

---

## Dependencies

- `pkg-config`
- `libgtk4`
- `libgtk4-layer-shell`

---

## Build

```sh
./build.sh
```

---

## Usage

### Options

| Flag | Long form | Description | Default |
|------|-----------|-------------|---------|
| `-x` | `--text1` | Primary text | `Activate Linux` |
| `-e` | `--style1` | Style for primary text | `Normal` |
| `-o` | `--font1` | Font family for primary text | system default |
| `-y` | `--text2` | Secondary text | `Go to Settings to activate Linux.` |
| `-f` | `--style2` | Style for secondary text | `Normal` |
| `-p` | `--font2` | Font family for secondary text | system default |
| `-s` | `--scale` | Scale factor (float) | `1.0` |
| `-w` | `--hshift` | Horizontal offset in pixels | `330` |
| `-v` | `--vshift` | Vertical offset in pixels | `115` |
| `-r` | `--rgba` | Text color as `R,G,B,A` (0–255) | `196,196,196,102` |

**Supported styles:** `Normal`, `Italic`, `Oblique`, `Bold`, `Underline`, `Underline_single`, `Underline_double`, `Strike`

### Examples

```sh
./bin/release/main --text1 "Activate Arch" --text2 "Go to Settings to activate Arch." --rgba "255,100,100,128" --scale 1.5 --font1 "Monospace" --font2 "Monospace"
```

---

## License

[MIT](LICENSE)
