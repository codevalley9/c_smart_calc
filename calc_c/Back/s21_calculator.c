#include "s21_calculator.h"

void stack_init_op(stack_operators *stack) {
  stack->size = 0;
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    stack->buf[i] = 0;
  }
}

void stack_init_num(stack_numbers *stack) {
  stack->size = 0;
  for (int i = 0; i < MAX_STACK_SIZE; i++) {
    stack->buf[i] = 0;
  }
}

int stack_push_op(stack_operators *stack, my_operator *c) {
  if (stack->size >= MAX_STACK_SIZE) {
    return 0;
  }

  stack->buf[stack->size] = *c;
  stack->size += 1;

  return 1;
}

int stack_push_num(stack_numbers *stack, double *c) {
  if (stack->size >= MAX_STACK_SIZE) {
    return 0;
  }

  stack->buf[stack->size] = *c;
  stack->size += 1;

  return 1;
}

int stack_pop_op(stack_operators *stack, my_operator *c) {
  if (stack->size <= 0) {
    return 0;
  }
  *c = stack->buf[stack->size - 1];
  stack->buf[stack->size - 1] = 0;
  stack->size -= 1;
  return 1;
}

int stack_pop_num(stack_numbers *stack, double *c) {
  if (stack->size <= 0) {
    return 0;
  }
  *c = stack->buf[stack->size - 1];
  stack->buf[stack->size - 1] = 0;
  stack->size -= 1;
  return 1;
}

int stack_top_op(stack_operators *stack, my_operator *c) {
  if (stack->size <= 0) {
    return 0;
  }
  *c = stack->buf[stack->size - 1];
  return 1;
}

int stack_top_num(stack_numbers *stack, double *c) {
  if (stack->size <= 0) {
    return 0;
  }
  *c = stack->buf[stack->size - 1];
  return 1;
}

my_operator get_operator(const char *c, int *index) {
  static const str_op operators_strings[] = {
      {"+", PLUS},         {"-", MINUS},     {"*", MUL},
      {"/", DIV},          {"÷", DIV},       {"%", MOD},
      {"mod", MOD},        {"^", POW},       {"(", LEFT_BRACES},
      {")", RIGHT_BRACES}, {"sin", SIN},     {"cos", COS},
      {"tan", TAN},        {"acos", ACOS},   {"asin", ASIN},
      {"atan", ATAN},      {"sqrt", SQRT},   {"ln", LN},
      {"log", LOG},        {NULL, UNDEFINED}};

  for (int i = 0; operators_strings[i].str; i++) {
    const char *op_str = operators_strings[i].str;
    if (strncmp(op_str, c, strlen(op_str)) == 0) {
      *index = strlen(op_str) - 1;
      return operators_strings[i].op;
    }
  }

  return UNDEFINED;
}

int skip_numbers(char *s, int index, int size) {
  for (; index < size; index++) {
    if (!isdigit(s[index]) && s[index] != '.') {
      break;
    }
  }
  return index;
}

int priority(my_operator op) {
  switch (op) {
    case PLUS:
      return PRIORITY_1;
    case MINUS:
      return PRIORITY_1;
    case MUL:
      return PRIORITY_2;
    case DIV:
      return PRIORITY_2;
    case MOD:
      return PRIORITY_2;
    case POW:
      return PRIORITY_3;  // x в степени y
    case SQRT:
      return PRIORITY_3;  //положительный квадратный корень положительного числа
    case SIN:
      return PRIORITY_4;
    case COS:
      return PRIORITY_4;
    case TAN:
      return PRIORITY_4;
    case ACOS:
      return PRIORITY_4;
    case ASIN:
      return PRIORITY_4;
    case ATAN:
      return PRIORITY_4;
    case LN:
      return PRIORITY_4;
    case LOG:
      return PRIORITY_4;
    default:
      return DEFAULT;
  }
}

double add(stack_numbers *stack_num, double result) {
  double right_number = 0;
  double left_number = 0;
  if (!stack_pop_num(stack_num, &right_number)) return 0;
  if (!stack_pop_num(stack_num, &left_number)) {
    result = right_number;
    stack_push_num(stack_num, &result);
  } else {
    result = right_number + left_number;
    stack_push_num(stack_num, &result);
  }
  return result;
}

double sub(stack_numbers *stack_num, stack_operators *stack_op, double result) {
  double right_number = 0;
  double left_number = 0;
  my_operator down;
  stack_top_op(stack_op, &down);
  if (!stack_pop_num(stack_num, &right_number)) return 0;
  if (!stack_pop_num(stack_num, &left_number)) {
    result = -right_number;
    stack_push_num(stack_num, &result);
  } else {
    result = left_number - right_number;
    stack_push_num(stack_num, &result);
  }
  return result;
}

double mul(stack_numbers *stack_num, double result) {
  double right_number = 0;
  double left_number = 0;
  stack_pop_num(stack_num, &right_number);
  stack_pop_num(stack_num, &left_number);
  result = right_number * left_number;
  stack_push_num(stack_num, &result);
  return result;
}

double division(stack_numbers *stack_num, double result) {
  double right_number = 0;
  double left_number = 0;
  stack_pop_num(stack_num, &right_number);
  stack_pop_num(stack_num, &left_number);
  result = left_number / right_number;
  stack_push_num(stack_num, &result);
  return result;
}

double exponentiation(stack_numbers *stack_num, double result) {
  double right_number = 0;
  double left_number = 0;
  stack_pop_num(stack_num, &right_number);
  stack_pop_num(stack_num, &left_number);
  result = pow(left_number, right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double sinus(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = sin(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double cosinus(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = cos(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double tangens(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = tan(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double cotangent(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = atan(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double arcsine(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = asin(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double arccosine(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = acos(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double square(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = sqrt(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double natural_logarithm(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = log(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double decimal_logarithm(stack_numbers *stack_num, double result) {
  double right_number = 0;
  stack_pop_num(stack_num, &right_number);
  result = log10(right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double remainder_of_the_division(stack_numbers *stack_num, double result) {
  double right_number = 0;
  double left_number = 0;
  stack_pop_num(stack_num, &right_number);
  stack_pop_num(stack_num, &left_number);
  result = fmod(left_number, right_number);
  stack_push_num(stack_num, &result);
  return result;
}

double calc(stack_numbers *stack_num, stack_operators *stack_op) {
  my_operator c = UNDEFINED;
  stack_top_op(stack_op, &c);
  if (c != UNDEFINED && c != LEFT_BRACES && c != RIGHT_BRACES) {
    if (!stack_pop_op(stack_op, &c)) return 0;
    my_operator current = c;
    double result = 0;
    if (current == PLUS)
      result = add(stack_num, result);
    else if (current == MINUS)
      result = sub(stack_num, stack_op, result);
    else if (current == MUL)
      result = mul(stack_num, result);
    else if (current == DIV)
      result = division(stack_num, result);
    else if (current == POW)
      result = exponentiation(stack_num, result);
    else if (current == SIN)
      result = sinus(stack_num, result);
    else if (current == COS)
      result = cosinus(stack_num, result);
    else if (current == TAN)
      result = tangens(stack_num, result);
    else if (current == ACOS)
      result = arccosine(stack_num, result);
    else if (current == ASIN)
      result = arcsine(stack_num, result);
    else if (current == ATAN)
      result = cotangent(stack_num, result);
    else if (current == SQRT)
      result = square(stack_num, result);
    else if (current == LN)
      result = natural_logarithm(stack_num, result);
    else if (current == LOG)
      result = decimal_logarithm(stack_num, result);
    else if (current == MOD)
      result = remainder_of_the_division(stack_num, result);
    else if (current == UNDEFINED)
      result = 0;
  }
  double result = 0;
  stack_top_num(stack_num, &result);
  return result;
}

void process_number(char *expr, int *i, stack_numbers *stack_num,
                    stack_operators *stack_op) {
  char *current_pos = &expr[*i];
  double num = atof(current_pos);
  stack_push_num(stack_num, &num);
  if (expr[*i - 2] == '(' && expr[*i - 1] == '-') {
    double tmp = 0;
    stack_pop_num(stack_num, &tmp);
    tmp = -tmp;
    my_operator temp;
    stack_pop_op(stack_op, &temp);
    stack_push_num(stack_num, &tmp);
  }
  *i = skip_numbers(expr, *i, strlen(expr)) - 1;
}

double parsing(char *expr, stack_numbers *stack_num, stack_operators *stack_op,
               double x) {
  stack_init_num(stack_num);
  stack_init_op(stack_op);
  double result = 0.0;
  int expr_size = strlen(expr);
  int counter_op = 0;
  int braces = 0;
  for (int i = 0; i < expr_size;) {
    char *c = &expr[i];
    if (*c == 'x')
      stack_push_num(stack_num, &x);
    else if (isdigit(*c)) {
      process_number(expr, &i, stack_num, stack_op);
    } else if (get_operator(c, &counter_op) != UNDEFINED) {
      my_operator temp;
      temp = get_operator(c, &counter_op);
      i += counter_op;
      my_operator op_down = UNDEFINED;
      if (temp == LEFT_BRACES) {
        braces++;
        stack_push_op(stack_op, &temp);
      } else if (temp == RIGHT_BRACES) {
        if (braces > 0) {
          my_operator tmp = UNDEFINED;
          while (tmp != LEFT_BRACES) {
            calc(stack_num, stack_op);
            stack_top_op(stack_op, &tmp);
          }
          if (tmp == LEFT_BRACES) {
            stack_pop_op(stack_op, &tmp);
          }
          braces--;
        }
      } else if (!stack_top_op(stack_op, &op_down)) {
        stack_push_op(stack_op, &temp);
      } else if (priority(temp) == priority(op_down) &&
                 priority(op_down) == PRIORITY_3) {
        stack_push_op(stack_op, &temp);
      } else if (priority(temp) <= priority(op_down)) {
        calc(stack_num, stack_op);
        stack_push_op(stack_op, &temp);
      } else {
        stack_push_op(stack_op, &temp);
      }
    }
    i++;
  }
  while (stack_op->size > 0 && stack_num->size > 0) {
    result = calc(stack_num, stack_op);
    printf("RESULT: %.8f\n", result);
  }
  return result;
}

// int main()
// {
//     stack_operators stack_op; // объявление стека операторов
//     stack_numbers stack_num;
//     double x;    // объявление стека операторов

//     char* expr = "1+2*3^sin(0.4)^3*2+1";    // исходное выражение
//     parsing(expr, &stack_num, &stack_op, x);
//     return 0;
// }
