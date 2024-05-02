#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#define eps 1e-3

void read_file(char filename[], int &n, float A[][100], int &check);
void input_file(char a[], float A[][100], int &n);
void change(float A[][100], float B[], int n);
void print_POLYNOMIAL(float B[], int n);
float Fx(float B[], int n, float x0);
void enter_input(float &a, float &b, float B[], int n);
float solve(float B[], float a, float b, int n);
void information();
void result(char a[]);
int menu_input(int &com);
void mtA(float A[][100], int &n);
void setcolor(int backgound_color, int text_color);

int main()
{
    int n,com;
    float a, b,c;
    char name[100], re[100], other[1],newP[1];
    float A[100][100];
    float B[100];

    information();//Introduce the topic and related information
   
    do{
       menu_input(com);
       if(com==1){
        setcolor(0,3);
        printf("\tMoi ban nhap ma tran A\n");
        printf("\tNhap buc cua ma tran: ");
        setcolor(0,8);
        scanf("%d", &n);
        mtA(A, n);
       }
       else if(com==2){
        (getchar()) != '\n';         
        input_file(name,A,n);
       }
       
        setcolor(0,15);
        change(A,B,n);
        print_POLYNOMIAL(B,n);
         while (1){
            enter_input(a,b,B,n);
            c=solve(B,a,b,n);
            setcolor(0,15);
            printf("\n    Bang gia tri thuc hien phuong phap chia doi\n");
            setcolor(0,3);
            printf("\nNgiem cua phuong trinh la:  %.3f", c);
            printf("\n\nBan co muon nhap khoang nghiem khac khong (y/n)? ");
            setcolor(0,8);
            scanf("%s",other);
            if (other[0]!='y') break;
        }
        setcolor(0,3);
        printf("\n\nBan co muon tim nghiem voi da thuc khac khong(Neu muon nhap lai thi chon c, con khong muon thi nhap phim bat ki)? ");
        setcolor(0,8);
        scanf("%s", newP);
    }while(newP[0]=='c');
    }

void setcolor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void information()
{
    int i;
    setcolor(0, 3);
    printf("\n%9c", 201);
    for (i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c", 187);
    printf("\n        %c %86c", 4, 4);
    printf("\n        %c                             DO AN LAP TRINH TINH TOAN                                %c", 4, 4);
    printf("\n        %c                   DE TAI: Tim nghiem gan dung bang phuong phap chia doi              %c", 4, 4);
    printf("\n        %c %86c", 4, 4);
    printf("\n        %c       Sinh vien thuc hien:                       Giao vien huong dan:                %c", 4, 4);
    printf("\n        %c           %c Le Ngoc Lam Na                            %c Do Thi Tuyet Hoa             %c", 4, 45, 45, 4);
    printf("\n        %c           %c Le Xuan Tung Son  %56c", 4, 45, 4);
    printf("\n        %c %86c", 4, 4);
    printf("\n        %c", 200);
    for (i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c\n", 188);
}

void read_file(char filename[], int &n, float A[][100], int &check)
{   setcolor(0,3);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        check = 0;        
        return;
    }
    fscanf(file, "%d", &n); // read array size
    char a;
    int s = 0, count = 0;

    // check size file
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(file, "%f", &A[i][j]) == 1)
            { // save data into array A
                s++;
                if ((a = fgetc(file)) != '\n')
                {
                    if (a != EOF)
                        count++;
                }
                else
                {
                    break;
                }
            }
        }
        if (count != (n - 1))
        {
            check = 2;
            fclose(file);
            return;
        }
        count = 0;
    }
    if (s != n * n)
    {
        check = 2;
        fclose(file);
        return;
    }
    check = 1;
    fclose;
}

void input_file(char a[], float A[][100], int &n)
{   
    setcolor(0,3);
    int check;
    do
    {
        printf("Nhap ten file du lieu: ");
         setcolor(0, 8);
        fgets(a, 100, stdin); // input name file to array a
        a[strcspn(a, "\n")] = 0;
        setcolor(0,3);
        read_file(a, n, A, check);
        if (check == 0)
        {
            printf("File %s khong ton tai\n", a);
        }
        else if (check == 2)
        {
            printf("File %s bi loi \n", a);
        }
        else
        {
            printf("Doc file thanh cong\n");
        }
    } while (check == 0 || check == 2);
}

void change(float A[][100], float B[], int n)
{ // data analysis
    B[0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i] += A[j][i];
        }
    }
    float max = B[0];
    for (int k = 0; k < n; k++)
    {
        if (B[k] > max)
        {
            max = B[k];
        }
    }
    B[n] = max;
}

void print_POLYNOMIAL(float B[], int n)
{ // print Polynomial
    printf("Da thuc sau khi su ly du lieu:  \n ");
    printf("F(x)= ");
    int m = 0;
    for (int i = 0; i <= n; i++)
    {
        if (B[i] == 0)
        {
            m++;
            continue;
        }
        if (B[i] < 0)
        {
            if (m - i == 0)
            {
                printf("-");
            }
            else
                printf(" - ");
        }
        else
        {
            if (m - i != 0)
                printf(" + ");
        }
        if (abs(B[i]) != 1)
        {
            printf("%.2f", B[i]);
        }

        if (i != n)
        {
            printf("x");
        }
        if (i < n)
        {
            printf("^%d", n - i);
        }
    }
    printf("\n");
}

float Fx(float B[], int n, float x0)
{ // value Fx at x0
    float Fx = B[0];
    for (int i = 1; i <= n; i++)
    {
        Fx = Fx * x0 + B[i];
    }
    return Fx;
}

void enter_input(float &a, float &b, float B[], int n)//input a,b
{
    float Fa, Fb;
    int i = 0;\

    do
    {   setcolor(0,3);
        i++;
        if (i > 1)
            printf("  ---Khoang nghiem khong phu hop---\n");
        printf("Nhap khoang nghiem(can duoi) a: ");
        setcolor(0,8);
        scanf("%f", &a);
        setcolor(0,3);
        printf("Nhap khoang nghiem(can tren) b: ");
        setcolor(0,8);
        scanf("%f", &b);
        Fa = Fx(B, n, a);
        Fb = Fx(B, n, b);

    } while (Fa * Fb > 0);
}

float solve(float B[], float a, float b, int n)//solve by bisection method

{   
    setcolor(0,5);
    printf("\n\t    a\t   b\t    c\t  f(c)\n");
    float c;
    setcolor(0,0);
    do
    {
        c = (a + b) / 2;
        printf("\t %0.3f\t %0.3f\t %0.3f\t  %0.3f\n", a, b, c, Fx(B, n, c));
        if (Fx(B, n, b) * Fx(B, n, c) > 0)
            b = c;
        else
            a = c;

    } while (abs(a - b) > eps && Fx(B, n, c) != 0);
    return c;
}

// void result(char a[])
// {
//     int check = 0;
//     FILE *file1 = NULL;
//     do
//     {
//         printf("Nhap file luu ket qua: ");
//         fgets(a, 100, stdin);
//         a[strcspn(a, "\n")] = 0;
//         file1 = fopen(a, "a");
//         if (file1 == NULL)
//         {
//             printf("Flie %s khong ton tai \n ", a);
//         }
//         check = 1;
//     } while (check == 0);
//     fclose(file1);
// }

int menu_input(int &com)
{
    setcolor(0, 14);
    printf("\n                                  %c   CHON CACH NHAP DU LIEU   %c\n", 16, 17);
    printf("\n                                        Nhap 1: Tu ban phim");
    printf("\n                                        Nhap 2: Tu file");
    printf("\n                                             -------\n");
    setcolor(0, 3);
    printf("\n          Nhap yeu cau: ");
     setcolor(0, 8);
    do
    {    setcolor(0, 8);
        scanf("%d", &com);
         setcolor(0, 3);
        if (com != 1 && com != 2)
            printf("\nMoi ban nhap lai: ");
    } while (com != 1 && com != 2);
    return com;
}

void mtA(float A[][100], int &n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {   setcolor(0,3);
            printf("A[%d][%d]=", i + 1, j + 1);
            setcolor(0,8);
            scanf("%f", &A[i][j]);
        }
    }
}