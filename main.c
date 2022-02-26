// Your C source code will go here.
// Feel free to replace this file with lab2base.c:
// (note this will get overwrite of the contents of this file)
// 	wget https://eecs.wsu.edu/~cs360/samples/LAB2/lab2base.c && mv lab2base.c t.c
#include <stdio.h>             // for I/O
#include <stdlib.h>            // for I/O
#include <libgen.h>            // for dirname()/basename()
#include <string.h>

typedef struct node{
         char  name[64];       // node's name string
         char  type;           // 'D' for DIR; 'F' for file
   struct node *child, *sibling, *parent;
}NODE;


NODE *root, *cwd, *start;
char line[128];
char command[16], pathname[64];
char *names[5], *ouch = "";

//               0       1      2       3        4       5      6       7      8
char *cmd[] = {"mkdir", "ls", "quit", "menu", "creat", "cd", "rmdir", "pwd", "rm", 0};

int findCmd(char *command)
{
   int i = 0;
   while(cmd[i]){
     if (strcmp(command, cmd[i])==0)
         return i;
     i++;
   }
   return -1;
}

NODE *search_child(NODE *parent, char *name)
{
  NODE *p;
  printf("search parent DIR %s for %s\n", parent->name, name);
  p = parent->child;
  if (p==0)
    return 0;
  while(p){
    if (strcmp(p->name, name)==0)
      return p;
    p = p->sibling;
  }
  return 0;
}

NODE *path2node(char *pathname)
{
    char *s;
    int n = 0;

    if (pathname[0]=='/')
    {
        start = root;
    }
    else
    {
        start = cwd;
    }

    /* gpath[] =[thisAB/thatCD/hereEF0]
                          	       [thisAB0thatCD0hereEF0] 
                                        |      |      |
                                     name[0] name[1] name[2]
                                     |<------ n = 3 -------->| */

    // printf("n=%d, pathname=%s\n", n, pathname);

    NODE *p = start;

    s = strtok(pathname, "/");

while (p)
{

        printf("i am in %s\n", s);
        p = search_child(p, s);
        s = strtok(NULL, "/");
}

	    if (p==0)
        { 
            printf("Could not find node. rmdir fail.");
            return 0;
	    }

       return p;
}	

int insert_child(NODE *parent, NODE *q)
{
  NODE *p;
  printf("insert NODE %s into END of parent child list\n", q->name);
  p = parent->child;
  if (p==0)
    parent->child = q;
  else{
    while(p->sibling)
      p = p->sibling;
    p->sibling = q;
  }

  q->parent = parent;
  q->child = 0;
  q->sibling = 0;
}

/***************************************************************
 This mkdir(char *name) makes a DIR in the current directory
 You MUST improve it to mkdir(char *pathname) for ANY pathname
****************************************************************/

int mkdir(char *name)
{
    char *s, *copy, *z;
  NODE *p, *q;
  // fgets(line, 128, stdin);
  printf("mkdir: name=%s\n", name);

  // WRITE C code : do not allow mkdir of / or . or ..

    if (strcmp(name, "/") == 0 || strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
    {
        printf("This directory has an invalid name. mkdir failed\n");
        return -1;
    }

  if (name[0]=='/')
    start = root;
  else
    start = cwd;

  // printf("check whether %s already exists\n", name);
  p = search_child(start, name);
  if (p){
    printf("name %s already exists, mkdir FAILED\n", name);
    return -1;
  }
  printf("--------------------------------------\n");
  printf("ready to mkdir %s\n", name);
  q = (NODE *)malloc(sizeof(NODE));
  q->type = 'D';
  strcpy(q->name, name);

    // FIX IT HERE

    p = start;

    strcpy(copy, name);
      
    z = strtok(copy, "/");
    z = strtok(0, "/");


    if (z)
    {
        s = strtok(name, "/");

      /*while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;
        p = p->sibling;
    }*/
    
    // s = strtok(name, "/");

    // printf("%s\n", name);

    while(s)
    {
        if (p->child)
        {
            p = p->child;
        }

        else
            break;

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                // printf("%s\n", p->name);
                break;
            }

            p = p->sibling;
        }

        s = strtok(0, "/");

    }

  strcpy(q->name, s);
  insert_child(p, q);         // add node as child of parent DIR 
  printf("mkdir %s OK\n", s);
  printf("--------------------------------------\n");


    }
    // MY CODE ABOVE

else
{
  insert_child(p, q);         // add node as child of parent DIR 
  printf("mkdir %s OK\n", name);
  printf("--------------------------------------\n");
}

  return 0;
}

int creat(char *name)
{
    char *s, *copy, *z;
  NODE *p, *q;
  // fgets(line, 128, stdin);
  printf("creat: name=%s\n", name);

  // WRITE C code : do not allow mkdir of / or . or ..

    if (strcmp(name, "/") == 0 || strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
    {
        printf("This directory has an invalid name. creat failed\n");
        return -1;
    }

  if (name[0]=='/')
    start = root;
  else
    start = cwd;

  // printf("check whether %s already exists\n", name);
  p = search_child(start, name);
  if (p){
    printf("name %s already exists, creat FAILED\n", name);
    return -1;
  }
  printf("--------------------------------------\n");
  printf("ready to creat %s\n", name);
  q = (NODE *)malloc(sizeof(NODE));
  q->type = 'F';
  strcpy(q->name, name);

    // FIX IT HERE

    p = start;

    strcpy(copy, name);
      
    z = strtok(copy, "/");
    z = strtok(0, "/");


    if (z)
    {
        s = strtok(name, "/");

      /*while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;
        p = p->sibling;
    }*/
    
    // s = strtok(name, "/");

    // printf("%s\n", name);

    while(s)
    {
        if (p->child)
        {
            p = p->child;
        }

        else
            break;

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                printf("%s\n", p->name);
                break;
            }

            p = p->sibling;
        }

        s = strtok(0, "/");

                

        if (p->child && strcmp(s, p->child->name) != 0)
        {
            break;
        }
    }

  strcpy(q->name, s);
  insert_child(p, q);         // add node as child of parent DIR 
  printf("creat %s OK\n", s);
  printf("--------------------------------------\n");


    }
    // MY CODE ABOVE

else
{
  insert_child(p, q);         // add node as child of parent DIR 
  printf("creat %s OK\n", name);
  printf("--------------------------------------\n");
}

  return 0;
}

// This ls() list CWD. You MUST improve it to ls(char *pathname)
int ls(char *pathname)
{
    char *s;
    int n = 0;
    NODE* p = cwd->child;

    if (strcmp(pathname, "") == 0)
    {

        printf("cwd contents = ");
  
        while (p)
        {
            if (p->name[0] != '\0')
            {
            printf("['%c' %s] ", p->type, p->name);
            }
            p = p->sibling;
        }

        printf("\n");
        return;
    }
    s = strtok(pathname, "/"); // first call to strtok()

    while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;

        p = p->sibling;
    }

    s = strtok(0, "/");

    while(s)
    {
        p = p->child;

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                break;
            }

            p = p->sibling;
        }

        s = strtok(0, "/");
    }

    p = p->child;

    while (p)
    {
        if (p->name[0] != '\0')
        {
            printf("['%c' %s] ", p->type, p->name);
        }
        p = p->sibling;
    }



  /*NODE *p = cwd->child;
  printf("cwd contents = ");
  
  while (p)
  {
    printf("['%c' %s] ", p->type, p->name);
    p = p->sibling;
  }
*/
  printf("\n");
}

int quit()
{
  printf("Program exit\n");
  exit(0);
}

int initialize()  // create the root DIR / and set CWD
{
    root = (NODE *)malloc(sizeof(NODE));
    strcpy(root->name, "/");
    root->parent = root;
    root->sibling = 0;
    root->child = 0;
    root->type = 'D';
    cwd = root;
    printf("Root initialized OK\n");
}

void menu()
{
    printf("\n======= MENU ======\n");
    printf("mkdir  rmdir  ls  cd  pwd  creat  rm  quit\n");
    printf("===================\n");
}

void cd(char *pathname)
{
    NODE* p;
    char *s, *copy, *z;

    if (strcmp(pathname, "..") == 0)
    {
        cwd = cwd->parent;
        printf("moved to %s\n", cwd->name);
        return;
    }

    else if (strcmp(pathname, "../../") == 0)
    {
        cwd = cwd->parent;
        cwd = cwd->parent;
        printf("moved to %s\n", cwd->name);
        return;
    }

    else
    {
        // returnedCD = search_child(cwd, pathname);

        // FINISH CODE

            p = start;

    strcpy(copy, pathname);
      
    z = strtok(copy, "/");
    z = strtok(0, "/");


    if (z)
    {
        s = strtok(pathname, "/");
    p = p->child;
   // printf("%s\n", s);
    while(s)
    {

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("string: %s\n", s);
            //printf("p->name: %s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                //printf("%s\n", p->name);
                break;
            }

            p = p->sibling;
            printf("%s  ", p->name);
        }

        s = strtok(0, "/");

        if (p->child)
        {
            p = p->child;
        }

        else
            break;
    }

        if (p->type == 'D')
        {
            cwd = p;
            printf("success - cwd:%s\n", cwd->name);
            printf("parent name: %s\n", cwd->parent->name);
        }
        else
        {
            printf("The item specified is a file. cd failed. \n");
        }
    }

    else
    {
        s = strtok(pathname, "/");
        p = p->child;
        while (p)
        {
            printf("%s\n", s);
            printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                cwd = p;
                printf("success - cwd:%s\n", cwd->name);
                printf("parent name: %s\n", cwd->parent->name);
                return;
            }

            p = p->sibling;
            //printf("%s  ", p->name);
        }
    }

}

    return;
}

char* tokenize(char *pathname)
{
    char *s;
    int n = 0;

    s = strtok(pathname, "/"); // first call to strtok()
    while(s)
    {
        printf("%s\n", s);
        s = strtok(0, "/"); // call strtok() until it returns NULL
    }

    return s;
}

int rmdir(char *pathname)
{
    char *s;
    int n = 0;
    NODE* p = cwd->child;

    s = strtok(pathname, "/"); // first call to strtok()

    while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;

        p = p->sibling;
    }

    s = strtok(0, "/");

    while(s)
    {
        p = p->child;

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                break;
            }

            p = p->sibling;
        }

        s = strtok(0, "/");
    }

    //printf("%s\n", p->name);
  
    if (p->name)
    {
        if (p->child)
        {
            printf("This directory is not empty and therefore cannot be removed - rmdir failed.\n");
        }

        else
        {   
            if (p->type != 'D')
            {
                printf("rmdir can not delete a file\n");
                return;
            }

            free(p);
            printf("Successfully removed directory!\n");    
        }
    }

    else 
    {
        printf("The directory could not be found\n");
    }

    /*
    NODE* newNode = path2node(pathname);
    if (!newNode)
    {
        return;    
    }
    else
    {
        if (newNode->child != NULL)
        {
            printf("found %s directory\n", newNode->name);
            NODE* par = newNode->parent;
            free(newNode->parent->child);
            par->child = NULL;
        }
        else
        {
            printf("This directory is not empty and therefore cannot be removed. rmdir failed.\n");
        }
    } */
}

void rm(pathname)
{
    char *s;
    int n = 0;
    NODE* p = cwd->child;

    s = strtok(pathname, "/"); // first call to strtok()

    while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;

        p = p->sibling;
    }

    s = strtok(0, "/");

    while(s)
    {
        p = p->child;

         // call strtok() until it returns NULL
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);

            if (strcmp(s, p->name) == 0)
            {
                break;
            }

            p = p->sibling;
        }

        s = strtok(0, "/");
    }

    //printf("%s\n", p->name);
  
    if (p->name)
    {

        if (p->type != 'F')
        {
            printf("rm can not delete a directory\n");
            return;
        }

        strcpy(p->name, "");
        //free(p);
        printf("Successfully removed file!\n");
    }

    else 
    {
        printf("The file could not be found\n");
    }



    /*char *s;
    int n = 0;
    NODE* p = cwd->child;
    s = strtok(pathname, "/"); // first call to strtok()
    while (p)
    {
        if (strcmp(s, p->name) == 0)
            break;
        p = p->sibling;
    }
    s = strtok(0, "/");
    while(s)
    {
        p = p->child;
        
        while (p)
        {
            //printf("%s\n", s);
            //printf("%s\n", p->name);
            if (strcmp(s, p->name) == 0)
            {
                break;
            }
            p = p->sibling;
        }
        s = strtok(0, "/");
    }
    //printf("%s\n", p->name);
  
    if (p->name)
    {
        if (p->child)
        {
            p->parent->child = p->child;
            free(p);
            printf("Successfully removed file!\n");
        }
        else
        {
            p->parent->child = NULL;
            free(p);
            printf("Successfully removed file!\n");
        }
    }
    else 
    {
        printf("The file could not be found\n");
    }*/
}

void pwd()
{
    char s[20][20] = {""};
    NODE *p = cwd;
    int x = 0;

    if (strcmp(cwd->name, "/") == 0)
    {
        putchar("/\n");
        return;
    }

    for (; strcmp(p->name, "/")!= 0; ++x)
    {
        // printf("%d\n", x);
        strcpy(s + x, p->name);
        // printf("%s\n", s + x);
        p = p->parent;
    }

    for (;x != -1; --x)
    {
        printf("%s", s + x);
        if (x != 0)
        {
            printf("/");
        }
    }

    putchar('\n');
}

int main()
{
  int index;

  initialize();

  while(1){
      printf("Enter command line : ");
      fgets(line, 128, stdin);
      line[strlen(line)-1] = 0;

      command[0] = pathname[0] = 0;
      sscanf(line, "%s %s", command, pathname);
      printf("command=%s pathname=%s, cwd=%s\n", command, pathname, cwd->name);
      
      if (command[0]==0) 
         continue;

      index = findCmd(command);

      switch (index)
      {
        case 0: mkdir(pathname); break;
        case 1: ls(pathname);    break;
        case 2: quit();          break;
        case 3: menu();          break;
        case 4: creat(pathname); break;
        case 5: cd(pathname);    break;
        case 6: rmdir(pathname); break;
        case 7: pwd();           break;
        case 8: rm(pathname);    break;
      }
  }
}
