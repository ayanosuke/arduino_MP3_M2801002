#include <scpiparser.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

struct scpi_parser_context ctx;

char VER[] = " D/A Ver0.1";
int dl = 100;  // 100msec wait  80msecでは足らないっぽい

void setup(void)
{
  struct scpi_command* source;
  struct scpi_command* measure;

  /* First, initialise the parser. */
  scpi_init(&ctx);

  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "DAC", 3, "DAC", 3, set_dac);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "WT", 2, "WT", 2, set_delay);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "+", 1, "+", 1, set_p);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "-", 1, "-", 1, set_n);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "P", 1, "P", 1, set_play);//play:pause
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "S", 1, "S", 1, set_stop);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "V", 1, "V", 1, set_next2);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "W", 1, "W", 1, set_prev2);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "N", 1, "N", 1, set_next);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "R", 1, "R", 1, set_prev);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "E", 1, "E", 1, set_eq);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "L", 1, "L", 1, set_repeat);
  scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "M", 1, "M", 1, set_mode);
   
  Serial.begin(9600);
  int ledPin = 9;
  char dac = 71;
  analogWrite(ledPin, dac);
}

void loop()
{
  char line_buffer[256];
  unsigned char read_length;

  Serial.println(VER);
  Serial.println();
  
  while (1)
  {
    /* Read in a line and execute it. */
    read_length = Serial.readBytesUntil('\n', line_buffer, 256);
    if (read_length > 0)
    {
      //Serial.println(line_buffer);
      scpi_execute_command(&ctx, StrToUpper(line_buffer), read_length);
    }
  }
}

//--------------------------------------------------------------------------------------
// 関数:char *StrToUpper(char *)
// 機能:文字列中の英小文字を大文字に変換
// http://www1.cts.ne.jp/~clab/hsample/Point/Point11.html
//--------------------------------------------------------------------------------------
char *StrToUpper(char *s)
{
  char *p;                     /* 作業用ポインタ */
  /* for (  )ループの初期化の式で、pは文字列の
     先頭アドレスを指すように初期化される */
  for (p = s; *p; p++)         /* pがヌルでなければ */
    *p = toupper(*p);        /* pの指す中身を大文字に変換 */
  return (s);                  /* 文字列の先頭アドレスを返す */
}

//--------------------------------------------------------------------------------------
// 関数:set_delay
// 機能:WT nnn
// 使用例：WT nnnn
//--------------------------------------------------------------------------------------
scpi_error_t set_delay(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;
 
  Serial.println("");
  Serial.println("CMD:WT");

  args = command;

  while (args != NULL && args->type == 0)
  {
    args = args->next;
  }

  dl = atoi(args->value);
  Serial.println(dl);

  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_dac
// 機能:D/A出力します
// 使用例：DAC 250
//--------------------------------------------------------------------------------------
scpi_error_t set_dac(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int data;
  int ledPin = 9;

  Serial.println("");
  Serial.println("CMD:DAC");

  args = command;

  while (args != NULL && args->type == 0)
  {
    args = args->next;
  }

  data = atoi(args->value);
  analogWrite(ledPin, data);

  Serial.println(data);

  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_p
// 機能:VOL +
// 使用例：+
//--------------------------------------------------------------------------------------
scpi_error_t set_p(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 56;
  
  Serial.println("");
  Serial.println("CMD:+");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_n
// 機能:VOL -
// 使用例：-
//--------------------------------------------------------------------------------------
scpi_error_t set_n(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 71;
  
  Serial.println("");
  Serial.println("CMD:-");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_play
// 機能:play
// 使用例：P
//--------------------------------------------------------------------------------------
scpi_error_t set_play(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 0;
  
  Serial.println("");
  Serial.println("CMD:play");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_stop
// 機能:stop
// 使用例：S
//--------------------------------------------------------------------------------------
scpi_error_t set_stop(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 153;
  
  Serial.println("");
  Serial.println("CMD:stop");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
//--------------------------------------------------------------------------------------
// 関数:set_next2
// 機能:next
// 使用例：N
//--------------------------------------------------------------------------------------
scpi_error_t set_next2(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 112;
  
  Serial.println("");
  Serial.println("CMD:next2");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
//--------------------------------------------------------------------------------------
// 関数:set_prev2
// 機能:next
// 使用例：R
//--------------------------------------------------------------------------------------
scpi_error_t set_prev2(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 128;
  
  Serial.println("");
  Serial.println("CMD:prev2");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_next
// 機能:next
// 使用例：N
//--------------------------------------------------------------------------------------
scpi_error_t set_next(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 15;
  
  Serial.println("");
  Serial.println("CMD:next");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
//--------------------------------------------------------------------------------------
// 関数:set_prev
// 機能:next
// 使用例：R
//--------------------------------------------------------------------------------------
scpi_error_t set_prev(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 26;
  
  Serial.println("");
  Serial.println("CMD:prev");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
//--------------------------------------------------------------------------------------
// 関数:set_eq
// 機能:eq
// 使用例：E
//--------------------------------------------------------------------------------------
scpi_error_t set_eq(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 97;
  
  Serial.println("");
  Serial.println("CMD:eq");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_repeat
// 機能:repeat
// 使用例：R
//--------------------------------------------------------------------------------------
scpi_error_t set_repeat(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 84;
  
  Serial.println("");
  Serial.println("CMD:repeat");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}

//--------------------------------------------------------------------------------------
// 関数:set_mode
// 機能:mode
// 使用例：M
//--------------------------------------------------------------------------------------
scpi_error_t set_mode(struct scpi_parser_context* context, struct scpi_token* command)
{
  struct scpi_token* args;
  struct scpi_numeric setmem_a;

  int ledPin = 9;
  char ref = 168;
  char dac = 42;
  
  Serial.println("");
  Serial.println("CMD:mode");

  analogWrite(ledPin, dac);
  delay(dl);
  analogWrite(ledPin, ref);
 
  scpi_free_tokens(command);
  return SCPI_SUCCESS;
}
