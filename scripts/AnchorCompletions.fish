function __anc_bookmarks
    set -l data_dir "$HOME/.local/share"

    if set -q XDG_DATA_HOME; and string match -q '/*' -- "$XDG_DATA_HOME"
        set data_dir "$XDG_DATA_HOME"
    end

    set -l bookmarks_file "$data_dir/anchor/bookmarks.txt"
    test -r "$bookmarks_file"; or return

    # Skip comments and output the first field: the bookmark name.
    awk '!/^\/\// && NF >= 2 { print $1 }' "$bookmarks_file"
end

complete -c anc \
    -f \
    -n 'test (count (commandline -opc)) -eq 1' \
    -a '(__anc_bookmarks)'