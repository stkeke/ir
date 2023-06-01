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
    printf "*** use_lists ([Insn_Idx] Edges_Idx, Count) ***\n"
    while ( $idx < $ctx->insns_count )
        set $list = $ctx->use_lists[$idx]
        printf "[%03d ", $idx
        print_op $ctx->ir_base[$idx].op
        printf "] (%d, %d)\n", $list.refs, $list.count
        set $idx = $idx + 1
    end

    set $idx = 0
    printf "*** use_edges ([Edges_Idx] Insn_Idx) ***\n"
    while ( $idx < $ctx->use_edges_count )
        printf "[%03d] (%d ", $idx, $ctx->use_edges[$idx]
        print_op $ctx->ir_base[$ctx->use_edges[$idx]].op
        printf ")\n"
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

# $arg0: instruction opcode
define dump_ir_op_flag
    set $op = (uint8_t) $arg0
    print_op $op
    set $flag = ir_op_flags[$op]
    printf ",\tFlag: 0x%08x ", $flag
    dump_operand_kind $flag
    printf ", Operands Count: %d", ($flag & 0x18)>>3
    printf ", Input Edges: %d", ($flag & 0x3)
    printf ", Flag:"
    if $flag & 0x4
        printf " VAR_INPUTS"
    end
    if $flag & 0x100
        printf " DATA"
    end
    if $flag & 0x200
        printf " CONTROL"
    end
    if $flag & 0x400
        printf " MEM"
    end

    if $flag & 0x1000
        printf " BB_START"
    end
    if $flag & 0x2000
        printf " BB_END"
    end
    if $flag & 0x4000
        printf " TERMINATOR"
    end
    if $flag & 0x8000
        printf " PINNED"
    end
    printf "\n"
end

# $arg0: flag
define dump_operand_kind
    set $kind = (uint32_t)$arg0 >> 16

    set $op1_kind = ($kind & 0x00F0) >> 4
    set $op2_kind = ($kind & 0x0F00) >> 8
    set $op3_kind = ($kind & 0xF000) >> 12

    printf "("
    _dump_operand_kind $op1_kind
    printf ", "
    _dump_operand_kind $op2_kind
    printf ", "
    _dump_operand_kind $op3_kind
    printf ")"
end

define _dump_operand_kind
# ir_private.h IR_OPND_XXXX
    set $op_kind = $arg0
    if $op_kind == 0x0
        printf "unused"
    end

    if $op_kind == 0x1
        printf "def/ref/var"
    end

    if $op_kind == 0x2
        printf "src"
    end

    if $op_kind == 0x3
        printf "reg"
    end

    if $op_kind == 0x4
        printf "ret"
    end

    if $op_kind == 0x5
        printf "str"
    end

    if $op_kind == 0x6
        printf "num"
    end

    if $op_kind == 0x7
        printf "prb/opt"
    end
end

define dump_all_op_flag
    set $op = 0
    while $op < IR_LAST_OP
        dump_ir_op_flag $op
        set $op = $op + 1
    end
end