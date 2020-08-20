char *color = (char*)0x70;
char *vidptr = (char*)0xb8000;
unsigned int curser_y = 1;
unsigned int io_i = 0;
unsigned int io_j = 0;

void clear(void);

void newline(void){
io_i = (io_i + ((160 * curser_y)- io_i)) - 2;
curser_y = curser_y + 1;
if (curser_y > 20){
	curser_y = 0;
	clear();
}
return;
}

void mvch(unsigned int x, unsigned int y){
io_i = y * 160;
io_i += (x*2);
}

void print(char *str){
	io_j = 0;
	/* this loop writes the string to video memory */
	while(str[io_j] != '\0') {
		if (str[io_j] == '\n'){
			newline();
		} else {
		/* the character's ascii */
		vidptr[io_i] = str[io_j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[io_i+1] = (int)color;
		}
		++io_j;
		io_i = io_i + 2;
	}
	if (io_i > (80 * curser_y)){
		curser_y++;
	}
    return;
}

void clear(){
	io_j = 0;
    /* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(io_j < 80 * 25 * 2) {
		/* blank character */
		vidptr[io_j] = ' ';
		/* color-attribute-byte */
		vidptr[io_j+1] = (int)color; 		
		io_j = io_j + 2;
	}
	curser_y = 1;
    io_i = 0;
	return;
}

void changeColor(char *newColor){
color = newColor;
return;
}

void setTheme(char *theme){
	changeColor(theme);
	io_j = 1;
	while(io_j < 80 * 25 * 2) {
		vidptr[io_j] = (int)theme;		
		io_j += 2;
	}
    return;
}