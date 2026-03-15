#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
using namespace std;
char mapkey[] = {
     'M','O','N','A','R',
     'C','H','Y','B','D',
     'E','F','G','I','K',
     'L','P','Q','S','T',
     'U','V','W','X','Z'
};
int issamerow(int a,int b){ // hàm kiểm tra 2 phần tử có cùng hàng hay không
    if (a/5 == b/5) return 1;
    else return 0;
} 
void cryptorow(int *c , int *d){ // mã hóa 2 phần tử cùng hàng
    if(*c ==*d){
      *d =23;
        return; 
    }
    if(*c%5 ==4){
        *c-=4;
        *d+=1;
        return;
    }
    if(*d%5 ==4){
        *c+=1;
        *d-=4;
        return;
    }
    else {
        *c+=1;
        *d+=1;
        return;
    }
}
int issamecol(int a,int b){ // hàm kiểm tra 2 phần tử có cùng cột hay không
    if (a%5 == b%5) return 1;
    else return 0;
}
void cryptocol(int *c , int *d){//mã hóa 2 phần tử cùng cột
    if(*c==*d){
        *d =23;
        return;
    }
    if(*c/5 ==4){
        *c-=20;
        *d+=5;
        return;
    }
    if(*d/5 ==4){
        *c+=5;
        *d-=20;
        return;
    }
    else {
        *c+=5;
        *d+=5;
        return;
    }
}
void cryptorectangle(int *c,int *d){
    int m=*c;
    *c=(*c/5)*5 +*d%5;
    *d=(*d/5)*5 +m%5;
}

void decryptrow(int *c , int *d){ // giải mã 2 phần tử cùng hàng (dịch trái 1)
    if(*c%5 ==0){
        *c+=4;
        *d-=1;
        return;
    }
    if(*d%5 ==0){
        *c-=1;
        *d+=4;
        return;
    }
    else {
        *c-=1;
        *d-=1;
        return;
    }
}

void decryptcol(int *c , int *d){//giải mã 2 phần tử cùng cột (dịch lên 1)
    if(*c/5 ==0){
        *c+=20;
        *d-=5;
        return;
    }
    if(*d/5 ==0){
        *c-=5;
        *d+=20;
        return;
    }
    else {
        *c-=5;
        *d-=5;
        return;
    }
}

char toupper(char c){// hàm nâng hết chữ thường thành in hoa
    if(c>='a' && c<='z') return (c-32);
    else return c;
}
void cryptographic(string s){
int k=0;
char*index = (char*)malloc(sizeof(char)*s.length());

for(int i = 0 ; i < s.length() ; i++){
    index[i]=toupper(s[i]);
}

int *tamthoi = (int*)malloc(sizeof(int)*s.length());//lưu vị trí của các phần tử trong mapkey
int *thaydoi = (int*)malloc(sizeof(int)*s.length());//lưu vị trí sau khi đã mã hóa
for(int i=0 ; i< s.length();i++){ // tìm vị trí của phần tử trong mapkey
    if(index[i] ==' '){
        tamthoi[i]=-1;
        continue;
    }
    if(index[i] == 'J') {
        tamthoi[i]=13;
        continue;
    }
    for(int j=0 ; j<25;j++){
        if(index[i]==mapkey[j]){
            tamthoi[i]=j;
        }   
    }
}

for(int i=0;i<s.length();i++){
    if(tamthoi[i]>=0){
        thaydoi[k]=tamthoi[i];
        ++k;
    }
}
//cout<<k;
for(int i=0 ; i<k;i++){
    if(i+1 >=k )
        break;
    if(issamerow(thaydoi[i],thaydoi[i+1])){
        cryptorow(&thaydoi[i],&thaydoi[i+1]);
        //cout<<'a';
        ++i;
    }
    else if(issamecol(thaydoi[i],thaydoi[i+1])){
        cryptocol(&thaydoi[i],&thaydoi[i+1]);
        //cout<<'b';
        ++i;
    }
    
    else{
        cryptorectangle(&thaydoi[i],&thaydoi[i+1]);
        //cout<<'c';
        ++i;
    }
}
k=0;
for(int i=0;i<s.length();i++){
    if(tamthoi[i]>=0){
        tamthoi[i]=thaydoi[k];
        ++k;
    }
}
for(int i=0;i<s.length();i++){
    if(tamthoi[i]>=0){
        cout<<mapkey[tamthoi[i]];
    }
    else cout<<s[i];
}
free (index);
free (tamthoi);
free (thaydoi);
}
void decryptographic(string s){
    int k=0;
    char*index = (char*)malloc(sizeof(char)*s.length());

    for(int i = 0 ; i < s.length() ; i++){
        index[i]=toupper(s[i]);
    }

    int *tamthoi = (int*)malloc(sizeof(int)*s.length());//lưu vị trí của các phần tử trong mapkey
    int *thaydoi = (int*)malloc(sizeof(int)*s.length());//lưu vị trí sau khi đã giải mã
    for(int i=0 ; i< s.length();i++){ // tìm vị trí của phần tử trong mapkey
        if(index[i] ==' '){
            tamthoi[i]=-1;
            continue;
        }
        if(index[i] == 'J') {
            tamthoi[i]=13;
            continue;
        }
        for(int j=0 ; j<25;j++){
            if(index[i]==mapkey[j]){
                tamthoi[i]=j;
            }
        }
    }

    for(int i=0;i<s.length();i++){
        if(tamthoi[i]>=0){
            thaydoi[k]=tamthoi[i];
            ++k;
        }
    }

    for(int i=0 ; i<k;i++){
        if(i+1 >=k )
            break;
        if(issamerow(thaydoi[i],thaydoi[i+1])){
            decryptrow(&thaydoi[i],&thaydoi[i+1]);
            ++i;
        }
        else if(issamecol(thaydoi[i],thaydoi[i+1])){
            decryptcol(&thaydoi[i],&thaydoi[i+1]);
            ++i;
        }
        else{
            cryptorectangle(&thaydoi[i],&thaydoi[i+1]);
            ++i;
        }
    }
    k=0;
    for(int i=0;i<s.length();i++){
        if(tamthoi[i]>=0){
            tamthoi[i]=thaydoi[k];
            ++k;
        }
    }
    for(int i=0;i<s.length();i++){
        if(tamthoi[i]>=0){
            cout<<mapkey[tamthoi[i]];
        }
        else cout<<s[i];
    }
    free (index);
    free (tamthoi);
    free (thaydoi);
}
int main(){
system("cls");
string s,s1;
printf("Nhap chuoi can ma hoa: ");
getline(cin,s);
cryptographic(s);
cout<<"\nnhap chuoi can giai ma:";
getline(cin,s1);
decryptographic(s1);
    return 0;
}

