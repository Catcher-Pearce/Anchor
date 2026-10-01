#!/usr/bin/env fish

function anc
    set -l output (/usr/local/bin/Fishmark $argv)
    or return 1

    if test -n "$output"; and test -d "$output"
        cd -- "$output"
    else if test -n "$output"
        printf '%s\n' "$output"
    end
end
