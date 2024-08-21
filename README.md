# webspeeddial

A speed dial system for websites

## Installation

There are no real packages at the moment only the NixOS Flake.

### Source

Download the `main.py` file and run this file with `python3`. This doesn't require any further dependencies.

### NixOS

Simply install the flake `github:larszauberer/webspeeddial` in the `#default` derivation.

## Usage

The script uses a config loacted at `~/.config/webspeeddial/config.json`. It is constructed of the form

```json
{
  "runner": "fzf",
  "bookmarks": [
    {
      "name": "YouTube",
      "address": "https://youtube.com"
    },
    {
      "name": "Some Website",
      "address": "https://someotherwebsite"
    }
  ]
}
```

You can also use `wofi` to view the speeddial bookmarks. Just replace `fzf` in the `runner` with `wofi --dmenu -i`.

Now, you can just run the script (or on NixOS run `webspeeddial`)
