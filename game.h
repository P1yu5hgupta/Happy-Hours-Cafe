int flag=0;
struct verticalStack
{
 int top;
 char a[6];
};
 struct verticalStack s1,s2,s3,s4;
 void iniStack(struct verticalStack s)
 {
  s.a[0]=s.a[1]=s.a[2]=s.a[3]=s.a[4]=s.a[5]='\0';
  s.top=-1;
 }
 void pop(struct verticalStack s)
 {
  s.a[s.top--]=' ';
 }
 void push(struct verticalStack s,char c)
 {
  s.top++;
  if(s.top<=5)
   {
   s.a[s.top]=c;
   } 
  else
   flag=-1;
 }
 bool checkAndDelete(struct verticalStack s)
 {
  char temp_top=s.top;
  char x=s.a[temp_top--];
  //getchar();
  if(x==s.a[temp_top--])
  {
   if(x==s.a[temp_top])
   {
    pop(s);
    pop(s);
    pop(s);
    return true;
   }
   else
    return false;
  }
  else
   return false;
 }
void layout(char c,int score)
{
 printf("    _________________________________________________________\n");
 printf("    |    _______       _______       _______       _______  |\n");
 printf("    |                                                       |\n");
 printf("    |      %c             %c            %c            %c    |\n",s1.a[5],s2.a[5],s3.a[5],s4.a[5]);
 printf("    |                                                       |\n");
 printf("    |    _______       _______       _______       _______  |                          _________\n");
 printf("    |                                                       |                         |         |\n");
 printf("    |      %c             %c            %c            %c    |                         |         |\n",s1.a[4],s2.a[4],s3.a[4],s4.a[4]);
 printf("    |                                                       |                         |    %c   |\n",c);
 printf("    |    _______       _______       _______       _______  |                         |         |\n");
 printf("    |                                                       |                         |_________|\n");
 printf("    |      %c             %c            %c            %c    |\n",s1.a[3],s2.a[3],s3.a[3],s4.a[3]);
 printf("    |                                                       |\n");
 printf("    |    _______       _______       _______       _______  |                       SCORE = %d\n",score);
 printf("    |                                                       |\n");
 printf("    |       %c            %c            %c             %c   |\n",s1.a[2],s2.a[2],s3.a[2],s4.a[2]);
 printf("    |                                                       |\n");
 printf("    |    _______       _______       _______       _______  |\n");
 printf("    |                                                       |\n");
 printf("    |       %c            %c            %c             %c   |\n",s1.a[1],s2.a[1],s3.a[1],s4.a[1]);
 printf("    |                                                       |\n");
 printf("    |    _______       _______       _______       _______  |\n");
 printf("    |                                                       |\n");
 printf("    |       %c            %c            %c             %c   |\n",s1.a[0],s2.a[0],s3.a[0],s4.a[0]);
 printf("    |                                                       |\n");
 printf("    |___________|_____________|_____________|_______________|\n");
 printf("          1             2            3              4        \n");
}
void stack()
{
w:  printf(" ");
    int r,game;
 time_t t;
    srand((unsigned) time(&t));
    int score=0;
 while(1)
 {
        int ip;
     system("cls");
  r=35+(rand()%6);
  char b=r;
  layout(b,score);
  printf("\n----------------------------------------------------------------------->>>>>  Enter Stack number: ");
  scanf("%d",&ip);
  if(ip==1)
  {
   push(s1,b);
   if(flag==-1)break;
   if(checkAndDelete(s1))
    score+=15;
  }
  else if(ip==2)
  {
   push(s2,b);
   if(flag==-1)break;
   if(checkAndDelete(s2))
    score+=15;
  }
  else if(ip==3)
  {
   push(s3,b);
   if(flag==-1)break;
   if(checkAndDelete(s3))
    score+=15;
  }
  else if(ip==4){
   push(s4,b);
   if(flag==-1)break;
   if(checkAndDelete(s4))
    score+=15;
  }
 }
 system("cls");
 printf("GAME OVER!!! XoX, your Score is: %d \nTo play again press 1 or 0 to exit--->> ",score);
 scanf("%d",&game);
 if(game==1)
  goto w;
}
