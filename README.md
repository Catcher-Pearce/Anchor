# Anchor

Anchor is a lightweight directory bookmarking utility built for the Fish shell.

## Requirements

- Fish shell

## Installation

1. Download the correct release for your computer
2. Extract the tar.gz folder
3. Run 'install.sh' in the scripts folder
4. Done!

## Usage

```bash
anc <command> [arguments]
```

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

---

### Go to a Bookmark

```bash
anc <name>
```

Changes working directing to path specified by the bookmark name.

#### Arguments

- `<name>` — Name of the bookmark to go to.

#### Example

```bash
anc projects
```

---

## Additional

### Viewing all Bookmarks

**Anchor comes preinstalled with a single bookmark: The directory containing your bookmark persistence file.**

To go to this directory, use:

```bash
anc anchors
```

Look for the txt file named 'bookmarks.txt'.

This is the file containing all of your bookmarks, you can view and edit them from here.

