	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1_m2p0_a2p1_c2p0"
	.file	"builtin.c"
	.option	push
	.option	arch, +a, +c
	.globl	.builtin.strcat                 # -- Begin function .builtin.strcat
	.p2align	1
	.type	.builtin.strcat,@function
.builtin.strcat:                        # @.builtin.strcat
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	sw	s2, 16(sp)                      # 4-byte Folded Spill
	sw	s3, 12(sp)                      # 4-byte Folded Spill
	sw	s4, 8(sp)                       # 4-byte Folded Spill
	mv	s0, a1
	mv	s1, a0
	call	strlen
	mv	s2, a0
	mv	a0, s0
	call	strlen
	mv	s3, a0
	add	s4, a0, s2
	addi	a0, s4, 1
	call	malloc
	blez	s2, .LBB0_3
# %bb.1:                                # %.preheader1
	add	a1, a0, s2
	mv	a2, a0
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	lbu	a3, 0(s1)
	sb	a3, 0(a2)
	addi	a2, a2, 1
	addi	s1, s1, 1
	bne	a2, a1, .LBB0_2
.LBB0_3:
	blez	s3, .LBB0_6
# %bb.4:                                # %.preheader
	add	s2, s2, a0
	add	a1, a0, s4
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	lbu	a2, 0(s0)
	sb	a2, 0(s2)
	addi	s2, s2, 1
	addi	s0, s0, 1
	bne	s2, a1, .LBB0_5
.LBB0_6:
	add	s4, s4, a0
	sb	zero, 0(s4)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s2, 16(sp)                      # 4-byte Folded Reload
	lw	s3, 12(sp)                      # 4-byte Folded Reload
	lw	s4, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end0:
	.size	.builtin.strcat, .Lfunc_end0-.builtin.strcat
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	string.length                   # -- Begin function string.length
	.p2align	1
	.type	string.length,@function
string.length:                          # @string.length
# %bb.0:
	li	a1, 0
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	add	a2, a0, a1
	lbu	a2, 0(a2)
	addi	a1, a1, 1
	bnez	a2, .LBB1_1
# %bb.2:
	addi	a0, a1, -1
	ret
.Lfunc_end1:
	.size	string.length, .Lfunc_end1-string.length
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	string.substring                # -- Begin function string.substring
	.p2align	1
	.type	string.substring,@function
string.substring:                       # @string.substring
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	sw	s1, 4(sp)                       # 4-byte Folded Spill
	sw	s2, 0(sp)                       # 4-byte Folded Spill
	mv	s0, a1
	mv	s2, a0
	sub	s1, a2, a1
	addi	a0, s1, 1
	call	malloc
	add	a1, a0, s1
	blez	s1, .LBB2_3
# %bb.1:                                # %.preheader
	add	s0, s0, s2
	mv	a2, a0
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	lbu	a3, 0(s0)
	sb	a3, 0(a2)
	addi	a2, a2, 1
	addi	s0, s0, 1
	bne	a2, a1, .LBB2_2
.LBB2_3:
	sb	zero, 0(a1)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	lw	s1, 4(sp)                       # 4-byte Folded Reload
	lw	s2, 0(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end2:
	.size	string.substring, .Lfunc_end2-string.substring
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	string.parseInt                 # -- Begin function string.parseInt
	.p2align	1
	.type	string.parseInt,@function
string.parseInt:                        # @string.parseInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	lui	a1, %hi(.L.str)
	addi	a1, a1, %lo(.L.str)
	addi	a2, sp, 8
	call	sscanf
	lw	a0, 8(sp)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end3:
	.size	string.parseInt, .Lfunc_end3-string.parseInt
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	string.ord                      # -- Begin function string.ord
	.p2align	1
	.type	string.ord,@function
string.ord:                             # @string.ord
# %bb.0:
	add	a0, a0, a1
	lbu	a0, 0(a0)
	ret
.Lfunc_end4:
	.size	string.ord, .Lfunc_end4-string.ord
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	print                           # -- Begin function print
	.p2align	1
	.type	print,@function
print:                                  # @print
# %bb.0:
	lui	a1, %hi(.L.str.1)
	addi	a1, a1, %lo(.L.str.1)
	mv	a2, a0
	mv	a0, a1
	mv	a1, a2
	tail	printf
.Lfunc_end5:
	.size	print, .Lfunc_end5-print
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	println                         # -- Begin function println
	.p2align	1
	.type	println,@function
println:                                # @println
# %bb.0:
	lui	a1, %hi(.L.str.2)
	addi	a1, a1, %lo(.L.str.2)
	mv	a2, a0
	mv	a0, a1
	mv	a1, a2
	tail	printf
.Lfunc_end6:
	.size	println, .Lfunc_end6-println
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	printInt                        # -- Begin function printInt
	.p2align	1
	.type	printInt,@function
printInt:                               # @printInt
# %bb.0:
	lui	a1, %hi(.L.str)
	addi	a1, a1, %lo(.L.str)
	mv	a2, a0
	mv	a0, a1
	mv	a1, a2
	tail	printf
.Lfunc_end7:
	.size	printInt, .Lfunc_end7-printInt
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	printlnInt                      # -- Begin function printlnInt
	.p2align	1
	.type	printlnInt,@function
printlnInt:                             # @printlnInt
# %bb.0:
	lui	a1, %hi(.L.str.3)
	addi	a1, a1, %lo(.L.str.3)
	mv	a2, a0
	mv	a0, a1
	mv	a1, a2
	tail	printf
.Lfunc_end8:
	.size	printlnInt, .Lfunc_end8-printlnInt
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	toString                        # -- Begin function toString
	.p2align	1
	.type	toString,@function
toString:                               # @toString
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	sw	s1, 4(sp)                       # 4-byte Folded Spill
	mv	s0, a0
	li	a0, 15
	call	malloc
	mv	s1, a0
	lui	a0, %hi(.L.str)
	addi	a1, a0, %lo(.L.str)
	mv	a0, s1
	mv	a2, s0
	call	sprintf
	mv	a0, s1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	lw	s1, 4(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end9:
	.size	toString, .Lfunc_end9-toString
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	getString                       # -- Begin function getString
	.p2align	1
	.type	getString,@function
getString:                              # @getString
# %bb.0:
	addi	sp, sp, -48
	sw	ra, 44(sp)                      # 4-byte Folded Spill
	sw	s0, 40(sp)                      # 4-byte Folded Spill
	sw	s1, 36(sp)                      # 4-byte Folded Spill
	sw	s2, 32(sp)                      # 4-byte Folded Spill
	sw	s3, 28(sp)                      # 4-byte Folded Spill
	sw	s4, 24(sp)                      # 4-byte Folded Spill
	sw	s5, 20(sp)                      # 4-byte Folded Spill
	sw	s6, 16(sp)                      # 4-byte Folded Spill
	sw	s7, 12(sp)                      # 4-byte Folded Spill
	sw	s8, 8(sp)                       # 4-byte Folded Spill
	sw	s9, 4(sp)                       # 4-byte Folded Spill
	li	a0, 11
	call	malloc
	mv	s3, a0
	lui	a0, %hi(.L.str.4)
	addi	s0, a0, %lo(.L.str.4)
	addi	a1, sp, 3
	mv	a0, s0
	call	scanf
	li	s9, 1
	bne	a0, s9, .LBB10_15
# %bb.1:                                # %.preheader4
	li	s6, 0
	li	s4, 10
	li	s5, 13
	mv	s2, s3
	li	a1, 1
	li	s7, 10
.LBB10_2:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB10_5 Depth 2
                                        #     Child Loop BB10_11 Depth 2
	lbu	a0, 3(sp)
	beq	a0, s5, .LBB10_4
# %bb.3:                                #   in Loop: Header=BB10_2 Depth=1
	bne	a0, s4, .LBB10_8
.LBB10_4:                               #   in Loop: Header=BB10_2 Depth=1
	andi	a1, a1, 1
	beqz	a1, .LBB10_16
.LBB10_5:                               #   Parent Loop BB10_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	addi	a1, sp, 3
	mv	a0, s0
	call	scanf
	bne	a0, s9, .LBB10_16
# %bb.6:                                #   in Loop: Header=BB10_5 Depth=2
	lbu	a0, 3(sp)
	beq	a0, s5, .LBB10_5
# %bb.7:                                #   in Loop: Header=BB10_5 Depth=2
	beq	a0, s4, .LBB10_5
.LBB10_8:                               #   in Loop: Header=BB10_2 Depth=1
	bne	s6, s7, .LBB10_13
# %bb.9:                                #   in Loop: Header=BB10_2 Depth=1
	slli	s8, s7, 1
	addi	a0, s8, 1
	call	malloc
	mv	s3, a0
	blez	s7, .LBB10_12
# %bb.10:                               # %.preheader
                                        #   in Loop: Header=BB10_2 Depth=1
	add	s7, s7, s3
	mv	a0, s2
	mv	a1, s3
.LBB10_11:                              #   Parent Loop BB10_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	lbu	a2, 0(a0)
	sb	a2, 0(a1)
	addi	a1, a1, 1
	addi	a0, a0, 1
	bne	a1, s7, .LBB10_11
.LBB10_12:                              #   in Loop: Header=BB10_2 Depth=1
	mv	a0, s2
	call	free
	lbu	a0, 3(sp)
	mv	s2, s3
	mv	s7, s8
	j	.LBB10_14
.LBB10_13:                              #   in Loop: Header=BB10_2 Depth=1
	mv	s3, s2
.LBB10_14:                              #   in Loop: Header=BB10_2 Depth=1
	addi	s1, s6, 1
	add	s6, s6, s3
	sb	a0, 0(s6)
	addi	a1, sp, 3
	mv	a0, s0
	call	scanf
	li	a1, 0
	mv	s6, s1
	beq	a0, s9, .LBB10_2
	j	.LBB10_17
.LBB10_15:
	li	s1, 0
	j	.LBB10_17
.LBB10_16:
	mv	s1, s6
	mv	s3, s2
.LBB10_17:
	add	s1, s1, s3
	sb	zero, 0(s1)
	mv	a0, s3
	lw	ra, 44(sp)                      # 4-byte Folded Reload
	lw	s0, 40(sp)                      # 4-byte Folded Reload
	lw	s1, 36(sp)                      # 4-byte Folded Reload
	lw	s2, 32(sp)                      # 4-byte Folded Reload
	lw	s3, 28(sp)                      # 4-byte Folded Reload
	lw	s4, 24(sp)                      # 4-byte Folded Reload
	lw	s5, 20(sp)                      # 4-byte Folded Reload
	lw	s6, 16(sp)                      # 4-byte Folded Reload
	lw	s7, 12(sp)                      # 4-byte Folded Reload
	lw	s8, 8(sp)                       # 4-byte Folded Reload
	lw	s9, 4(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end10:
	.size	getString, .Lfunc_end10-getString
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	getInt                          # -- Begin function getInt
	.p2align	1
	.type	getInt,@function
getInt:                                 # @getInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	lui	a0, %hi(.L.str)
	addi	a0, a0, %lo(.L.str)
	addi	a1, sp, 8
	call	scanf
	lw	a0, 8(sp)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end11:
	.size	getInt, .Lfunc_end11-getInt
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	.builtin.AllocateClassBody      # -- Begin function .builtin.AllocateClassBody
	.p2align	1
	.type	.builtin.AllocateClassBody,@function
.builtin.AllocateClassBody:             # @.builtin.AllocateClassBody
# %bb.0:
	tail	malloc
.Lfunc_end12:
	.size	.builtin.AllocateClassBody, .Lfunc_end12-.builtin.AllocateClassBody
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	.builtin.GetArrayLength         # -- Begin function .builtin.GetArrayLength
	.p2align	1
	.type	.builtin.GetArrayLength,@function
.builtin.GetArrayLength:                # @.builtin.GetArrayLength
# %bb.0:
	lbu	a1, -3(a0)
	lbu	a2, -4(a0)
	lbu	a3, -2(a0)
	lbu	a0, -1(a0)
	slli	a1, a1, 8
	or	a1, a1, a2
	slli	a3, a3, 16
	slli	a0, a0, 24
	or	a0, a0, a3
	or	a0, a0, a1
	ret
.Lfunc_end13:
	.size	.builtin.GetArrayLength, .Lfunc_end13-.builtin.GetArrayLength
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	.builtin.RecursiveAllocateArray # -- Begin function .builtin.RecursiveAllocateArray
	.p2align	1
	.type	.builtin.RecursiveAllocateArray,@function
.builtin.RecursiveAllocateArray:        # @.builtin.RecursiveAllocateArray
# %bb.0:
	addi	sp, sp, -48
	sw	ra, 44(sp)                      # 4-byte Folded Spill
	sw	s0, 40(sp)                      # 4-byte Folded Spill
	sw	s1, 36(sp)                      # 4-byte Folded Spill
	sw	s2, 32(sp)                      # 4-byte Folded Spill
	sw	s3, 28(sp)                      # 4-byte Folded Spill
	sw	s4, 24(sp)                      # 4-byte Folded Spill
	sw	s5, 20(sp)                      # 4-byte Folded Spill
	sw	s6, 16(sp)                      # 4-byte Folded Spill
	sw	s7, 12(sp)                      # 4-byte Folded Spill
	lw	s0, 0(a2)
	mv	s3, a1
	mv	s2, a0
	srli	s5, s0, 8
	srli	s4, s0, 16
	li	a0, 1
	srli	s6, s0, 24
	bne	s2, a0, .LBB14_2
# %bb.1:
	mul	a0, s0, s3
	addi	a0, a0, 4
	call	malloc
	sb	s0, 0(a0)
	sb	s5, 1(a0)
	sb	s4, 2(a0)
	sb	s6, 3(a0)
	addi	a0, a0, 4
	j	.LBB14_6
.LBB14_2:
	mv	s7, a2
	slli	a0, s0, 2
	addi	a0, a0, 4
	call	malloc
	sb	s0, 0(a0)
	sb	s5, 1(a0)
	sb	s4, 2(a0)
	sb	s6, 3(a0)
	addi	a0, a0, 4
	blez	s0, .LBB14_6
# %bb.3:
	li	s1, 0
	addi	s2, s2, -1
	addi	s5, s7, 4
	mv	s4, a0
	mv	s0, a0
.LBB14_4:                               # =>This Inner Loop Header: Depth=1
	mv	a0, s2
	mv	a1, s3
	mv	a2, s5
	call	.builtin.RecursiveAllocateArray
	lw	a1, 0(s7)
	sw	a0, 0(s0)
	addi	s1, s1, 1
	addi	s0, s0, 4
	blt	s1, a1, .LBB14_4
# %bb.5:
	mv	a0, s4
.LBB14_6:
	lw	ra, 44(sp)                      # 4-byte Folded Reload
	lw	s0, 40(sp)                      # 4-byte Folded Reload
	lw	s1, 36(sp)                      # 4-byte Folded Reload
	lw	s2, 32(sp)                      # 4-byte Folded Reload
	lw	s3, 28(sp)                      # 4-byte Folded Reload
	lw	s4, 24(sp)                      # 4-byte Folded Reload
	lw	s5, 20(sp)                      # 4-byte Folded Reload
	lw	s6, 16(sp)                      # 4-byte Folded Reload
	lw	s7, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end14:
	.size	.builtin.RecursiveAllocateArray, .Lfunc_end14-.builtin.RecursiveAllocateArray
                                        # -- End function
	.option	pop
	.option	push
	.option	arch, +a, +c
	.globl	.builtin.AllocateArray          # -- Begin function .builtin.AllocateArray
	.p2align	1
	.type	.builtin.AllocateArray,@function
.builtin.AllocateArray:                 # @.builtin.AllocateArray
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	mv	s0, a1
	mul	a0, a1, a0
	addi	a0, a0, 4
	call	malloc
	sb	s0, 0(a0)
	srli	a1, s0, 8
	sb	a1, 1(a0)
	srli	a1, s0, 16
	sb	a1, 2(a0)
	srli	s0, s0, 24
	addi	a1, a0, 4
	sb	s0, 3(a0)
	mv	a0, a1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end15:
	.size	.builtin.AllocateArray, .Lfunc_end15-.builtin.AllocateArray
                                        # -- End function
	.option	pop
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%s"
	.size	.L.str.1, 3

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"%s\n"
	.size	.L.str.2, 4

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"%d\n"
	.size	.L.str.3, 4

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"%c"
	.size	.L.str.4, 3

	.ident	"Ubuntu clang version 18.1.8 (++20240731024944+3b5b5c1ec4a3-1~exp1~20240731145000.144)"
	.section	".note.GNU-stack","",@progbits
