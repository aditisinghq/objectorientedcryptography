#include"turing.h"
int main()
{
   RSA r1, r2;
   int y=1;
   
   int d;
   while(y==1)
   {
     int x=1;
     cout<<"\n\n1.\tENCODE\n2.\tDECODE WITH PASSWORD\n3.\tDECODE WITH CODE AND KEY\n4.\tEXIT"<<endl;
     int ch;
     cout<<"enter choice: ";
     cin>>ch;
     int n=0;//1 if password was correct
     switch(ch)
     {
        
        case 1:
        r1.encode();
        break;
        
        case 2:
        //when code is stored in previous loop
        cout<<"enter key: ";
        cin>>d;
        r1.decode(d);
        break;
        
        case 3:
        cout<<"enter the private key ( d and n respectively):\n";
        cin>>d;
        cin>>n;
        r2.decode(d,n);
        break;
        
        case 4:
        default:
        y=0;
        exit(0);
      }
    }
}
