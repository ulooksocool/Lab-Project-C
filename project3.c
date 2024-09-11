

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
  int line;
  struct node *next;
} node;

#define rows 250000
#define cols 100
char words[rows][cols];
node *ptarr[rows];
int df[rows];

void freeeverything(void)
{
  int i;
  node *p;

  for (i = 0; i < rows; i++)
  {

    p = ptarr[i];
    while (p != NULL)
    {
      p = p->next;
      free(ptarr[i]);
      ptarr[i] = p;
    }
  }
}

int h(char *token)
{
  //503 41
  int i;
  int num = 5683;

  for (i = 0; token[i] != '\0'; i++)
  {
    num = num * 59 + token[i];
  }

  return num % rows;
}

void search_query(char *choise)
{
  int fkey, i, c;

  for (i = 0; i < cols; i++)
  {
    choise[i] = tolower(choise[i]);
  }

  fkey = h(choise);
  node *p;

  c = fkey - 1;
  for (i = fkey; i < rows; i++)
  {
   // printf("\n word: %s   %s \n", choise, strcmp(words[i], words[i]));
    if ((words[i] != NULL) && (strcmp(words[i], choise) == 0))
    {
      c = -2;
      printf("\n word: %s \n found at line/lines=[", choise);
      p = ptarr[i];
      while (p != NULL)
      {
        printf(" %d ,", p->line);
        p = p->next;
      }
      printf("] \n");
      break;
    }
    if (i == (rows - 1))
    {
      i = 0;
      c++;
    }
  }
  if (c != -2)
  {
    printf("Document not found!!\n");
  }
}

void search_stats(char *choise)
{
  int fkey, i, c;

  for (i = 0; i < cols; i++)
  {
    choise[i] = tolower(choise[i]);
  }

  fkey = h(choise);
  node *p;

  c = fkey - 1;
  for (i = fkey; i < rows; i++)
  {
    if (c = i)
    {
      break;
    }
    if (strcmp(words[i], choise) == 0)
    {
      c = -2;
      printf("\n word: %s , found %d times ", choise, df);
      break;
    }
    if (i == (rows - 1))
    {
      i = 0;
      c++;
    }
  }
  if (c != 2)
  {
    printf("Zero Times");
  }
}

int creation(int x, char token[], int size)
{

  int c = h(token), i, k, j;

  //pou to h(token) megalitero apo tous pinakes
  k = c - 1;
  for (i = c; i < rows; i++)
  {
    if (i = k)
    {
      break;
    }
    if (strcmp(words[i], token) == 0)
    {
      for (j = 0; j < cols; j++)
      {

        words[i][j] = token[j];
        //printf("\n157: array=%s size=%d  , x=%d i=%d\n", token, size, x, i);
      }
      df[i] = 1;

      node *p = ptarr[i];
      while (p != NULL)
      {
        p = p->next;
      }
      p = (node *)malloc(sizeof(node));
      if (p == NULL)
      {
        return 1; //no memory
      }
      p->line = x;
      return 0;
    }
    if ((i + 1) == rows)
    {
      k = c;
      i = 0;
    }
  }

  //an den uparxei hdh balto se adeia thesi
  k = c - 1;
  for (i = c; i < rows; i++)
  {
    if (i = k)
    {
      break;
    }
    if (words[i][0] == '\0')
    {
      for (j = 0; j < cols; j++)
      {

        words[i][j] = token[j];
        //printf("\n143: array=%s size=%d  , x=%d i=%d\n", token, size, x, i);
      }
      df[i] = 1;

      node *p = ptarr[i];
      while (p != NULL)
      {
        p = p->next;
      }
      p = (node *)malloc(sizeof(node));
      if (p == NULL)
      {
        return 1; //no memory
      }
      p->line = x;
      return 0;
    }
    if ((i + 1) == rows)
    {
      k = c;
      i = 0;
    }
  }

  return 0;
}

void load(char filename[])
{
  int j, i;
  int flength = 0;
  
 
  for (i = 0;filename[i]!='\0'; i++)
  {
    if(!(isalpha(filename[i])||(filename[i]=='.'))){
      for(j=i;filename[j]!='\0';j++)
        filename[j]=filename[j+1];
        if(filename[j+1]=='\0'){
          filename[j]='\0';
        }
    }
  }
  
  for (i = 0;filename[i]!='\0'; i++)
  {
    flength++;
  }
  flength++;
 // printf("\n%d %s\n",flength,filename);
  char myfile[flength];
  for (i = 0;i<flength; i++)
  {
    myfile[i]=filename[i];
  }
  

//  printf("\n%d %s\n",flength,myfile);
  FILE *file; //mallon error!
  file = fopen(myfile, "r");

  if (file == NULL)
  {
    printf(" \n ERROR! FILE DOES NOT EXIST OR CAN NOT BE READ!! \n");
    return;
  }

  char c;
  int count = 0, s = -1, x = 0, flag = 0;
  i = 0;
  char arr[cols];
  for (i = 0; i < cols; i++)
  {
    arr[i] = '\0';
  }
  i = 0;
  while ((c = fgetc(file)) != EOF)
  {
    //printf("%d-->%s-->%d-->%d-->%d-->%d-->%c\n", count, arr, s, x, flag, i, c);
    if ((s != -1) && (c == ':'))
    {
      s = s / 10;
      x = s;
      s = -1;
      if (x != count)
      {
        x = 0;
      }
      // printf("\n204: s=%d  , x=%d\n", s, x);
      continue;
    }
    if (isdigit(c))
    {
      if (s == -1)
      {
        s = 0;
      }
      s += c - '0';
      s *= 10;
      //printf("\n215: s=%d  \n", s);
      //i++;
      continue;
    }

    if ((c == ' ') && (flag == 0))
    {
      continue;
    }
    if (ispunct(c))
    {
      continue;
    }
    if (isalpha(c))
    {

      arr[i] = c;
      i++;
      s = -1;
      flag = 1;
      // printf("\n235: array=%s  ,  s=%d , flag=%d  ,i=%d \n", arr, s, flag, i);
    }
    else
    {

      if (flag == 1)
      {

        for (j = 0; j < cols; j++)
        {
          arr[j] = tolower(arr[j]);
          //    printf("\n246: j=%d--> array=%c \n", j, arr[j]);
        }

        creation(x, arr, cols);

      //  printf("251: count=%d---->array=%s\n", count, arr);  //remove to see fill
      }

      for (i = 0; i < cols; i++)
      {
        arr[i] = '\0';
      }
      i = 0;
      flag = 0;
      //s=0;
    }
    if (c == '\n')
    {
      x = s = -1;
      count++;
      continue;
    }
  }
  fclose(file);
}

int main(int argc, char *argv[])
{

  char c;
  int i;
  if (argc != 3)
  {
    printf("Wrong arguments");
  }

  if (argc == 3)
  {

    if (strncmp(argv[1], "load", 4) == 0)
    {
      load(argv[2]);
    }
  }

  char token[6], choise[100];
  for (i = 0; i < 5; i++)
  {
    token[i] = '\0';
  }
  for (i = 0; i < cols; i++)
  {
    choise[i] = '\0';
  }

  while (1)
  {
    printf("\n\t~ load \" insert_file.txt \"\n");
    printf("\t~ query \" insert_word_to_search \"\n");
    printf("\t~ stats \" insert_word_to_search \" \n");
    printf("\t~ exit \n");

    //kanei energeies =)
    fgets(token, 5, stdin);
    //file or word
    fgets(choise, cols, stdin);

    if (!(strncmp(token, "load", 4)))
    {
      load(choise);
    }
    else if (!(strncmp(token, "query", 5)))
    {
      search_query(choise);
    }
    else if (!(strncmp(token, "stats", 5)))
    {
      search_stats(choise);
    }
    else if (!(strncmp(token, "exit", 4)))
    {
      freeeverything();
      break;
    }

    for (i = 0; i < 5; i++)
    {
      token[i] = '\0';
    }
    for (i = 0; i < cols; i++)
    {
      choise[i] = '\0';
    }
  }
}