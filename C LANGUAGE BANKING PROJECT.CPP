# include <dos.h>
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
// stucture-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  struct bank
  {
     char name[50],type;
     int acc,ofbal;
  };
struct cashbook
{
	int acno;
	char transtype;
	int tamt,bamt;

};
// box-------------------------------------------------------------------------------------------------------------------------------------------
  void box()
  {
    char ch=216;
    int i;
       for (i=1 ; i<=78 ; i++)
       {
	   gotoxy(i,1);
	   cprintf("%c%c",ch,ch);
	   delay(10);
       }
       for (i=1 ; i<=25 ; i++)
       {
	   gotoxy(78,i);
	   cprintf("%c%c",ch,ch);
	   delay(10);
       }
      for (i=78 ; i>=1 ; i--)
       {
	   gotoxy(i,25);
	   cprintf("%c%c",ch,ch);
	   delay(10);
       }
      for (i=25 ; i>=1 ; i--)
       {
	   gotoxy(1,i);
	   cprintf("%c%c",ch,ch);
	   delay(10);
       }
  }
// add account -----------------------------------------------------------------------------------------------------------------------------
  void add()
  {
      struct bank b,d;
      int m=0;
      FILE *p,*q;
      p=fopen("bank.txt","rb");
      if(p)
      {
	  while(fread(&d,sizeof(d),1,p))
	  {
		m=d.acc;
	  }
      }
      fclose(p);

	  printf("\n enter name:");
	  scanf("%s",&b.name);
	  printf("enter type s/c:");
	  scanf(" %c",&b.type);
	  printf("enter balance:");
	  scanf("%d",&b.ofbal);
	  b.acc= m + 1;
	  printf("\n your account no.: %d",b.acc);

	  q=fopen("bank.txt","ab");
	  fwrite(&b,sizeof(b),1,q);
	  fclose(q);

      printf("\n account added succesfully");
      getch();
  }
// display all accounts----------------------------------------------------------------------------------------------------------
  void displayall()
  {
      struct bank b;
      FILE *p;
      p=fopen("bank.txt","rb");
      printf("\nname\taccount no\ttype\tbalance");
      while(fread(&b,sizeof(b),1,p))
      {
	 printf("\n%s\t%d\t\t%c\t%d ",b.name,b.acc,b.type,b.ofbal);
      }
      fclose(p);
      getch();
  }
// search account----------------------------------------------------------------------------------------------------------------------------
  void searchacc()
  {
      struct bank b;
      int r,flag=0;
      textcolor(14);
      FILE *p;
      p=fopen("bank.txt","rb");
      cprintf(" enter account no.to be found: ");
      scanf("%d",&r);
      while(fread(&b,sizeof(b),1,p))
      {
	if( r==b.acc)
	{
	    cprintf(" name=%s account no.=%d type=%c balance=%d",b.name,b.acc,b.type,b.ofbal);
	    flag=1;
	}
      }
      if ( flag==0)
	  cprintf(" acc not found");
      fclose(p);
      getch();
  }
// delete account------------------------------------------------------------------------------------------------------------------------------
  void deleterecord()
  {
      struct bank b;
      int i,r,flag=0;
      char n[50];
      textcolor(14);
      FILE *p, *q;
      p=fopen("bank.txt","rb");
      q=fopen("temp.new","wb");
      cprintf(" enter account no. to be found: ");
      scanf("%d",&r);
      while(fread(&b,sizeof(b),1,p))
      {
	if ( r!= b.acc )
	{
	    fwrite(&b,sizeof(b),1,q);
	}
	else
	{
	    flag=1;
	}
      }
      fclose(p);
      fclose(q);
      remove("bank.txt");
      rename("temp.new","bank.txt");
      if (flag==0)
	  cprintf("\n account not found");
      else
	  cprintf("\n record deleted");
      getch();
  }
// modify account---------------------------------------------------------------------------------------
  void modify()
  {
      struct bank b;
      int i,r,flag=0;
      textcolor(14);
      FILE*p,*q;
      p=fopen("bank.txt","rb");
      q=fopen("temp.new","wb");
      cprintf(" enter account to be modify: ");
      scanf("%d",&r);
      while(fread(&b,sizeof(b),1,p))
      {
	if (r==b.acc)
	{
	   cprintf("\n name, account no., type and balance: ");
	   scanf("%s%d%c%d",&b.name,&b.acc,&b.type,&b.ofbal);
	   flag=1;
	}
      fwrite(&b,sizeof(b),1,q);
      }
      fclose(p);
      fclose(q);
      remove("bank.txt");
      rename("temp.new","bank.txt");
      if (flag==0)
	  cprintf("account not found");
      else
	  cprintf("record modifyied");
      getch();
  }
// report of account---------------------------------------------------------------------------
void report()
{
      struct cashbook b;
      int i,r,flag=0;
      char n[50];
      textcolor(14);
      FILE *p;
      p=fopen("cashbook.txt","rb");
      printf("enter account no.to be found report: ");
      scanf("%d",&r);
      printf("\nAccount No\tTrans type \t Amount \t Balance Amt");
      while(fread(&b,sizeof(b),1,p))
      {
	if (r==b.acno)
	{
	    printf("\n%d\t%c\t%d\t%d",b.acno,b.transtype,b.tamt,b.bamt);
	    flag=1;
	}
      }
      if(flag==0)
	 cprintf("account no not found ");
      fclose(p);
      getch();
}

// deposit in account-------------------------------------------------------------
  void deposit()
  {
      struct bank b;
      struct cashbook cb;
      int r,amt,flag=0;
      textcolor(14);
      FILE *p,*t,*s;
      p=fopen("bank.txt","rb");
      t=fopen("temp.new","wb");
      cprintf(" enter account no to be found: ");
      scanf("%d",&r);
      while(fread(&b,sizeof(b),1,p))
      {
	if (r==b.acc)
	{
	    cprintf(" enter deposit amount: ");
	    scanf("%d",&amt);
	    b.ofbal= b.ofbal+amt;
	    flag=1;
	    cb.acno=b.acc;
	    cb.transtype='D';
	    cb.tamt=amt;
	    cb.bamt=b.ofbal;
	    s=fopen("cashbook.txt","ab");
	    fwrite(&cb,sizeof(cb),1,s);
	    fclose(s);

	}
	fwrite(&b,sizeof(b),1,t);
      }
      fclose(p);
      fclose(t);
      remove("bank.txt");
      rename("temp.new","bank.txt");
      if (flag==0)
	  cprintf("account not found");
      else
	  cprintf("amount deposited in the account");
      getch();
  }
// withdrawl of amount----------------------------------------------------------------------------
  void withdrawl()
  {
      struct bank b;
      struct cashbook cb;
      int i,r,amt,flag=0;
      textcolor(14);
      FILE *p,*w,*s;
      p=fopen("bank.txt","rb");
      cprintf(" enter account to be found: ");
      scanf("%d",&r);
      while(fread(&b,sizeof(b),1,p))
      {
	if (r==b.acc)
	{
	    cprintf(" enter withdrawl amount: ");
	    scanf("%d",&amt);
	    flag=1;
	    if ( amt > b.ofbal )
	    {
		cprintf("balance amt only is %d",b.ofbal);
		getch();
		return;
	    }
	}
      }
      fclose(p);
      if(flag==1)
      {
	    p=fopen("bank.txt","rb");
	    w=fopen("minus.new","wb");
	    while(fread(&b,sizeof(b),1,p))
	    {
		if (r==b.acc)
		{
			b.ofbal=b.ofbal-amt;
			cb.acno=b.acc;
			cb.transtype='W';
			cb.tamt=amt;
			cb.bamt=b.ofbal;
			s=fopen("cashbook.txt","ab");
			fwrite(&cb,sizeof(cb),1,s);
			fclose(s);
		 }
		fwrite(&b,sizeof(b),1,w);
	    }
	    fclose(p);
	    fclose(w);
	    remove("bank.txt");
	    rename("minus.new","bank.txt");

	    cprintf("amount is withdrawl in the account");
      }
      else
	     cprintf("account no not exists");

      getch();
   }

// exit code--------------------------------------------------------------
  void exitcode()
  {
     textcolor(7);
     box();
     gotoxy(30,10);
     cprintf("THANK YOU FOR VISITING");
     delay(1000);
     exit(0);
  }
// welcome code ------------------------------------------------------------
  void welcome()
  {
     clrscr();
     box();
     textcolor(9);
     gotoxy(30,10);
     cprintf("PROJECT MADE BY: ");
     gotoxy(30,12);
     cprintf("ANUSHKA JAIN");
     textcolor(2);
     gotoxy(30,14);
     cprintf("LOADING....");
     delay(3000);
  }
// password code------------------------------------------------------------
  void password()
  {
      int ch[3];
      clrscr();
      box();
      textcolor(15);
      textbackground(14);
      gotoxy(30,10);
      cprintf("enter password: ");
      gotoxy(48,10);
      ch[0]=getch();
      printf("*");
      ch[1]=getch();
      printf("*");
      ch[2]=getch();
      printf("*");
      if ( ch[0]=='1' && ch[1]=='2' && ch[2]=='3' )
      {
	  textcolor(2);
	  textbackground(0);
	  gotoxy(30,12);
	  cprintf("CORRECT PASSWORD ");
	  gotoxy(30,14);
	  cprintf("LOADING.... ");
	  delay(1000);
	  welcome();
      }
      else
      {
	 textcolor(4);
	 textbackground(0);
	 gotoxy(30,12);
	 cprintf("INCORRECT PASSWORD ");
	 delay(1000);
	 exit(1);
      }
  }
// main menu -------------------------------------------------------------------------------
void main()
{
   int ch ;
   password();
	clrscr();
	textbackground(0);
	do
	{
	printf("\n------------------------------ MENU FOR BANK---------------------------------");
	printf("\n 1) add");
	printf("\n 2) display all");
	printf("\n 3) search by account number");
	printf("\n 4) delete account");
	printf("\n 5) modify");
	printf("\n 6) deposit");
	printf("\n 7) withdrawl");
	printf("\n 8) report");
	printf("\n 9) exit");

	printf("\n------------------------------------------------------------------------");
	printf("\n enter choice:  ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1 :
			add();
			break;
		case 2 :
			displayall();
			break;
		case 3 :
			searchacc();
			break;
		case 4 :
			deleterecord();
			break;
		case 5 :
			modify();
			break;
		case 6 :
			deposit();
			break;
		case 7 :
			withdrawl();
			break;
		case 8 :
			report();
			break;
		case 9 :
			clrscr();
			exitcode();
			break;
		default :
			printf("invalid choice");
			break;
   }
       }while(ch!=9);
}
// the end-----------------------------------------------------------------
