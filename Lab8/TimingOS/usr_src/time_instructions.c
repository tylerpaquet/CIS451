/******************************************************************
 * time_branches.c
 *
 * Time instruction sequences of varying lengths
 *
 * (C) 2016 Zachary Kurmas
 ******************************************************************/


#include "timingos.h"
#include "vga.h"
#include "util.h"

terminal_section_t debug;


// It is assumed that a separate C file will define and populate this array
// It represents the list of functions to be timed.
int num_functions;
unsigned long long (*functions[5000])();


///////////////////////////////////////////////////////////////////////
//
// Repeatedly time the code passed in function_to_time and report 
// statistics.
//
///////////////////////////////////////////////////////////////////////
static void time_instructions (unsigned long long (*function_to_time)(),
				 int exp_index,
				 terminal_section_t* head, 
				 terminal_section_t* body) {

  int iterations = 1000;
  int warm_up =100;

  // Warm up the cache with "untimed" runs
  // However, we keep track of the minimum so that the 
  // compiler doesn't optimize the loop away.
  unsigned long long min = function_to_time();
  for (int i = 0; i < warm_up; i++) {
    unsigned long long value = function_to_time();
    min = (value < min) ? value : min;
  }

  unsigned long long max = 0;
  unsigned long long sum = 0;
  unsigned long long sum_sq = 0;
  unsigned long long variance = 0;
  for (int i = 1; i <= iterations; i++) {

    // Generate a data piont
    unsigned long long value = function_to_time();

    // Do the "recordkeeping" (update sum, min, max, etc.)
    sum += value;
    sum_sq += value*value;
    if (value > max) {
      max = value;
    }
    if (value < min) {
      min = value;
    }
    // Take care not to divide by 0 if i < 2
    variance = i>=2 ? (i*sum_sq - sum*sum)/(i*(i-1)) : 0;
    //end starter code removal ')


    // Put the last line of output in the head
    terminal_section_t* output = (i == iterations) ? head : body;
    int print_me = (i == iterations) ? exp_index : i;

    terminal_write_unsigned(output, print_me, ": cur=");
    terminal_write_unsigned(output, value, ", avg=");
    terminal_write_unsigned(output, (sum/i), ", min=");
    terminal_write_unsigned(output, min, ", max=");
    terminal_write_unsigned(output, max, ", var=");
    terminal_write_unsigned(output, variance, "\n");
  }// end

#ifdef DEBUG
  // Print extra information to stdout when runing in debug mode 
  // (i.e., as a "normal" user process)
  printf("%5d  %10llu %10llu\n", exp_index*25, min, (sum/iterations));
#endif

}


/////////////////////////////////////////////////////////////////
//
// This is the entry point for our "timingOS"
//
///////////////////////////////////////////////////////////////////
void time_instructions_kernel_main() {
  randomize(0);
  
  /* Initialize terminal interface.  This function must always be
     called.  It sets up the text buffer. 
  */
  terminal_initialize();  

  /* Now, set up the individual text areas.  The code here sets up 
     two text areas: The bottom line is a "debug" area.  The rest
     is for "normal" output.
  */
  terminal_section_t body;
  int debug_window_height = 1;
  terminal_section_initialize(&body, 0, VGA_HEIGHT-debug_window_height -1, 
			      0, VGA_WIDTH-1);
  terminal_section_initialize(&debug, VGA_HEIGHT-debug_window_height, 
			      VGA_HEIGHT-1, 
			      0, VGA_WIDTH-1);
  
  for (int i = 0; i < num_functions; i++) {
    time_instructions(functions[i],i, &body, &debug);
  }


}

