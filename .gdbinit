define dump_ctx
    set $ctx = $arg0
    set $idx = 0
    while ($idx < $ctx->insns_count)
        dump_insn $ctx->ir_base+$idx
        set $idx = $idx + 1
    end
end


# $arg0: insn_ptr
define dump_insn
    set $insn = (ir_insn*) $arg0
    printf "addr=%p ", $insn
    print_op $insn->op
    printf " "
    print_type $insn->type
    printf " "
    printf "(%d) ", $insn->inputs_count

    # dump ops
    printf "op1=%d ", $insn->op1
    printf "op2=%d ", $insn->op2
    printf "op3=%d\n", $insn->op3
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

# $arg0: pointer to ir_ctx{}
define dump_prev_ref
    if $argc == 0
        help dump_prev_ref
    else
        set $ctx = (ir_ctx*) $arg0
    end

    set $idx = 1
    printf "prev_ref count = %d\n", $ctx->insns_count
    while ($idx < $ctx->insns_count)
        printf "%03d %d\n", $idx, $ctx->prev_ref[$idx]
        set $idx = $idx + 1
    end
end

document dump_prev_ref
    Usage: dump_prev_ref ctx_ptr
end

# $arg0: pointer to ir_ctx{}
define dump_rules
    if $argc == 0
        help dump_rules
    else
        set $ctx = (ir_ctx*) $arg0
    end

    set $idx = 0
    printf "rules count = %d\n", $ctx->insns_count
    while ($idx < $ctx->insns_count)
        printf "%03d ", $idx

        # print instruction
        print_op $ctx->ir_base[$idx].op

        # Trick: print rule
        # print rule number value
        printf " %d\t", $ctx->rules[$idx]

        # Try to print rule name, or op name, or nothing
        print_rule $ctx->rules[$idx]
        print_op $ctx->rules[$idx]

        printf "\n"
        set $idx = $idx + 1
    end
end

document dump_rules
    Usage: dump_rules ctx_ptr
end

# $arg0: pointer to ir_ctx{}
define dump_vregs
    if $argc == 0
        help dump_vregs
    else
        set $ctx = (ir_ctx*) $arg0
    end

    set $idx = 1
    printf "vregs count = %d\n", $ctx->vregs_count
    while ($idx <= $ctx->vregs_count)
        printf "%03d %d\n", $idx, $ctx->vregs[$idx]
        set $idx = $idx + 1
    end
end

document dump_vregs
    Usage: dump_vregs ctx_ptr
end
