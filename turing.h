#ifndef turing
#define turing

#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cmath>
#include<cstring>
#include<iomanip>
#include<cctype>
using namespace std;

class alphaci{
                             protected:
                               char text[173];
                               char code[173];
                               int set;
                               
                             public:
                                void enter(int n)
                                {
                        
                                    cout<<"enter the ";
                                    if(n==1)
                                    {
                                      cout<<"text: ";
                                      cin.ignore();
                                      cin.getline(text,173);
                           
                                    }
                                    else if(n==2)
                                    {
                                      cout<<"code: ";
                                      cin.ignore();
                                      cin.getline(code, 173);
                                    }
                                }
                                
                                void display(int n)
                                {
   
                                  if(n==1)
                                    cout<<"ENCRYPTED: "<<code<<endl;
                                  else if(n==2)
                                    cout<<"DECRYPTED: "<<text<<endl;
                                }
                                
                                  int ifset()
                                  {
                                    return set;
                                  }
                      
};

class dateshift: public alphaci
{
                   int key[8];
                   static int c;
                   int limit;
                   
                   public:
                   
                     dateshift()
                     {
                        for(int i=0; i<8; ++i)
                          key[i]=0;
                     }
                     void copy(const dateshift &d)
                     {
                        for(int i=0; i<8; ++i)
                          this->key[i]=d.key[i];
                        strcpy(this->text, d.text);
                        strcpy(this->code, d.code);
                        this->limit=d.limit;
                        this->set=0;
                     }
                     friend dateshift enterdate();  
                      int check(dateshift &);
                      void encode();
                      void decode(dateshift &);
                      void decode(int&, dateshift &);
                      
                    
                      
};

int dateshift::c=0;
dateshift enterdate()
{
    dateshift t;
    char date[10];
    cout<<"enter date: eg 02/04/1976:\n";
    cin>>date;
    int j=0;
    
    for(int i=0; i<10; ++i)
    {
       if(i!=2 && i!=5)
          t.key[j++]=date[i]-48;
    }     
    return t;
}



int dateshift::check(dateshift & d){

                         if(c++<limit)
                         {
                            for(int i=0; i<8; ++i)
                            {
                               if(this->key[i]!=d.key[i])
                               {
                                  cout<<"INCORRECT PASSWORD! TRY AGAIN ("<<limit-c<<" tries left)"<<endl;
                                  return -1;
                               }
                             }
                             return 1;
                          }
                          else
                           cout<<"TRY LIMIT EXCEEDED!  DATA LOCKED"<<endl;
                           return -1;
                        }
                        
void dateshift::encode()
{
   dateshift t;
   cout<<"set password date:"<<endl;
   t.copy(enterdate());
   cout<<"enter the limit for tries: ";
   cin>>t.limit;
   t.enter(1);
   int j=0;
   for(int i=0; i<strlen(t.text); ++i)
   {
      char c=tolower(t.text[i]);
      if(c>=97 && c<=122)
      { 
        int l=c+t.key[j++];
        if(j==8)
          j=0;
        if(l>122)
        {
           c=97+(l-123);
           t.code[i]=c;
        }
        else
          t.code[i]=l;
      } 
      else
        t.code[i]=t.text[i];
      
      
    }
    this->copy(t);
    this->set=1;
    display(1);
}

void dateshift::decode(dateshift &d)
{
   //with code, without password(with key)
   d.copy(enterdate());
   d.enter(2);
   
   //decoding process
   int j=0;
   for(int i=0; i<strlen(d.code); ++i)
   {
      if(d.code[i]>=97 && d.code[i]<=122)
      {
        int l=d.code[i]-d.key[j++];
        if(j==8)
          j=0;
        if(l<97)
           d.text[i]=123-(97-l);
        else
           d.text[i]=l;
      }
      else
        d.text[i]=d.code[i];
    }
   
   d.display(1);
   d.display(2);
}

void dateshift::decode(int &n, dateshift &d)
{
   n=check(d);
   if(n==1)
   {
       cout<<"DATA UNLOCKED! ";
       display(2);
   }
}

class vigenere: public alphaci
{
                 char vt[26][26];
                 char key[10];
                 static int c;
                 int limit;
                 
                 public:
                      vigenere(){
                                   int c;
                                   for(int i=0; i<26; ++i)
                                   {
                                      for(int j=0; j<26; ++j)
                                      {
                                         c=97+i+j;
                                         if(c>122)
                                           c=(c-123)+97;
                                         vt[i][j]=c;
                                         
                                       }
                                       
                                    }
                                  strcpy(text, "");
                                  strcpy(code, "");
                                  strcpy(key, "");
                                   set=0;
                                   }
                     int check(vigenere &);
                     void copy(const vigenere &v)
                     {
                        strcpy(this->key, v.key);
                        strcpy(this->text, v.text);
                        strcpy(this->code, v.code);
                        this->limit=v.limit;
                        this->set=0;
                     }
                                                
                     void encode();
                     void decode(int &, vigenere &);
                     void decode(vigenere &);
                   
                     friend vigenere enterkey();
                     void printvt()
                     {
                        for(int i=0; i<25; i++)
                        {
                          for(int j=0; j<25; ++j)
                            cout<<vt[i][j]<<" ";
                          cout<<"\n";
                         }
                     }
};
int vigenere::c=0;

                        
vigenere enterkey()
{
   vigenere v;
   cout<<"enter the password: (alphabetical <10) ";
   cin>>v.key;
   return v;
}

void vigenere::encode()
{
    vigenere v;//this should wipe the previous stored
    v.copy(enterkey());
    cout<<"enter the limit for tries: ";
    cin>>v.limit;
    v.enter(1);
    int j=0;
    int i;
    for( i=0; i<strlen(v.text); ++i)
    {
        if(v.text[i]>=97 && v.text[i]<=122)
        {
           v.code[i]=97+((v.text[i]-97+v.key[j++]-97)%26);
           if(j==strlen(v.key))
              j=0;
        }
        else
          v.code[i]=v.text[i];
    }
    v.code[i]='\0';
    this->copy(v);
    this->set=1;
    display(1);
}

int vigenere::check(vigenere &v)
{
                        if(c++<limit)
                         {
                            if(strlen(this->key)!=strlen(v.key)) 
                            {
                               cout<<"INCORRECT PASSWORD! TRY AGAIN ("<<limit-c<<" tries left)"<<endl;
                                  return -1;
                            }
                            else
                            {
                               for(int i=0; i<strlen(v.key); ++i)
                               {
                                  if(this->key[i]!=v.key[i])
                                  {
                                    cout<<"INCORRECT PASSWORD! TRY AGAIN ("<<limit-c<<" tries left)"<<endl;
                                    return -1;
                                  }
                               }
                               return 1;
                          }
                         }
                          else
                           cout<<"TRY LIMIT EXCEEDED!  DATA LOCKED"<<endl;
                           return -1;
}

void vigenere::decode(int &n, vigenere &v)
{
   n=check(v);
   if(n==1)
   {
     cout<<"DATA UNLOCKED!"<<endl;
     display(2);
   }
}

void vigenere::decode(vigenere &v)
{
   v.copy(enterkey());
   v.enter(2);
   //making sure the object has been cleared
   for(int i=0; i<strlen(v.text); ++i)
      v.text[i]='\0';
   //decrypting process
   int j=0;
   int i;
   for(i=0; i<strlen(v.code); ++i)
   {
      if(v.code[i]>=97 && v.code[i]<=122)
      {
        v.text[i]=97+(((v.code[i]-97)-(v.key[j++]-97)+26)%26);
        if(j==strlen(v.key))
          j=0;
      }
      else
        v.text[i]=v.code[i];
      
   }
   v.text[i]='\0';
   v.display(1);
   v.display(2);
}
class RSA{
              int a[100];
              int c[100];
              int l;
              int p, q;
              int n, phi, d, e;
              public:
                     RSA()
                     {
                       setpq();
                       //if user wish to enter pq himself, the programmer can call setpq(int, int) before using encode
                     }
                     void enter(int n, int x)
                     {
                        
                        cout<<"enter the values:\n";
                        if(x==1)
                        {
                          for(int i=0; i<n; ++i)
                             cin>>a[i];
                        }
                        else if(x==2)
                        {
                           for(int i=0; i<n; ++i)
                              cin>>c[i];
                        }
                     }
                     void display(int n, int x)
                     {
                        if(x==1)
                        {
                          for(int i=0; i<n; ++i)
                             cout<<a[i]<<endl;
                        }
                        else if(x==2)
                        {
                           for(int i=0; i<n; ++i)
                              cout<<c[i]<<endl;
                        }
                     }
                     void setpq()
                     {
                       int i,j, x, y;
                       srand(time(0));
                       do
                       {
                         
                         x=rand()%(1000+1-2)+2;
                         y=rand()%(1000+1-2)+2;
                 
                         if(x%2==0 || y%2==0)
                           continue;
                         for(i=3; i<=sqrt(x); i+=2)
                         {
                            if(x%i==0)
                                break;
                             
                         }
                         for(j=3; j<=sqrt(y); j+=2)
                         {
                            if(y%j==0)
                              break;
                         }
                         if(i>sqrt(x) && j>sqrt(y))
                         {
                            p=x;
                            q=y;
                            break;
                         }
                         else
                           continue;
                       }while(1);
                      }
                      void setpq(int p, int q)//in case of user entered
                      {
                         this->p=p;
                         this->q=q;
                      }
                      void generate()
                      {
                         n=p*q;
                         phi=(p-1)*(q-1);
                         for(int i=2; i<phi; ++i)
                         {
                           if (gcd(i,phi)==1)
                           {
                              e=i;
                              break;
                           }
                         }
                      }
                      int gcd(int a, int b)
                      {
                        if(b==0)
                          return a;
                        else
                          return gcd(b, a%b);
                      } 
                     int exponentMod(int A, int B, int C)  
                     {  
                          // Base cases  
                          if (A == 0)  
                             return 0;  
                          if (B == 0)  
                             return 1;  
  
                          // If B is even  
                          long y;  
                          if (B % 2 == 0) 
                          {  
                            y = exponentMod(A, B / 2, C);  
                            y = (y * y) % C;  
                          }  
  
                          // If B is odd  
                          else 
                          {  
                                y = A % C;  
                                y = (y * exponentMod(A, B - 1, C) % C) % C;  
                           }  
  
                         return (int)((y + C) % C);  
                    }  
                     void generateprivatekey()
                     {
                        int x;
                        for(int k=1; ; ++k)//possibly infinite loop
                        {
                          x=1+(k*phi);
                          if(x%e==0)
                          {
                             d=x/e;
                             break;
                          }
                       }
                     }
                     void encode()
                     {
                        cout<<"Enter the number of values you wish to encode: ";
                        cin>>l;
                        enter(l,1);
                        generate();
                        generateprivatekey();
                        int f=0;
                        
                        for(int i=0; i<l ; ++i)
                        {
                            c[i]=exponentMod(a[i], e, n);
                        }
                        cout<<"ENCRYPTED:\n";
                        display(l, 2);
                        cout<<"PUBLIC KEY: "<<"( "<<e<<", "<<n<<")"<<endl;
                        cout<<"PRIVATE KEY: "<<"( "<<d<<" (keep confidential!), "<<n<<" )"<<endl;
                     }
                     
                     void decode(int d1)//for decoding with only key
                     {
                        if(d1==d)
                        {
                           cout<<"CORRECT KEY! DATA UNLOCKED."<<endl;
                           display(l,1);
                        }
                        else
                        {
                           cout<<"INCORRECT KEY! TRY AGIAN.";
                        }
                     }
                     void decode(int d1, int n1)//plugin decode
                     {
                         cout<<"enter number of values in cipher array: ";
                         cin>>l;
                         enter(l,2);
                         for(int i=0; i<l; ++i)
                         {
                            a[i]=exponentMod(c[i],d1,n1);
                         }
                         cout<<"DECRYPTED:\n";
                         display(l,1);
                    }
};

#endif
