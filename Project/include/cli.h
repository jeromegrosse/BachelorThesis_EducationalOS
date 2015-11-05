#ifndef CLI_H
#define CLI_H

#define MAX_LINE 255
#define PREFIX_LINE "raspberry-pi >> "


void command_line(void);
void echo(char *str);
void show_logo(void);
void show_rotating_bars(void);
void help(void);

#endif
