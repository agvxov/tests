/* This is me messing with the optimization of
 *  constant function pointers.
 */
#define SECTION 0

#if SECTION == 0
    /* NOTE:
     *  The pointer fp was optimized out from calls.
     */
    #include <stdio.h>

    __attribute__((noinline))
    static int add1(int x)
    {
        return x + 1;
    }

    static int (* const fp)(int) = add1;

    __attribute__((noinline))
    static int call_via_fp(int x)
    {
        return fp(x);
    }

    int main(void)
    {
        printf("%d\n", call_via_fp(41));
        return 0;
    }
    /*
     * fp:
     * 	.quad	add1
     * 	.text
     * 	.type	call_via_fp, @function
     * call_via_fp:
     * .LFB1:
     * 	.cfi_startproc
     * 	endbr64
     * 	pushq	%rbp
     * 	.cfi_def_cfa_offset 16
     * 	.cfi_offset 6, -16
     * 	movq	%rsp, %rbp
     * 	.cfi_def_cfa_register 6
     * 	subq	$16, %rsp
     * 	movl	%edi, -4(%rbp)
     * 	leaq	add1(%rip), %rdx
     * 	movl	-4(%rbp), %eax
     * 	movl	%eax, %edi
     * 	call	*%rdx
     * 	leave
     * 	.cfi_def_cfa 7, 8
     * 	ret
     */
#elif SECTION == 1
    /* A real namespace in C.
     */
    typedef struct {
        int (*add)(int, int);
        int (*sub)(int, int);
    } math_ns_t;

    static int add_impl(int a, int b) { return a + b; }
    static int sub_impl(int a, int b) { return a - b; }

    const math_ns_t math = {
        .add = add_impl,
        .sub = sub_impl,
    };

    signed main(void) {
        volatile int x = math.add(1, 2);
        volatile int y = math.sub(5, 3);
        return 0;
    }
    /*
     * main:
     * .LFB2:
     * 	.cfi_startproc
     * 	endbr64
     * 	pushq	%rbp
     * 	.cfi_def_cfa_offset 16
     * 	.cfi_offset 6, -16
     * 	movq	%rsp, %rbp
     * 	.cfi_def_cfa_register 6
     * 	subq	$16, %rsp
     * 	leaq	add_impl(%rip), %rax
     * 	movl	$2, %esi
     * 	movl	$1, %edi
     * 	call	*%rax
     * 	movl	%eax, -8(%rbp)
     * 	leaq	sub_impl(%rip), %rax
     * 	movl	$3, %esi
     * 	movl	$5, %edi
     * 	call	*%rax
     * 	movl	%eax, -4(%rbp)
     * 	movl	$0, %eax
     * 	leave
     * 	.cfi_def_cfa 7, 8
     * 	ret
     * 	.cfi_endproc
     */
#elif SECTION == 2
    /* Same as above. (s/static/extern/)
     */
    typedef struct {
        int (*add)(int, int);
        int (*sub)(int, int);
    } math_ns_t;

    extern int add_impl(int a, int b);
    extern int sub_impl(int a, int b);

    const math_ns_t math = {
        .add = add_impl,
        .sub = sub_impl,
    };

    signed main(void) {
        volatile int x = math.add(1, 2);
        volatile int y = math.sub(5, 3);
        return 0;
    }

    // used to be file d.c
    int add_impl(int a, int b) { return a + b; }
    int sub_impl(int a, int b) { return a - b; }
    /*
     * main:
     * .LFB0:
     * 	.cfi_startproc
     * 	endbr64
     * 	pushq	%rbp
     * 	.cfi_def_cfa_offset 16
     * 	.cfi_offset 6, -16
     * 	movq	%rsp, %rbp
     * 	.cfi_def_cfa_register 6
     * 	subq	$16, %rsp
     * 	movq	add_impl@GOTPCREL(%rip), %rax
     * 	movl	$2, %esi
     * 	movl	$1, %edi
     * 	call	*%rax
     * 	movl	%eax, -8(%rbp)
     * 	movq	sub_impl@GOTPCREL(%rip), %rax
     * 	movl	$3, %esi
     * 	movl	$5, %edi
     * 	call	*%rax
     * 	movl	%eax, -4(%rbp)
     * 	movl	$0, %eax
     * 	leave
     * 	.cfi_def_cfa 7, 8
     * 	ret
     * 	.cfi_endproc
    */
#endif
