#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#define eps 1e-3

void read_file(char filename[], int *n, float A[][100], int *check);
int input_file(char a[], float A[][100], int *n);
void change(float A[][100], float B[], int n);
void print_POLYNOMIAL(float B[], int n);
float Fx(float B[], int n, float x0);
void enter_input(float *a, float *b, float B[], int n);
float solve(float B[], float a, float b, int n);
void information();
void result(char a[]);
int menu_input(int *com);
void array_A(float A[][100], int *n);
void setcolor(int backgound_color, int text_color);
void printarray(float A[][100], int n);
int out_to_file(float B[], int n, char s[], float a, float b, int c);
int guess_x(float a[], int n);
void wait_for_enter();
void clear_screen();
char Input_Choice(int n, int control);
int main()
{
    int n, k, com, stop = 1,choice;
    float a, b, c;
    char s[60];
    char name[100], re[100], other[1], newP[1];
    float A[100][100];
    float B[100];
    //khoi tao mang chua ten file
    int i;
    for ( i = 0; i < sizeof(s) / sizeof(s[0]); i++)
    {
        s[i] = '\0';
    }
    information();
    do
    {   
        //tag khi nhap du lieu tu file va chon thoat lua chon nhap file
        menu:
        do
        {
            menu_input(&com);
            
            // Lua chon lay du lieu tu ban phim
            if (com == 1)
            {
                clear_screen();
                setcolor(0, 3);
                printf("\tMoi ban nhap ma tran A.\n");
                printf("\tNhap bac cua ma tran: ");
                setcolor(0, 8);
                scanf("%d", &n);
                array_A(A, &n);
            }
            // Lua chon lay du lieu tu file
            if (com == 2)
            {
                (getchar()) != '\n';
                choice= input_file(name, A, &n);
                if(choice==1){
                     goto menu;
                }
                
            }
            // Lua chon du lieu co san
            int i,j;
            if (com == 3)
            {
                n = 3;
                for (i = 0; i < n; i++)
                {
                    for (j = 0; j < n; j++)
                    {
                        A[i][j] = i + j;
                    }
                }
            }
            //Ket thuc chuong trinh
            if (com == 7)
                return 0;
            // Khi thieu du lieu dau vao
            if (com != 1 && com != 2 && com != 3 && com != 5)
            {
                setcolor(0, 3);
                printf("\tDu lieu dau vao rong.\n");
                printf("\tMoi ban nhap du lieu de tiep tuc.\n");
            }
            //In du lieu ra man hinh
            if (com == 1 || com == 2 || com == 3)
            {
                setcolor(0, 3);
                clear_screen();
                printf("\n\tMa tran chua du lieu:\n");
                setcolor(0, 8);
                printarray(A, n);
                printf("\n");
                setcolor(0, 15);
                change(A, B, n);
                print_POLYNOMIAL(B, n);
                wait_for_enter();
            }
            //Da co the di toi thuc hien tim nghiem
            stop = 4;
            if (com != 2)
                getchar() != '\n';

        } while (com != 1 && com != 2 && com != 3);
        
        do
        {
            switch (menu_input(&com))
            {
            // Gia tri com :1;2;3 thi can xac nhan du lieu moi bang cach nhap 5
            case 1:
            case 2:
            case 3:
                printf("\tChon ");
                setcolor(0, 5);
                printf("5");
                setcolor(0, 3);
                printf(" de cung cap du lieu moi.");
                wait_for_enter();
                (getchar()) != '\n';
                clear_screen();
                break;
            // Thuc hien tim nghiem
            case 4:
                k = guess_x(B, n);
                if (!k)
                {
                    // Xac nhan da tim nghiem va co the luu ra file
                    if (stop == 4)
                        stop = 6;
                    wait_for_enter();
                    (getchar()) != '\n';
                    clear_screen();
                    break;//Khi du doan khong co nghiem thi k thuc hien tim nghiem nua
                }
                enter_input(&a, &b, B, n);
                clear_screen();
                c = solve(B, a, b, n);
                setcolor(0, 3);
                printf("\n\tNghiem cua phuong trinh la:  %.3f\n", c);
                if (stop == 4)
                    stop = 6;
                wait_for_enter();
                (getchar()) != '\n';
                clear_screen();
                break;
            // Xac nhan thuc hien cung du lieu moi
            case 5:
                clear_screen();
                // Quay ve nhan du lieu moi
                stop = 0;
                int i;
                for (i = 0; i < sizeof(s) / sizeof(s[0]); i++)
                {
                    s[i] = '\0';
                }
                break;
            // In ket qua ra file
            case 6:

                if (stop == 6)
                {
                    (getchar()) != '\n';
                    result(s);
                    stop = 5;
                }
                if (out_to_file(B, n, s, a, b, k))
                    printf("\tKet qua da luu tai file %s.\n", s);
                wait_for_enter();
                if (stop != 5)
                    getchar() != '\n';
                stop = 50;
                clear_screen();
                break;
            // Thoat khoi chuong trinh
            case 7:
                clear_screen();
                return 0;
                stop = 0;
                break;
            }

        } while (stop);

    } while (1);
    return 0;
}

// In ket qua ra file
int out_to_file(float B[], int n, char s[], float a, float b, int c)
{
    FILE *f = fopen(s, "a");
    if (f == NULL)
    {
        printf("\tChua co du lieu.");
        return 0;
    }

    if (!c)
    {
        fprintf(f, "\tPhuong trinh F(x)=0 khong co nghiem thuc.\n");
    }
    else
    {
        fprintf(f, "\tDa thuc:  ");
        fprintf(f, "F(x)= ");
        int m = 0,i;
        for ( i = 0; i <= n; i++)
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
                    fprintf(f, "-");
                }
                else
                    fprintf(f, " - ");
            }
            else
            {
                if (m - i != 0)
                    fprintf(f, " + ");
            }
            if (abs(B[i]) != 1)
            {
                fprintf(f, "%.2f", fabs(B[i]));
            }

            if (i != n)
            {
                fprintf(f, "x");
            }
            if (i < n)
            {
                fprintf(f, "^%d", n - i);
            }
        }

        fprintf(f, "\n");
        fprintf(f, "\tQua trinh thuc hien phuong phap chia doi trong khoang nghiem (%.2f;%.2f)\n", a, b);
        fprintf(f, "\n\t ");
        for (i = 0; i <= 85; i++)
            fprintf(f, "_");
        fprintf(f, "\n\t|                                                                                      |");
        fprintf(f, "\n\t*                     Bang gia tri thuc hien phuong phap chia doi                      *");
        fprintf(f, "\n\t*                                                                                      *");
        fprintf(f, "\n\t|         a          |          b         |          c          |          f(c)        |\n");
        fprintf(f, "\t*                                                                                      *");

        float c;
        do
        {
            c = (a + b) / 2;
            fprintf(f, "\n\t|");
            fprintf(f, "   %-4s%-7.4g%-6s|%-7s%-7.4g%-6s|%-8s%-7.4g%-6s|%-7s%-10.3g%-5s", " ", a, " ", " ", b, " ", " ", c, " ", " ", Fx(B, n, c), " ");
            fprintf(f, "|");

            if (Fx(B, n, b) * Fx(B, n, c) > 0)
                b = c;
            else
                a = c;

        } while (fabs(a - b) > eps && Fx(B, n, c) != 0);
        fprintf(f, "\n\t*                                                                                      *");
        fprintf(f, "\n\t*");
        for ( i = 0; i <= 85; i++)
            fprintf(f, "_");
        fprintf(f, "*\n");
        fprintf(f, "\n\tNghiem cua phuong trinh la:  %.3f\n\n", c);
    }
    fclose(f);
    return 1;
}

// Dieu chinh mau sac
void setcolor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

// Gioi thieu thong tin ve nhom va de tai
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
    printf("\n        %c                   NHOM: 9                                                            %c", 4, 4);
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

// Doc du lieu tu file va luu vao mang A
void read_file(char filename[], int *n, float A[][100], int *check)
{
    setcolor(0, 3);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        *check = 0;
        return;
    }
    fscanf(file, "%d", n); // Doc kich thuoc ma tran
    char a;
    int s = 0, count = 0;

    // Kiem tra tinh dung dan cua file
    int i,j;
    for ( i = 0; i < *n; i++)
    {
        for ( j = 0; j < *n; j++)
        {
            if (fscanf(file, "%f", &A[i][j]) == 1)
            {
                // Luu du lieu vao mang A
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
        // Kiem tra kich thuoc moi hang
        if (count != (*n - 1))
        {
            *check = 2;
            fclose(file);
            return;
        }
        count = 0;
    }
    // Kiem tra kich thuoc file
    if (s != (*n) * (*n))
    {
        *check = 2;
        fclose(file);
        return;
    }
    *check = 1;
    fclose;
}

// Nhap ten file chua ket qua
int input_file(char a[], float A[][100], int *n)
{
    setcolor(0, 3);
    int check;
    int i=0;
    do
    {   
        // Sau khi nhap sai qua 2 lan thi co the thoat
        if(i==2){
            char choice = Input_Choice(0,1);

                if (choice == 'r')
                {
                    system("cls");  
                    i=1;                  
                    goto out;
                }
                else{
                i=0;
                 getchar() != '\n';
                 }
        }
        printf("\tNhap ten file du lieu: ");
        setcolor(0, 8);
        fgets(a, 100, stdin);
        a[strcspn(a, "\n")] = 0;
        setcolor(0, 3);
        read_file(a, n, A, &check);
        if (check == 0)
        {
            printf("\tFile %s khong ton tai.\n", a);
            i++;
        }
        else if (check == 2)
        {
            printf("\tFile %s bi loi. \n", a);
        }
        else
        {
            printf("\tDoc file thanh cong.\n");
        }
    } while (check == 0 || check == 2);
    out:
    return i;
    
}

// Chuyen doi du lieu tu file sang mang B[]
void change(float A[][100], float B[], int n)
{
    // Phan tich du lieu
    int i,j,k;
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            B[i] = 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            B[i] += A[j][i];
        }
    }
    float max = B[0];
    for ( k = 0; k < n; k++)
    {
        if (B[k] > max)
        {
            max = B[k];
        }
    }
    B[n] = max;
}

// Chuyen doi du lieu tu B sang mot da thuc
void print_POLYNOMIAL(float B[], int n)
{
    printf("\tDa thuc sau khi xu ly du lieu:  \n");
    printf("\t       F(x)= ");
    int m = 0,i;
    for (i = 0; i <= n; i++)
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
            printf("%.2f", fabs(B[i]));
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

// Tinh gia tri F(x) tai x(o)
float Fx(float B[], int n, float x0)
{
    float Fx = B[0];
    int i;
    for ( i = 1; i <= n; i++)
    {
        Fx = Fx * x0 + B[i];
    }
    return Fx;
}

// Nhap can (a;b)
void enter_input(float *a, float *b, float B[], int n)
{
    float Fa, Fb;
    int i = 0;

    do
    {
        setcolor(0, 3);
        i++;
        if (i > 1)
            printf("\t  ---Khoang nghiem khong phu hop---\n");
        printf("\n\tNhap khoang nghiem(can duoi) a: ");
        setcolor(0, 8);
        scanf("%f", a);
        setcolor(0, 3);
        printf("\tNhap khoang nghiem(can tren) b: ");
        setcolor(0, 8);
        scanf("%f", b);
        Fa = Fx(B, n, *a);
        Fb = Fx(B, n, *b);

    } while (Fa * Fb > 0);
}

// Giai phuong trinh bang phuong phap chia doi
float solve(float B[], float a, float b, int n)
{
    setcolor(0, 5);
    printf("\n%9c", 201);
    int i;
    for ( i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c", 187);

    printf("\n        %c %86c", 4, 4);
    printf("\n        %c                    Bang gia tri thuc hien phuong phap chia doi %23c", 4, 4);
    printf("\n        %c %86c", 4, 4);
    printf("\n\t%c         a          %c          b         %c          c          %c         F(c)         %c\n", 4, 4, 4, 4, 4);
    printf("        %c %86c", 186, 186);
    setcolor(0, 0);

    float c;
    do
    {
        c = (a + b) / 2;

        setcolor(0, 5);
        printf("\n\t%c", 186);
        setcolor(0, 0);
        printf("   %-4s%-7.4g%-6s|%-7s%-7.4g%-6s|%-8s%-7.4g%-6s|%-7s%-10.3f%-5s", " ", a, " ", " ", b, " ", " ", c, " ", " ", Fx(B, n, c), " ");
        setcolor(0, 5);
        printf("%c", 186);
        setcolor(0, 0);
        if (Fx(B, n, b) * Fx(B, n, c) > 0)
            b = c;
        else
            a = c;

    } while (fabs(a - b) > eps && Fx(B, n, c) != 0);

    setcolor(0, 5);
    printf("\n        %c %86c", 4, 4);
    printf("\n        %c", 200);
    for ( i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c\n", 188);

    return c;
}

// Nhap ten file chua ket qua
void result(char a[])
{
    int check = 0;
    FILE *file1 = NULL;
    do
    {
        check = 1;
        setcolor(0, 3);
        printf("\tNhap file luu ket qua: ");
        setcolor(0, 8);
        fgets(a, 100, stdin);
        a[strcspn(a, "\n")] = 0;
        setcolor(0, 3);
        file1 = fopen(a, "a");
        if (file1 == NULL)
        {
            printf("\tFlie %s khong ton tai. \n ", a);
            check = 0;
        }
    } while (check == 0);
    fclose(file1);
}

// Chuc nang cua chuong trinh
int menu_input(int *com)
{
    setcolor(0, 2);
    printf("\n%9c", 201);
    int i;
    for ( i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c", 187);
    printf("\n\t%c %86c", 186, 186);
    printf("\n\t%c ", 186);
    setcolor(0, 14);
    printf("                                   %c   MENU   %c                                      ", 16, 17);
    setcolor(0, 2);
    printf("%c ", 186);
    printf("\n\t%c %86c", 186, 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 1: Nhap du lieu tu ban phim.   ", 4);
    setcolor(0, 2);
    printf("%29c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 2: Nhap du lieu tu file.   ", 4);
    setcolor(0, 2);
    printf("%33c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 3: Su dung du lieu cho san.   ", 4);
    setcolor(0, 2);
    printf("%30c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 4: Tim nghiem trong khoang nghiem (a;b).   ", 4);
    setcolor(0, 2);
    printf("%17c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 5: Thuc hien cung du lieu khac.   ", 4);
    setcolor(0, 2);
    printf("%26c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 6: Xuat ket qua ra file.   ", 4);
    setcolor(0, 2);
    printf("%33c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                        %c 7: Ket thuc chuong trinh.   ", 4);
    setcolor(0, 2);
    printf("%32c ", 186);
    printf("\n\t%c ", 186);
    setcolor(0, 5);
    printf("                                               ");
    setcolor(0, 2);
    printf("%39c ", 186);
    printf("\n        %c", 200);
    for ( i = 0; i <= 85; i++)
        printf("%c", 205);
    printf("%c\n", 188);
    setcolor(0, 3);
    printf("\n\tNhap yeu cau: ");
    setcolor(0, 8);
    do
    {
        setcolor(0, 8);
        scanf("%d", com);
        printf("\n");
        setcolor(0, 3);
        if (*com != 1 && *com != 2 && *com != 3 && *com != 4 && *com != 5 && *com != 7 && *com != 6)
            printf("\n\tMoi ban nhap lai: ");
    } while (*com != 1 && *com != 2 && *com != 3 && *com != 4 && *com != 5 && *com != 7 && *com != 6);
    return *com;
}

// Nhap du lieu tu ban phim
void array_A(float A[][100], int *n)
{   int i,j;
    for ( i = 0; i < *n; i++)
    {
        for ( j = 0; j < *n; j++)
        {
            setcolor(0, 3);
            printf("\tA[%d][%d]=", i + 1, j + 1);
            setcolor(0, 8);
            scanf("%f", &A[i][j]);
        }
    }
}

// In du lieu dau vao
void printarray(float A[][100], int n)
{   int i,j;
    for ( i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("\t      %6.3f  ", A[i][j]);
        }
        printf("\n");
    }
}

// Du doan khoang nghiem
int guess_x(float a[], int n)
{
    float firstRange[100];
    int nRoots = 0;
    double i;
    for (i = -1000; i < 1000; i += 0.1)
    {
        if (Fx(a, n, i) * Fx(a, n, i + 0.1) < 0)
        {
            firstRange[nRoots] = i;
            ++nRoots;
        }
    }
    float rootRange[100];
    int cntRoot = 0;
    int j;
    for ( j = 0; j < nRoots; j++)
    {
        rootRange[cntRoot] = firstRange[j] - 1;
        ++cntRoot;

        rootRange[cntRoot] = ceil(firstRange[j]);

        ++cntRoot;
    }

    printf("\tPhuong trinh F(x) = 0 co %d nghiem thuc.\n", nRoots);
    if (nRoots == 0)
    {
        return 0;
    }

    printf("\tDe xuat khoang nghiem la: ");
    for (j = 0; j < cntRoot; j += 2)
    {
        printf("(%0.6g;%0.6g)      ", rootRange[j], rootRange[j + 1]);
    }
    return 1;
}
// Ham cho nguoi dung
void wait_for_enter()
{
    setcolor(0, 0);
    printf("\n\tNhan enter de tiep tuc...");

    while (getchar() != '\n')
        ;
}

// Ham xoa man hinh
void clear_screen()
{
    system("cls");
}

//HAm nhap lua chon ra menu
char Input_Choice(int n, int control)
{
    printf("\n");
    if (control == 1)
    {
       printf("\tChon \"r\" de quay lai menu \"c\" de tiep tuc.....\n");
    }
    int c, d,i, check = 0;
    do
    {
        printf("\tNhap lua chon cua ban: ");
        setcolor(0,0);
        c = getchar();
        setcolor(0,3);
        if (c == '\n')
        {
            continue;
        }
        if (c == 'r' || c == 'c')
        {
            break;
        }
        for ( i = 49; i <= 49 + n - 1; i++)
        {

            if ((int)c == i)
            {
                check = 1;
                break;
            }
        }
        if (check == 1)
        {
            break;
        }

        d = getchar();
        while (d != '\n')
        {
            d = getchar();
        }
        printf("\tMoi ban nhap lai, chon \"r\" de quay lai menu \"c\" de tiep tuc.....\n");
    } while (1);
    printf("\n");
    return c;
}
