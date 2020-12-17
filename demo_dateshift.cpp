#include"turing.h"
int main()
{
   
   dateshift d,t;
   int y=1;
   
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
        d.encode();
        break;
        
        case 2:
        //when code is stored in previous loop
          if(d.ifset()==1)
          {
             t.copy(enterdate());
             d.decode(n, t);
          }
          else
          {
             cout<<"no data stored. encode new"; } 
        break;
        
        case 3:
        //when user has the code
        d.decode(t);
        break;
        
        case 4:
        default:
        y=0;
        exit(0);
      }
    }
}
        
