# Webspeeddial

A speed dial system for websites and files

## Installation

### Gentoo

There is an ebuild on [lentoo](https://github.com/LarsZauberer/lentoo) under `app-misc` to install the package.

## Usage

The script uses a config loacted at `~/.config/webspeeddial/config.yml`. It is constructed of the form

```yml
runner: fzf
bookmarks:
- name: Webspeeddial
  link: https://github.com/LarsZauberer/webspeeddial
- name: Some Website
  link: https://example.com
```

You can also use `wofi` to view the speeddial bookmarks. Just replace `fzf` in the `runner` with `wofi --dmenu -i`.
