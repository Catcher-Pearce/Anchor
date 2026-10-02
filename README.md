# Anchor

Anchor is a lightweight directory bookmarking utility built for the Fish shell.

## Requirements

- Fish shell

## Usage

```bash
anc <command> [arguments]
```

## Installation

1. Download the correct release for your computer
2. Extract the tar.gz folder
3. Run 'install.sh' in the scripts folder
4. Done!

## Commands

### Add a Bookmark

```bash
anc + <name> [directory]
```

Creates a new directory bookmark.

#### Arguments

- `<name>` — Name of the bookmark.
- `[directory]` — Directory to bookmark. If omitted, Anchor uses the current working directory.

#### Examples

Bookmark a specific directory:

```bash
anc + projects ~/Documents/projects
```

Bookmark the current directory:

```bash
anc + projects
```

---

### Remove a Bookmark

```bash
anc - <name>
```

Removes an existing bookmark.

#### Arguments

- `<name>` — Name of the bookmark to remove.

#### Example

```bash
anc - projects
```
