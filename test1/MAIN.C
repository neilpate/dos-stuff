#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;


int sub(int num){
    return num-1;
}

void print(char* string)
{
    union REGS r;

    // string will be automatically null terminated
    // But calling strlen returns the length of the actual content
    // Pad it by one as we will need to append the $
    char* buffer = malloc(strlen(string)+ 1);
    if (buffer == NULL){
        return; //For now just silence the error
    }
    else {

        int length = strlen(string);
        
       memcpy(buffer, string, length);

        // And finally append the final termination character DOS wants
        buffer[length] = '$';

        r.h.ah = 0x09;
        r.x.dx = (unsigned) buffer;
	    intdos(&r, &r);
        
        free(buffer);
        
    }
}

void set_cursor_pos(unsigned char line, unsigned char col)
{
    union REGS r;

    char function = 0x02; // position cursor 

    r.h.ah = function;  
    r.h.bh = 0; // Screen page number
    r.h.dh = line; // Screen line
    r.h.dl = col; // Screen line

    int86(0x10, &r, &r);

    
}

void set_video_mode(unsigned char mode)
{
    union REGS r;

    unsigned char function = 0x00; // set video mode 

    r.h.ah = function;
    r.h.al = mode;  // e.g. 1 = 40x25 text

    int86(0x10, &r, &r);

}

void set_pixel(uint x, uint y, unsigned char colour)
{

    union REGS r;

    char function = 0x0C; // write pixel

    r.h.ah = function;
    r.h.al = colour;
    r.h.bh = 0; // graphics page. For now keeping at 0 
    r.x.cx = x;
    r.x.dx = y;

    int86(0x10, &r, &r);

}

void draw_horizontal_line(uint x_start, uint x_stop, uint y, unsigned char colour )
{
    int x; 
    for (x = x_start; x < x_stop; x++ ){
        set_pixel(x, y, colour);
    }
}

void random_pixels()
{
    uint count;

    for (count = 0; count < 0xffff; count++)
    {
        uint x = rand();
        uint y = rand();
        char colour = rand();

        set_pixel(x, y,  colour);
    }

    print("Random pixels done");
}

void draw_horizontal_lines()
{
     int y;
    for (y = 0; y < 200; y++)
    {
        draw_horizontal_line(000, 320, y, y);

    }

}

int main() {
    
    
    // First some text mode stuff
    printf("Welcome!!!\n");  // Print using the std library
    
    set_cursor_pos(10, 10);
    print("Repositioned"); // Print using BIOS functions
    
    getch();
    
    // Now some graphical stuff
    set_video_mode(0x13);   // 0x13 is VGA mode 320x200 256 colour 
    
    random_pixels();

    draw_horizontal_lines();
   
    // Back to text mode
    set_video_mode(0x03);   // Back to normal text mode (80x25 colour text)
    
    return 0;
}
