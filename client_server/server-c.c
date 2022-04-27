//Server code from the book

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

int response(char * chosenWord, int lives, char unknownWord[])
{
  
  //opens txt file to read char from
  FILE *fp;
  char c;
  char * pch;
  int index;
  bool found = false;
  
  fp = fopen("a.txt", "r");
  c = fgetc(fp);
  fclose(fp);

  pch = strchr(chosenWord, c);

  //code to print out entire txt file (for testing purposes if needed)
  /* 
  while (c != EOF)
  {
    
    //printf ("%c", c);
    c = fgetc(fp);
  }
  */

  //TODO: put the guess into the right index in the array then print out the full array with the blanks filled in based on the guesses
  while(pch!=NULL)
  {
    index = (int)(pch-chosenWord);
    
    printf("found at %d\n", index);
    printf("correct guess, lives remaining: %d\n", lives);
    pch=strchr(pch+1,c);
    found = true;
    fp = fopen("a.txt", "w");

  }
  if(found == false)
  {
    lives--;
    printf("Incorrect guess, lives remaining: %d\n", lives);
    if(lives == 0)
    {
      printf("%s", "Game Over, you lose\n");
      exit(0);
    }
      
    return lives;
  }

  

  return lives;
}

int
main()
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  char * chosenWord;
  char unknownWord[] = "";
  int buf_len, addr_len;
  int s, new_s;
  int lives = 5;
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
  chosenWord = wordList[n];
  
  //loop to create new string of blanks (underscores) to match the length of the chosenWord
  for (int i = 0; i < strlen(chosenWord); i++)
  {
    strcat(unknownWord, "_");
  }
  //printf("%s", unknownWord);
  //fflush(stdout);

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
printf("%s", chosenWord);
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
        /* For loop compares char to the chosen word */
       
      
        
      fp = fopen("a.txt", "w");
      fputs(buf, fp);
      fclose(fp);
      
      lives = response(chosenWord, lives, unknownWord);
      fflush(stdout);
    }
    //fp = fopen("a.txt","r");
    //fflush(fp);
    //fclose(fp);
    //fflush(stdout);
    close(new_s);
  
  
  }

}