#pragma once

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 256

typedef enum {
  PLUS = 1,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
  LEFT_BRACES,
  RIGHT_BRACES,
  SIN,
  COS,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  UNDEFINED
} my_operator;

typedef struct {
  my_operator buf[MAX_STACK_SIZE];
  int size;
} stack_operators;

typedef struct {
  double buf[MAX_STACK_SIZE];
  int size;
} stack_numbers;

typedef enum {
  DEFAULT,
  PRIORITY_1,
  PRIORITY_2,
  PRIORITY_3,
  PRIORITY_4
} Priority;

typedef struct {
  const char *str;
  my_operator op;
} str_op;

void stack_init_op(stack_operators *stack);
void stack_init_num(stack_numbers *stack);

int stack_push_op(stack_operators *stack,
                  my_operator *c);  //добавляем элемент в стек
int stack_push_num(stack_numbers *stack, double *c);

int stack_pop_op(stack_operators *stack,
                 my_operator *c);  // извлечение элемента из стека
int stack_pop_num(stack_numbers *stack, double *c);

int stack_top_op(stack_operators *stack, my_operator *c);
int stack_top_num(stack_numbers *stack, double *c);

my_operator get_operator(const char *c, int *index);

double calc(stack_numbers *stack_num, stack_operators *stack_op);
int skip_numbers(char *s, int index, int size);
double parsing(char *expr, stack_numbers *stack_num, stack_operators *stack_op,
               double x);
double add(stack_numbers *stack_num, double result);
double sub(stack_numbers *stack_num, stack_operators *stack_op, double result);
double mul(stack_numbers *stack_num, double result);
double division(stack_numbers *stack_num, double result);
double exponentiation(stack_numbers *stack_num, double result);