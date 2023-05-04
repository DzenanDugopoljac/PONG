  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

	.data
	
	.align 2
mytime:	.word 0x5957
timstr:	
        .ascii "text more text lots of text\0"
	.text
	
	
.global delay
.global time2string
.global enable_interrupt

enable_interrupt:
        
        ei
        jr $ra
        nop

main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
hexasc:                         # You can write your own code for hexasc here
        andi  $a0, $a0, 0xf     # only values from 0 - 15
        addi  $v0, $a0, 0x30    # v0 = a0 + 0x30 so that get the correct ASCII- code value.
        li    $t0, 0x39            
          
        ble   $v0, $t0, continue   # v0 <= 0x39 (9) (if v0 <= 0x39 ----> continue)
        nop
          
        addi  $v0, $v0, 7          # else: v0 = v0 + 7.  to be able to reprsesent A B C D E and F.
          
               
               
continue:  jr $ra
           nop                     


#---------  Assignment 4 ----------- #
           
delay:
           li $t0, 0               # int i = 0; 
           li $t1, 1               # t1 = 1
           li $t2, 4000          # constant
           
back:      slt $t3, $0, $a0        # t3 = 0 < a0  (true t3 = 1, false t3 = 0)
           beq $t3, $0, exit       # if t3 = 0 then exit delay
           nop
           li $t0, 0               # reset i so that i = 0;
loop:                              # FOR LOOP
           sub  $a0, $a0, $t1        # ms = ms -1;
check:     slt  $t4, $t0, $t2
           beq  $t4, $0,  back
           nop
           addi  $t0, $t0, 1
           j     check
           nop
           
exit:      jr $ra
           nop
# ********************************** #  

#--------- Assignment 3 ----------- #     
time2string:

          PUSH $ra
      
# -------- Minute 1 ----------------- #
          PUSH $a0
          andi $t0, $a1, 0xf000
          srl  $a0, $t0, 12
          jal  hexasc
          nop
          move $t0, $v0
          POP $a0     
          sb   $t0, 0($a0)
#*************************************

#---------- Minute 2 ---------------- #  
          PUSH $a0  
          andi $t1, $a1, 0x0f00
          srl  $a0, $t1, 8
          jal  hexasc
          nop
          move $t1, $v0
          POP $a0
          sb   $t1, 1($a0)
#*************************************
          # colon character
          li $t2, 0x3A
          sb $t2, 2($a0)
          
          PUSH $a0
          andi $t3, $a1, 0x00f0
          srl  $a0, $t3, 4
          jal  hexasc
          nop
          move $t3, $v0
          POP $a0
          sb   $t3, 3($a0)

          PUSH $a0
          andi $t4, $a1, 0xf
          add  $a0, $0, $t4 
          jal  hexasc
          nop
          move $t4, $v0
          POP $a0
          sb   $t4, 4($a0)
          
          # NULL
          li  $t5,  0x00
          sb  $t5,  5($a0)
         
          POP $ra
          jr $ra
          nop

          
                              
