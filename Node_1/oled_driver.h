/*! @file
 * Oled driver header file
 */
#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

void write_c(uint8_t val);
void write_d(uint8_t data);

uint8_t oled_init(void);

int oled_print_char_small_buffer(char chr, int line, int col_start);
int oled_print_char_medium_buffer(char chr, int line, int col_start);
int oled_print_char_large_buffer(char chr, int line, int col_start);

int oled_update_buffer(void);
void oled_page_select(int page);
void oled_col_start_end(int start, int end);
void oled_clear_line(int line);
void oled_reset_screen(void);
void oled_fill_screen(void);
/*void oled_print_arrow(uint8_t line);*/

// int oled_print_small(char chr,FILE* file);
// int oled_print_medium(char chr, FILE* file);
// int oled_print_large(char chr,FILE* file);
// int oled_home(void);

void set_cursor(int line, int col);
int oled_print_small_b(char ch, FILE* file);
int oled_print_medium_b(char ch, FILE* file);
int oled_print_large_b(char ch, FILE* file);

//Circle drawing functions
// bool oled_draw_circle_buffer(int line, int col_start,int radius);
// void oled_draw_picture();
// void oled_draw_face();
// int oled_draw_man(void);

void oled_adjust_brightness(uint8_t level);
int oled_set_last_brightness(void);

static FILE oled_stdout_4 = FDEV_SETUP_STREAM(oled_print_small_b,NULL,_FDEV_SETUP_WRITE);
static FILE oled_stdout_5 = FDEV_SETUP_STREAM(oled_print_medium_b,NULL,_FDEV_SETUP_WRITE);
static FILE oled_stdout_8 = FDEV_SETUP_STREAM(oled_print_large_b,NULL,_FDEV_SETUP_WRITE);

#define  FONT4 (&oled_stdout_4)
#define  FONT5 (&oled_stdout_5)
#define  FONT8 (&oled_stdout_8)
#define EEPROM_BRIGHTNESS_ADR 0x70

uint8_t LINE_POS;
uint8_t COL_POS;

#endif /* OLED_DRIVER_H_ */