#!/usr/bin/env bash
set -eu

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

if ! command -v fish >/dev/null 2>&1; then
    printf 'ERROR: Unable to find fish installation\n'
    exit 1
fi

printf 'Creating installation directories...\n'
mkdir -p "$HOME/.local/bin" "$HOME/.config/fish/functions" \
    "$HOME/.config/fish/completions"

printf 'Installing Anchor to %s...\n' "$HOME/.local/bin/anchor"
install -m 755 "$script_dir/../anchor" "$HOME/.local/bin/anchor"
printf 'Installing the anc Fish function...\n'
install -m 644 "$script_dir/Anchor.fish" \
    "$HOME/.config/fish/functions/anc.fish"
install -m 644 "$script_dir/AnchorCompletions.fish" \
    "$HOME/.config/fish/completions/anc.fish"


cat <<'EOF'

Anchor installed successfully!

Open a new Fish terminal, or load the function in your current Fish session:
  source ~/.config/fish/functions/anc.fish

Anchor comes preinstalled with a bookmark, go to 'anchors' bookmark to find
the bookmarks.txt file containing your bookmarks.

Usage:
  anc + project                  Save the current directory as "project"
  anc + project /path/to/folder   Save a specified directory
  anc project                    Jump to the saved directory
  anc - project                  Remove the bookmark
EOF
