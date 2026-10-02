#!/usr/bin/env bash
set -eu

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

printf 'Creating installation directories...\n'
mkdir -p "$HOME/.local/bin" "$HOME/.config/fish/functions"

printf 'Installing Anchor to %s...\n' "$HOME/.local/bin/anchor"
install -m 755 "$script_dir/../anchor" "$HOME/.local/bin/anchor"
printf 'Installing the anc Fish function...\n'
install -m 644 "$script_dir/Anchor.fish" \
    "$HOME/.config/fish/functions/anc.fish"

cat <<'EOF'

Anchor installed successfully!

Open a new Fish terminal, or load the function in your current Fish session:
  source ~/.config/fish/functions/anc.fish

Usage:
  anc + project                  Save the current directory as "project"
  anc + project /path/to/folder   Save a specified directory
  anc project                    Jump to the saved directory
  anc - project                  Remove the bookmark
EOF
