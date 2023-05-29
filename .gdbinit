define dump_ctx
end



# $arg0: pointer to ir_ctx{}
define dump_def_use_lists
    if $argc == 0
        help dump_def_use_lists
    else
        set $ctx = (ir_ctx*) $arg0
    end

    # Dump summary
    printf "ctx Address: [%p]\n", $ctx
    printf "use_lists=[%p] count=%d\n", $ctx->use_lists, $ctx->insns_count
    printf "use_edges=[%p] count=%d\n", $ctx->use_edges, $ctx->use_edges_count

    # Dump details
    set $idx = 1
    printf "*** use_lists ***\n"
    while ( $idx < $ctx->insns_count )
        set $list = $ctx->use_lists[$idx]
        printf "[%03d] (%d, %d)\n", $idx, $list.refs, $list.count
        set $idx = $idx + 1
    end

    set $idx = 0
    printf "*** use_edges ***\n"
    while ( $idx < $ctx->use_edges_count )
        printf "[%03d] (%d)\n", $idx, $ctx->use_edges[$idx]
        set $idx = $idx + 1
    end
end

document dump_def_use_lists
    Usage: dump_def_use_lists ctx_ptr
end