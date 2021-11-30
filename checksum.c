#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int binary_addition(int binary1,int binary2,int k)
{
         int i = 0, remainder = 0, sum[20],count=0,m;
     while (binary1 != 0 || binary2 != 0)

    {

        sum[i++] =(binary1 % 10 + binary2 % 10 + remainder) % 2;

        remainder =(binary1 % 10 + binary2 % 10 + remainder) / 2;

        binary1 = binary1 / 10;

        binary2 = binary2 / 10;

    }

    if (remainder != 0)

        sum[i++] = remainder;

    --i;   


    while (i >= 0)
  {
        //printf("%d", sum[i--]);
        count++;
        i--;
  }
   if(count>k)
   {  
      
      m=0;
      for(i=count-2;i>=0;i--)
     {
      m = 10 * m + sum[i];
      //printf("%d",sum[i]);
     }
     //printf("m is %d",m);
     binary_addition(m,1,k);
   }
  else
  { 
        m=0;
        for(i=count-1;i>=0;i--)
  {
       // printf("%d", sum[i]);
        m = 10 * m + sum[i];
        //count++;
  } 
       return m;
   }
}
char *Receiver(char data[],int len1,int sum1)
{
 int slot,i,j,k,l,sum=0,len,num,result,checksum;
 char temp[100]={};
 char str1[100]={};
 char str2[100]={};
 char ans[100]={};
  slot=(strlen(data)-len1)/4;
 for(j=0;j<(strlen(data)-len1);j++)
  {
    k=0;
    for(i=j;i<j+slot;i++)
    {
       temp[k]=data[i];
       k++;
    }
    if(strlen(temp)==slot)
    {
      num=atoi (temp);
      sum=binary_addition(num,sum,slot);  // send both temp and sum as integers
    }
    else
     {
       len=strlen(temp);
       for(l=0;l<slot-len;l++)
        {
           str1[l]='0';
        }
       strcat(str1,temp);
       num=atoi (str1);
       //printf("temp is %d\n",num);
       sum=binary_addition(num,sum,slot); // send both temp and sum as integers
     }
    j=i-1;
  }
    sprintf(str1, "%d", sum);
    if(strlen(str1)<slot)
     {
       // sprintf(str1, "%d", sum);
        len=strlen(str1);
        for(l=0;l<slot-len;l++)
        {
           str2[l]='0';
        }
       strcat(str2,str1);
       k=0;
       for(i=(strlen(data)-len1);i<strlen(data);i++)
       {
         temp[k]=data[i];
         k++;
       }
      checksum=atoi (temp);
      sum=atoi (str2);
      result=binary_addition(sum1,checksum,slot);
      sprintf (ans, "%d", result);
       i=0;
      while(ans[i]!='\0')
      {
        if(ans[i]=='0')
        ans[i]='1';
        else
        ans[i]='0';
        i++;
      }
      printf("Result at the receiver end is %s\n",ans);
     }
     else
    {
       sprintf(str1, "%d", sum);
       k=0;
       for(i=(strlen(data)-len1);i<strlen(data);i++)
       {
         temp[k]=data[i];
         k++;
       }
      checksum=atoi (temp);
      sum=atoi (str1);
      result=binary_addition(sum1,checksum,slot);
      sprintf (ans, "%d", result);
      i=0;
      while(ans[i]!='\0')
      {
        if(ans[i]=='0')
        ans[i]='1';
        else
        ans[i]='0';
        i++;
      }
     printf("Result at the receiver end is %s\n",ans);
    }
}
int main()
{
 int slot,i,j,k,l,sum=0,len,num,len1;
 char data[100]={};
 char temp[100]={};
 char str1[100]={};
 char str2[100]={};
 printf("Enter the data\n");
 scanf("%s",data);
 slot=strlen(data)/4;
 for(j=0;j<strlen(data);j++)
  {
    k=0;
    for(i=j;i<j+slot;i++)
    {
       temp[k]=data[i];
       k++;
    }
    if(strlen(temp)==slot)
    {
      num=atoi (temp);
      sum=binary_addition(num,sum,slot);  // send both temp and sum as integers
     //printf("temp is %d\n",num);
    }
    else
     {
       len=strlen(temp);
       for(l=0;l<slot-len;l++)
        {
           str1[l]='0';
        }
       strcat(str1,temp);
       num=atoi (str1);
       //printf("temp is %d\n",num);
       sum=binary_addition(num,sum,slot); // send both temp and sum as integers
     }
    j=i-1;
  }
    sprintf(str1, "%d", sum);
    if(strlen(str1)<slot)
     {
        len=strlen(str1);
        for(l=0;l<slot-len;l++)
        {
           str2[l]='0';
        }
       strcat(str2,str1);
       i=0;
       while(str2[i]!='\0')
       {
          if(str2[i]=='0')
          str2[i]='1';
          else
          str2[i]='0';
         i++;
       }
       printf("CheckSum at the sender end is %s\n",str2);
       strcat(data,str2);
       len1=strlen(str2);
       Receiver(data,len1,sum);
     }
     else
    {
     i=0;
     sprintf(str1, "%d", sum);
     while(str1[i]!='\0')
       {
          if(str1[i]=='0')
          str1[i]='1';
          else
          str1[i]='0';
         i++;
       }
     printf("CheckSum at the sender end is %s\n",str1);
     strcat(data,str1);
     len1=strlen(str1);
     Receiver(data,len1,sum);
    }

    
}
