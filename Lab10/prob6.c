/* i.e., 16KB.  The array needs to be at least twice the size of the
   8KB cache so that the array doesn't fit in memory. */
#define ARRAY_SIZE 16*2048 
#define NUM_LOOPS 100

int main()
{
  char array[ARRAY_SIZE];
  register int outer_loop;
  register int inner_loop;
  register int solution = 0;
  register int i = 0;

  for (outer_loop = 0; outer_loop < NUM_LOOPS; outer_loop++)
    {
      for (inner_loop = 0; inner_loop < ARRAY_SIZE; inner_loop++)
	  {
		if(i == 0)
		{
			solution *= array[0];
			i++;
		}
		else if(i == 1)
		{
			solution *= array[4096];
			i++;
		}
		else if(i == 2)
		{
			solution *= array[8192];
			i++;
		}
		else if(i == 3)
		{
			i = 0;
		}
	  }
	
    }
  return solution;
}
