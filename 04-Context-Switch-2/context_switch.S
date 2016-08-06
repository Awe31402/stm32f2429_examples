.thumb
.syntax unified

.type svc_handler, %function
.global svc_handler
svc_handler:
  mrs r0, psp
  stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

  pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
  msr psr, ip
  bx lr

.global activate
activate:
  mrs ip, psr
  push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

  msr psp, r0
  mov r0, #3
  msr control, r0

  pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}

  bx lr

