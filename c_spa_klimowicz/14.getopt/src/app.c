// based on https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
// 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "ab:c:")) != -1)
    switch (c)
      {
      case 'a':
          printf("a \n");
          break;
      case 'b':
        printf("b ");
        printf("%s \n",optarg);
        break;
      case 'c':
        printf("c ");
        printf("%s ",optarg);
        while ((optind < argc)&&(argv[optind][0]!='-'))
        {
            // more arguments
            printf("%s ",argv[optind]);
           ++optind; 
        }
        printf("\n");
        break;
      default:
        abort ();
      }

  printf("end of parsing \n");

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);

  return 0;
}

