#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <graphics.h>
void arkaplancizgileri()
{
    initwindow(960,960,"MinimumCevreleyenCember&B-spline",0,0);//arayüzde pencere açan fonksiyon
        setcolor(BLUE);//renk belirleyici fonksiyon
        for(int i=0; i<960; i+=20)//dikey çizgiler
        {
            if(i!=480){//oordinat apsis hariç
                int j=0;
                int h=960;
                line(i,j,i,h);
            }
        }
        for(int i=0; i<960; i+=20)//yatay çizgiler
        {
            if(i!=480)
            {
                int j=0;
                int h=960;
                line(j,i,h,i);
            }

        }
}
void koordinatsistemi()
{
    setcolor(RED);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH);//kalýnlýk belirleyici
        line (0,480,960,480);
        line (480,0,480,960);
        for(int i=20; i<960; i+=20)//küçük çizgiler dikeydeki
        {
            line(i,472,i,488);
        }
        for(int i=20; i<960; i+=20)//küçük çizgiler yataydaki
        {
            line(472,i,488,i);

        }
        setcolor(YELLOW);
        int deger=-24;
        int deger1=0;
        int deger2=0;
        int deger3=0;
        setcolor(GREEN);
        for(int i=-8; i<960; i+=20)
        {
            if(deger<0)//dikeydeki - sayilar
            {
                char sayi[3];
                sprintf(sayi,"%d",deger);
                outtextxy(i,495,sayi);
            }
            deger++;
        }
        for(int i=476; i<960; i+=20)
        {
            if(deger1!=0)//dikeydeki +sayılar
            {
                char sayi[3];
                sprintf(sayi,"%d",deger1);//değer1 i sayiya çevirerek atar sayi bi karakter dizisi
                outtextxy(i,450,sayi);
            }
            deger1++;
        }

        for(int i=472; i<960; i+=20)
        {
            char sayi[3];//yataydaki + sayılar
            sprintf(sayi,"%d",deger2);
            if(deger2!=0)
            {
                outtextxy(495,i,sayi);
            }
            deger2--;
        }
        for(int i=472; i>0; i-=20)
        {
            char sayi[3];
            sprintf(sayi,"%d",deger3);
            if(deger3!=0) //yataydaki - sayılar
            {
                outtextxy(465,i,sayi);
            }
            deger3++;
        }
}
void cemberciz(double x1,double y1,double enbuyuk)
{
setcolor(WHITE);
circle((x1*(double)20) + (double)480, (y1+(double)480) - (y1*(double)20), enbuyuk * (double)20);//(x,y,yarıçap) 20 le çarptı çünkü karelerin kenarları 20
}
void yaricapiciz(double x1,double y1,int matris1[1][2])
{
    setcolor(LIGHTBLUE);
        line(x1*20+480,480-y1*20,matris1[0][0]*20+480,480-matris1[0][1]*20);
    char msg[80];
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL,MAGENTA);
        pieslice((x1*20+480),(480)- y1*20, 0,360, 4);//koordinatları gösteren noktalar. pasta dilimi x,y koordinatlı 360 derece 4 yarıçaplı
}
struct Nokta
{
	float x;
	float y;
};

struct Nokta splineNoktalariniAl(float aralik, int noktaBoyut,struct Nokta noktalar[])
{
    int p0, p1, p2, p3;

    p1 = (int)aralik;
    p2 = (p1 + 1) % noktaBoyut;
    p3 = (p2 + 1) % noktaBoyut;
    if(p1 >= 1)
    {
        p0 = p1 - 1 ;
    }
    else
        p0=noktaBoyut - 1;


     aralik = aralik - (int)aralik;

    float aralikKare = aralik * aralik;
    float aralikKup = aralikKare * aralik;

    float q1 = -aralikKup + 2.0f*aralikKare - aralik;
    float q2 = 3.0f * aralikKup - 5.0f*aralikKare + 2.0f;
    float q3 = -3.0f *aralikKup + 4.0f*aralikKare+ aralik;
    float q4 = aralikKup - aralikKare;

    float konumx = 0.5f * (noktalar[p0].x * q1 + noktalar[p1].x * q2 + noktalar[p2].x * q3 + noktalar[p3].x * q4);
    float konumy = 0.5f * (noktalar[p0].y * q1 +noktalar[p1].y * q2 + noktalar[p2].y * q3 + noktalar[p3].y * q4);

    struct Nokta noktaninKonumuxy = {konumx, konumy };

    return noktaninKonumuxy;
}
int main()
{
    FILE *dosya;
    dosya=fopen("koordinat.txt","r+");//dosya okuma r+ okuma modu
    char dizi[250];
    char atama[1];
    char atama2[2];
    int k=0,x=0,y=0,n=0,uzakliksayisi,xx,yy;
    double uzaklik,cap=0.0;
    if (dosya!=NULL)
    {
        for(int j=0; j<250; j++)
        {
            fscanf(dosya,"%c",&dizi[j]);//dosyadakileri diziye geçiriyo
            printf("%c",dizi[j]);
            if(dizi[j]=='(')
                n++;
            if(dizi[j]=='}')
                break;
        }
        printf("\n");
        int matris[n][2];
        for(x=0; x < n; x++)
        {
            for(y=0; y<2; y++)
            {
                if( dizi[k]!='{' && dizi[k]!=',' && dizi[k]!='}'&& dizi[k]!=')'&& dizi[k]!='(' )
                {
                    if(dizi[k]==' ')//bpşluksa 0 ata
                    {
                        dizi[k]=0;
                    }
                    if(dizi[k]=='-')
                    {
                        if(dizi[k+2]!=',' || dizi[k+2]!=')')//, veya ) değilse 2 basamaklıdır
                        {
                            atama2[0]=dizi[k+1];
                            atama2[1]=dizi[k+2];
                            matris[x][y]=atoi(atama2)*-1;
                            k+=3;
                        }
                        else
                        {
                            atama[0]=dizi[k];
                            matris[x][y]=atoi(atama)*-1;
                            k++;
                        }
                    }

                    else
                    {
                        if(dizi[k+1]!=',' || dizi[k+1]!=')')
                        {
                            atama2[0]=dizi[k];
                            atama2[1]=dizi[k+1];
                            matris[x][y]=atoi(atama2);
                            k+=2;
                        }
                        else
                        {
                            atama[0]=dizi[k];
                            matris[x][y]=atoi(atama);
                            k++;
                        }
                    }

                }
                else
                {
                    y--;//dizi elemanı sayı değilse dizide ilerle ama matrisin indisini değiştirme
                    k++;
                }
            }
        }
        int matris1[1][2];
        int matris2[1][2];
        for(xx=0; xx<n; xx++)
        {
            for(yy=xx+1; yy<n; yy++)
            {
                uzaklik = sqrt((pow(((double)matris[xx][0]-(double)matris[yy][0]),2.0))+(pow(((double)matris[xx][1]-(double)matris[yy][1]),2.0)));//noktaların birbirine olan uzaklığı
                if(uzaklik > cap)//en uzak çap koordinatlarını matris1 ve matirs2 ye ata
                {
                    cap=uzaklik;
                    matris1[0][0]=matris[xx][0];
                    matris1[0][1]=matris[xx][1];
                    matris2[0][0]=matris[yy][0];
                    matris2[0][1]=matris[yy][1];
                }
            }
        }
       double yaricap=cap/2.0;
        double x1=0.0;//merkez kooordinatları
        double y1=0.0;
        x1=matris1[0][0]+matris2[0][0];
        y1=matris1[0][1]+matris2[0][1];
        x1=x1/2.0;//
        y1=y1/2.0;
        int m=0;
        int disardakinokta[1][2];
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                double k1=sqrt(pow((double)x1-(double)matris[i][0],2)+pow((double)y1-(double)matris[i][1],2));//bir noktanın merkeze olan uzaklığı
                double k2=sqrt(pow((double)x1-(double)matris[j][0],2)+pow((double)y1-(double)matris[j][1],2));//diğer noktaların merkeze uzaklığı
                if((yaricap)<k1 && k1>=k2)//bir noktanın merkeze uzaklığı yarıçaptan büyükse ve diğer noktaların merkeze uzaklığından da büyükse ife girer
                {
                    disardakinokta[0][0]=matris[i][0];
                    disardakinokta[0][1]=matris[i][1];
                    m++;
                }
            }
        }
        if(m>0)//m 0 dan büyükse dışarda nokta var demektir
        {
            double x11,y11,dy1,dx1,x22,y22,dy2,dx2,dx,dy;
             x11 = (matris2[0][0] + matris1[0][0]) / 2.0;
             y11 = (matris2[0][1] + matris1[0][1]) / 2.0;
             dy1 = matris2[0][0] - matris1[0][0];
             dx1 = -(matris2[0][1] - matris1[0][1]);

             x22 = (disardakinokta[0][0] + matris2[0][0]) / 2.0;
             y22 = (disardakinokta[0][1] + matris2[0][1]) / 2.0;
             dy2 = disardakinokta[0][0] - matris2[0][0];
             dx2 = -(disardakinokta[0][1] - matris2[0][1]);

             x1 = (y11 * dx1 * dx2 + x22 * dx1 * dy2 - x11 * dy1 * dx2 - y22 * dx1 * dx2) / (dx1 * dy2 - dy1 * dx2);
             y1 = (x1 - x11) * dy1 / dx1 + y11;

             dx = x1 - matris1[0][0];
             dy = y1 - matris1[0][1];
            yaricap=sqrt(dx*dx + dy*dy);
        }
        printf("cemberin merkezi (%lf,%lf)\n",x1,y1);
        printf("cemberin yari capi=%lf",yaricap);
        arkaplancizgileri();
        koordinatsistemi();
        cemberciz(x1,y1,yaricap);
        yaricapiciz(x1,y1,matris1);
        struct Nokta noktalar[n];
        for(int i=0;i <n;i++)
        {
            noktalar[i].x = matris[i][0];
            noktalar[i].y = matris[i][1];
        }

        for (float aralik = 0; aralik < (float)n-1; aralik+= 0.005f)
        {
            struct Nokta konum = splineNoktalariniAl(aralik, n ,noktalar);
            putpixel(konum.x * 20 + 480,480 - konum.y  * 20,WHITE);
        }
        setcolor(YELLOW);
        // merkez ve noktaları çizme
        for(int i=0; i<n; i++)
        {
            setfillstyle(SOLID_FILL,YELLOW);
            pieslice((matris[i][0]*20+480),(480)- matris[i][1]*20, 0,360, 4);
            char koordinat[2];
             sprintf(koordinat, " (%d, %d)", matris[i][0], matris[i][1]);
              outtextxy((matris[i][0]*20+480),(480)- matris[i][1]*20,koordinat);
        }

        getch();

    }
    else
    {
        printf("Dosya bulunamadi");
    }

    fclose(dosya);//dosyayı kapat

    return 0;
}
