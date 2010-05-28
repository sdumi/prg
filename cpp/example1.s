	.file	"example1.c"
	.text
.globl function
	.type	function, @function
function:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	leave
	ret
	.size	function, .-function
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	movl	$3, 8(%esp)
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	call	function
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.1"
