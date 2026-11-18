#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <bios.h>
#include <time.h>

typedef unsigned int uint;

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

char get_pressed_key()
{
   union REGS r;

    char function = 0x00; // get pressed key

    r.h.ah = function;
    r.h.al = 0;

    int86(0x16, &r, &r);

    return r.h.al;
} 

// Returns 1 if a key was pressed
// Does not wait
int check_pressed_key()
{
    char function = 0x01; // get key

    int got_char = 0;

    // After the interrupt call the Zero flag is clear if there was a character
    // We cannot easily get the Zero flag using the WATCOM routines, so instead do the whole thing in ASM

    _asm {
        mov ah, function
        int 0x16
        jz no_key
        mov got_char, 1
    no_key:
    }

    return got_char;
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
    uint count = 0;
    
    printf("Press any key to stop drawing\n");

    while ( 1 )
    {
        uint x = rand();
        uint y = rand();
        char colour = rand();

        set_pixel(x, y,  colour);

        // Dont check the keyboard every single pixel, this would be too slow
        // Check only every N pixels 
        count++;
        if (count >= 10000)
        {
            count = 0;

            if ( check_pressed_key() )
                break;

        } 
    }
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
    
    char key;
    int count = 0;
    // First some text mode stuff
    printf("Welcome! Press a key to continue\n");  // Print using the std library
    
    while (check_pressed_key() != 1)
    {
        delay(100);
        count++;
        printf("Nothing pressed %d\n", count);
    }

    key = get_pressed_key();
    printf("Key pressed: %c\n", key);
    getch();

    set_cursor_pos(20, 20);
    print("Repositioned to (20,20)"); // Print using BIOS functions
    getch();

    // Now some graphical stuff
    set_video_mode(0x13);   // 0x13 is VGA mode 320x200 256 colour 
    
    random_pixels();
    // getch();

    draw_horizontal_lines();
    getch();
   
    // Back to text mode
    set_video_mode(0x03);   // Back to normal text mode (80x25 colour text)
    
    return 0;
}
