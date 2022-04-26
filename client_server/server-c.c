//Server code from the book

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

void response()
{
  
  //opens txt file to read char from
  FILE *fp;
  char c;
  
  fp = fopen("a.txt", "r");
  c = fgetc(fp);
  
  //TODO: next step is to change these if statements below to compare char to a word that the server chooses and printf the correct response
  //compare char to a letter and printf a certain response
  if (c == 'y')
  {
    printf("%s", "yes \n");
  }
  if (c == 'n')
  {
    printf("%s", "no \n");
  }

  //code to print out entire txt file (for testing purposes if needed)
  /* 
  while (c != EOF)
  {
    
    //printf ("%c", c);
    c = fgetc(fp);
  }
  */
  

  
  fclose(fp);

  

  return 0;
}

int
main()
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  int buf_len, addr_len;
  int s, new_s;
  FILE* fp;

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);

  //Choose random word
  const char* wordList[] = {
    "purple", "blue", "yellow", "orange", "white", "tiger",
    "alligator", "zebra", "elephant", "shark"
  };
  srand((unsigned)time(NULL));
  int n = rand()%10;

  /* setup passive open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  listen(s, MAX_PENDING);

//Prints random word chosen (for testing purposes)
printf("%s", wordList[n]);
fflush(stdout);

//TODO: allow multiple clients to connect
 /* wait for connection, then receive and print text */
  while(1) {
    if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) {
      perror("simplex-talk: accept");
      exit(1);
    }
    
    while (buf_len = recv(new_s, buf, sizeof(buf), 0))
    {
      //TODO: instead of just printing, use buffer to compare char to entire word then send back result to 
      
      fp = fopen("a.txt", "w");
      fputs(buf, fp);
      fclose(fp);
      
     response();
      fflush(stdout);
    }
    //fp = fopen("a.txt","r");
    //fflush(fp);
    //fclose(fp);
    //fflush(stdout);
    close(new_s);
  
  
  }

}