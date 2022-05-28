#ifndef ERRORS_H
#define ERRORS_H

// Is called when stack fails
void __stack_chk_fail(void);
// Is called when division by zero happens
void __div_by_zero(void);

#endif