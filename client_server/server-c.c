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

void response(char *chosenWord, int *lives, char *blankWord)
{
  //opens txt file to read char from
  FILE *fp;
  //chosen letter by client
  char c;
  //used to search through string
  char * pch;
  char* gamewinch;
  //location of letter in word
  int index;
  //turns true if letter is in word
  bool found = false;
  //used to update lives counter
  int temp = *lives;
  //gets letter input by client from text file
  fp = fopen("a.txt", "r");
  c = fgetc(fp);
  fclose(fp);
  pch = strchr(chosenWord, c);

  //loops through the word to find multiple instances of the chosen letter
  while(pch!=NULL)
  {
    index = (int)(pch-chosenWord);

    //adds the letter if found to the blank word
    blankWord[index] = c;

    //displays the index, lives remaining, and the letters found with dashes
    printf("found at %d\n", index);
    printf("correct guess, lives remaining: %d\n", *lives);
    printf("the word is %s\n",blankWord)

    //increments to the index found in order to search through the word again
    pch=strchr(pch+1,c);

    found = true;    
  }

  //if the word has no more _ the client has won and the game exits
  if (strchr(blankWord, '_') == NULL)
  {
      printf("%s", " You Win!\n");
      exit(0);
  }
  
  //if the chosen letter is not in the word lives are decremented and if no lives are left the user loses and exits
  if(found == false)
  {
    *lives = temp - 1;
    printf("Incorrect guess, lives remaining: %d\n", *lives);
    if(*lives == 0)
    {
      printf("%s", "Game Over, you lose\n");
      exit(0);
    }
  }
}

int
main()
{
  //variables
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  char * chosenWord;
  char* unknownWord[] = {};
  int buf_len, addr_len;
  int s, new_s;
  int gameLives = 5;
  FILE* fp;

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);

  //word list
  const char* wordList[] = {
    "purple", "blue", "yellow", "orange", "white", "tiger",
    "alligator", "zebra", "elephant", "shark"
  };

  //choses random word from list
  srand((unsigned)time(NULL));
  int n = rand()%10;
  chosenWord = wordList[n];
  
  //loop to create new string of blanks (underscores) to match the length of the chosenWord
  for (int i = 0; i < strlen(chosenWord); i++)
  {
    strcat(unknownWord, "_");
  }

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
    if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) 
    {
      perror("simplex-talk: accept");
      exit(1);
    }
    
    while (buf_len = recv(new_s, buf, sizeof(buf), 0))
    {
      fp = fopen("a.txt", "w");
      fputs(buf, fp);
      fclose(fp);
      
      //call funtion every time a letter is chosen by the client
      response(chosenWord, &gameLives, unknownWord);
      fflush(stdout);
    }
    
    close(new_s);
  }
}



