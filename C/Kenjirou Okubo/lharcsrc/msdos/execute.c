/***************************************************************/
/*                                                             */
/* Name    : execute     (For Turbo C V1.5)                    */
/*                                                             */
/* Function:                                                   */
/*                                                             */
/*  常駐ＣＯＭＭＡＮＤ．ＣＯＭの呼び出しによる子プロセスの実行 */
/*                      (int 2eh による呼び出し)               */
/* return  : None                                              */
/* Author  : S.Takanami                                        */
/* Date    : 88/07/24                                          */
/* Update  : 88/08/05   MS-DOS Ver2.11 で引数がない場合でも    */
/*                      正常に動作するように修正               */
/*                                                             */
/***************************************************************/

#include  <string.h>

void execute(char *parameter)
{
	char	buf[100];
	int	stk[100];

	if ((buf[0] = strlen(parameter)) != 0) {
		strcpy(&buf[1], parameter);
		strcat(buf, "\r");

		asm	jmp	short exe1
		asm	rss	dw	?
		asm	rsp	dw	?
		asm	res	dw	?
		asm	rds	dw	?
		asm	rdi	dw	?
		asm	rsi	dw	?
		asm	rbp	dw	?
		asm	rdx	dw	?
		asm	rcx	dw	?
		asm	rbx	dw	?
		asm	rax	dw	?

exe1:
		asm	mov	rss,ss
		asm	mov	rsp,sp
		asm	mov	res,es
		asm	mov	rds,ds
		asm	mov	rdi,di
		asm	mov	rsi,si
		asm	mov	rbp,bp
		asm	mov	rdx,dx
		asm	mov	rcx,cx
		asm	mov	rbx,bx
		asm	mov	rax,ax

		asm	lea	si,buf
		asm	mov	ax,ss
		asm	mov	ds,ax
		asm	lea	sp,stk
		asm	add	sp,99*2

		asm	int	2eh

		asm	mov	ax,rax
		asm	mov	bx,rbx
		asm	mov	cx,rcx
		asm	mov	dx,rdx
		asm	mov	bp,rbp
		asm	mov	si,rsi
		asm	mov	di,rdi
		asm	mov	ds,rds
		asm	mov	es,res
		asm	mov	sp,rsp
		asm	mov	ss,rss
	}
}
