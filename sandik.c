#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>



int f_yeni_islem(void);

int f_sc_uye_islemleri(void);												//uye_ekle
	int f_uye_ekle(void);													//						//Son Güncelleme: 25.05.2017 - 22.09
	int f_uyeler_goster(void);												//						//Son Güncelleme: 25.05.2017 - 20.13
	int f_uye_sil(void);													//
	int f_uye_bul(int arama_SN);											//

int f_sc_islem_goster(void);												//TAMAMLANDI			//Son Güncelleme: 30.05.2017 - 16.22
	void f_islemler_bul_yazdir (char tur[] ,int SN ,char arama[]);			//TAMAMLANDI			//Son Güncelleme: 30.05.2017 - 21.44

void f_aidat_odemeyenler (char ay[]);										//TAMAMLANDI			//Son Güncelleme: 01.06.2017 - 18.26

int f_islemler_toplam (char tur[] ,int SN ,char arama_kelime[]);			//deneme aşaması		//Son Güncelleme: 22.06.2017 - 22.27	->		bir kez malloc kullanılmadan çalışırsa, ikinci çalışmasında segmantaltion fault 

//Programa özel yardımcı fonksiyonlar
	void f_aidat_odemeyenler (char ay[]);									//TAMAMLANDI			//Son Güncelleme: 31.05.2017 - 10.03
	void f_tam_yedekleme(void);												//...					//Son Güncelleme: 29.05.2017 - 13.23
		int f_dosya_yedekle (char dosya_ismi[]);							//TAMAMLANDI			//Son Güncelleme: 29.05.2017 - 13.23
	int f_islemler_bul (char tur[] ,int SN ,char arama[]);					//TAMAMLANDI			//Son Güncelleme: 30.05.2017 - 18.56
	void f_freele(void);													//eksik					//Son Güncelleme: 01.06.2017 - 14.29
	char *f_uye_isim_bul (int arama_SN);									//TAMAMLANDI			//Son Güncelleme: 31.05.2017 - 02.06
	void f_uyeler_SN_hepsi(void);											//TAMAMLANDI			//Son Güncelleme: 31.05.2017 - 09.58

//Yardımcı fonksiyonlar 
	char *f_simdi_zaman_st(char kontrol);									//free'lenecek			//Son Güncelleme: 27.05.2017 - 19.53				
	int f_simdi_zaman();													//TAMAMLANDI!			//Son Güncelleme: 25.05.2017
	void f_buyuk_harf(char string[]);										//TAMAMLANDI!			//Son Güncelleme: 27.05.2017 - 18.59
	void f_kucuk_harf(char string[]);										//TAMAMLANDI!			//Son Güncelleme: 27.05.2017 - 19.02
	int f_islem_tur_donustur(char is[]);									//Ara Toplam ayarlana	//Son Güncelleme: 27.05.2017
	void f_islem_tur_sabit(char string[]);									//						//Son Güncelleme: 27.05.2017 - 23.47
	void fgets_stdin(char *yazi ,int size ,int yeni_satir);					//						//Son Güncelleme: 28.05.2017 - 19.02		//yeni_satir == 1 -> getchar() v yeni_satir == 0 -> direk
	void fgets_dosya(char *yazi ,int size ,FILE *dosya);					//TAMAMLANDI			//Son Güncelleme: 31.05.2017 - 02.06
	int f_dosya_kopyala (char dosya_ismi[] ,char hedef_dosya_ismi[]);		//TAMAMLANDI			//Son Güncelleme: 29.05.2017 - 13.23
	void f_devam_bas(void);													//TAMAMLANDI			//Son Güncelleme: 30.05.2017 - 22.05
	char *f_buay (void);													//TAMAMLANDI			//Son Güncelleme: 01.06.2017 - 18.25

// Evrensel Tanımlamalar
	struct tag_uyeler
	{
		int SN;
		char tarih[11];
		char isim[50];
	}st_uye_bul;

	struct tag_islemler
	{
		int IN;
		char tarih[11];
		int SN;
		char tur[11];
		int miktar;
		char aciklama[200];
	}*st_islemler_bul;		//st_islemler_bul -> f_islemler_bul (char ,int ,char );

	char simdi_tarih[11] ,simdi_saat[6];
	int sayac_arama;		//sayac_arama -> f_islemler_bul (char ,int ,char );
	int *int_uyeler_SN_hepsi;	//int_uyeler_SN_hepsi -> f_uyeler_SN_hepsi (void)
	int sayac_uyeler_SN_hepsi;	//sayac_uyeler_SN_hepsi -> f_uyeler_SN_hepsi (void)
int main()
{	


	int tercih = 1;
	puts("Bismillahirrahmanirrahim\n");
	while (tercih!=0)
	{	
		//puts("____________________________________________________\n\n");
		puts("\tYARDIMLAŞMA SANDIĞI 0.0\n");
		puts("\t 1- Yeni işlem Gir\n\t 2- Bu ay aidat ödemeyenler\n\t 3- Sandıktaki para\n\t 4- Üye işlemleri\n\t 5- İşlemleri göster\n\t 6- Toplam değerleri göster\n\t 7- ...\n\t 8- ...\n\n\t 0- Çıkış\n");
		printf("Yapmak istediğiniz işlem numarasını giriniz: ");	scanf("%d",&tercih );
		puts("");

		switch (tercih)
		{
			case 1:
			system("clear");
			f_yeni_islem();
			break;

			case 2:
			system("clear");
			f_aidat_odemeyenler(f_buay());
			f_devam_bas();
			break;

			case 3:
			system("clear");
			//puts("____________________________________________________");
			printf ("Sandık kasası:  %d TL" ,f_islemler_toplam ("0" ,0 ,"0"));
			f_devam_bas();
			break;

			case 4:
			system("clear");
			f_dosya_yedekle(".uyeler.txt");
			if(f_sc_uye_islemleri() == -1)
			{
				//Çıkış
				puts("\nAllah işinizi rast getirsin");
				return 0;
			}
			break;

			case 5:
			system("clear");
			if(f_sc_islem_goster() == -1)
			{
				//Çıkış
				puts("\nAllah işinizi rast getirsin");
				return 0;
			}
			//f_islemler_bul_goster("00000" ,0 ,"000");
			break;

			case 6:
			system("clear");
			char *tur, *arama_kelime;	tur = (char*)malloc(sizeof(char) * 10); arama_kelime = (char *) malloc (sizeof(char) * 20);
			int SN;
			printf("İşlem türü giriniz (Hepsi->0): ");			scanf("%s" ,tur);
			printf("Üye SN giriniz (Hepsi->0): ");				scanf("%d" ,&SN);
			printf("Aranacak kelimeyi giriniz (Hepsi->0): ");	scanf("%s" ,arama_kelime);
			printf ("Toplam: %d TL" ,f_islemler_toplam (tur ,SN ,arama_kelime));

			free(tur);	free(arama_kelime);
			f_devam_bas();
			break;

			case 7:
			system("clear");

			puts("Geçerli işlem oluşturulmamış");
			
			f_devam_bas();
			break;

			case 8:
			system("clear");

			puts("Geçerli işlem oluşturulmamış");
			
			f_devam_bas();
			break;

			case 0:
			//Çıkış
			f_freele(	);
			f_tam_yedekleme();
			puts("Allah işinizi rast getirsin");
			return 0;

			default:
			printf("Lütfen geçerli bir işlem seçiniz.\n");
			printf("a\n");

		}
		puts("\n");
		system("clear");
	}
	printf("Olası olmayan çıkış\n");
	f_freele();
	f_tam_yedekleme();
	puts("Allah işinizi rast getirsin");
	return 0;
}

int f_yeni_islem(void)
{
	int arama_SN;
	struct
	{
		int IN;
		int SN;
		char tarih[11];
		char tur[11];
		int miktar;
		char aciklama[200];
	}islem;
	f_uyeler_goster();
	puts("");

	FILE *dg_yeni_islem;
	dg_yeni_islem = fopen(".islemler.txt","a+");
	if (dg_yeni_islem == NULL)
	{
		puts ("\".islemler.txt\" isimli dosya açılamadı.");
		return 1;
	}

	islem.IN = 0;
	while (!feof(dg_yeni_islem))
	{
		fscanf(dg_yeni_islem,"%d %s %d %s %d",&islem.IN ,islem.tarih ,&islem.SN ,islem.tur ,&islem.miktar);
//		fgets(islem.aciklama ,2 ,dg_yeni_islem);
		fgets_dosya(islem.aciklama ,200 ,dg_yeni_islem);
	}
	printf("Son İşlem: %d %s %d %s %d %s\n\n" ,islem.IN ,islem.tarih ,islem.SN ,islem.tur ,islem.miktar ,islem.aciklama  );
	
	islem.IN++;

	printf("İşlem numarası: %d\n",islem.IN );
	memcpy(islem.tarih, f_simdi_zaman_st('t'), sizeof(char) * 11);
	printf("İşlem tarihi: %s",islem.tarih);					char e_h; scanf("%c",&e_h); scanf("%c",&e_h);	if(e_h == 'h') scanf("%s",islem.tarih);
	printf("Üye SN giriniz: ");								scanf("%d",&islem.SN);						f_uye_bul(islem.SN);
	printf("Üye: %s\n",st_uye_bul.isim );
	printf("İşlem türünü giriniz: ");						scanf("%s",islem.tur);				f_buyuk_harf(islem.tur);	f_islem_tur_sabit(islem.tur);
	printf("Miktar giriniz: ");								scanf("%d",&islem.miktar);
	printf("İşlem açıklaması giriniz: ");					fgets_stdin(islem.aciklama ,sizeof(islem.aciklama) ,1);//getchar();fgets(islem.aciklama, 200, stdin);

	fprintf(dg_yeni_islem, "\n%d\t%s\t%d\t%s\t%d\t(%s)",islem.IN ,islem.tarih ,islem.SN ,islem.tur ,islem.miktar ,islem.aciklama);
	fclose(dg_yeni_islem);
	puts("\nYeni işlem \".islemler.txt\" dosyasına eklendi.");

	switch (f_islem_tur_donustur(islem.tur))
	{
		case 1:	//Aidat
		puts("Aidat için düzenlemeler yapılıyor...");
		break;

		case 2:	//"APB"
		puts("APB için düzenlemeler yapılıyor...");
		break;

		case 3:	//"APB-Ö"
		puts("APB-Ö için düzenlemeler yapılıyor...");
		break;

		case 4:	//"PDAY"
		puts("PDAY için düzenlemeler yapılıyor...");
		break;

		case 5:	//"PDAY-Ö"
		puts("PDAY-Ö için düzenlemeler yapılıyor...");
		break;

		case 6:	//"Ara Toplam"
		puts("Ara Toplam için düzenlemeler yapılıyor...");
		break;

		default:
		printf("Hata işlem türü\n");
	}

	return 0;
}

void f_buyuk_harf(char string[])
{
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] >= 'a' && string[i] <= 'z') 
		{
			string[i] = string[i] - 32;
		}
		/*string[i] = toupper(string[i]);*/
	}
}

void f_kucuk_harf(char string[])
{
	for (int i = 0; string[i] != '\0'; ++i)
	{
		if (string[i] >= 'A' && string[i] <= 'Z') 
		{
			string[i] = string[i] + 32;
		}
	}
}

void f_islem_tur_sabit(char string[])
{

	if (strcmp(string, "AIDAT") == 0) memcpy(string, "Aidat", sizeof("Aidat"));
}

int f_uye_ekle(void)
{
	struct tag_uyeler st_uye_ekle;

	FILE *dg_uye_ekle;
	dg_uye_ekle = fopen(".uyeler.txt","a+");
	if (dg_uye_ekle == NULL)
	{
		puts ("\".uyeler.txt\" isimli dosya açılamadı.");
		return 1;
	}

	while (!feof(dg_uye_ekle))
	{
		fscanf(dg_uye_ekle, "%d",&st_uye_ekle.SN);
		fscanf(dg_uye_ekle ,"%s" ,st_uye_ekle.tarih);
		fgets_dosya(st_uye_ekle.isim ,50 ,dg_uye_ekle);
	}
	st_uye_ekle.SN += 100;

	st_uye_ekle.tarih[0] = '0';
	while(st_uye_ekle.tarih[0] == '0')
	{
		printf("\n\t\tYENİ ÜYE EKLEME (Çıkış: -1)\n");
		printf("Üye SN: %d\n",st_uye_ekle.SN);
		printf("Üye ad ve soyadını giriniz: ");								fgets_stdin(st_uye_ekle.isim, 50, 1);
		if(st_uye_ekle.isim[0] == '-' && st_uye_ekle.isim[1] == '1')		return 1;
		memcpy(st_uye_ekle.tarih, f_simdi_zaman_st('t'), sizeof(char) * 11);	
		printf("Tarih: %s",st_uye_ekle.tarih );	char e_h; scanf("%c",&e_h);	if(e_h == 'h') scanf("%s",st_uye_ekle.tarih);
		if (st_uye_ekle.tarih[0] == '0')	puts("\nHATA_101");
	}

	fprintf(dg_uye_ekle, "\n%d %s %s",st_uye_ekle.SN ,st_uye_ekle.tarih ,st_uye_ekle.isim);
	fclose(dg_uye_ekle);
	printf("Yeni üye \"%d %s %s\", \".uyeler.txt\" dosyasına eklendi.",st_uye_ekle.SN ,st_uye_ekle.tarih ,st_uye_ekle.isim);
	return 0;
}

int f_simdi_zaman()	// Yapılacak
{
	time_t simdi = time(0);
	struct tm zaman;
	zaman = *localtime(&simdi);
	strftime(simdi_tarih ,sizeof(simdi_tarih) ,"%d.%m.%Y" ,&zaman );
	strftime(simdi_saat, sizeof(simdi_saat), "%H.%M", &zaman);
	return 1;
}

char * f_simdi_zaman_st(char kontrol)
{

	time_t simdi = time(0);
	struct tm zaman;
	zaman = *localtime(&simdi);

	char * r_simdi_zaman_st;
	if (kontrol == 't')
	{
		r_simdi_zaman_st = malloc(sizeof(char)*11);
		strftime(r_simdi_zaman_st ,sizeof(simdi_tarih) ,"%d.%m.%Y" ,&zaman );
	}
	else if (kontrol == 's')
	{
		r_simdi_zaman_st = malloc(sizeof(char)*5);
		strftime(r_simdi_zaman_st, sizeof(simdi_saat), "%H.%M", &zaman);
	}
	else if (kontrol == 'y')	//yyyy.aa.gg
	{
		r_simdi_zaman_st = malloc(sizeof(char)*11);
		strftime(r_simdi_zaman_st, sizeof(char)*11, "%Y.%m.%d", &zaman);
	}
	return r_simdi_zaman_st;
}

int f_uyeler_goster(void)
{
	struct tag_uyeler st_uye_goster;
	FILE *dg_uye_goster;
	dg_uye_goster = fopen(".uyeler.txt","a+");
	if (dg_uye_goster == NULL)
	{
		puts ("\".uyeler.txt\" isimli dosya açılamadı.");
		return 1;
	}

	printf("\n\n\t     ÜYE LİSTESİ\n");
	while (!feof(dg_uye_goster))
	{
		fscanf(dg_uye_goster, "%d",&st_uye_goster.SN);
		fscanf(dg_uye_goster ,"%s" ,st_uye_goster.tarih);
		fgets_dosya(st_uye_goster.isim ,50 ,dg_uye_goster);
		fprintf(stdout, "\t%d\t%s\n",st_uye_goster.SN ,st_uye_goster.isim);
	}

	return 0;
}

int f_uye_sil(void)
{
	struct tag_uyeler st_uye_sil;
	int arama_SN, sayac_uye_sil = 0;

	f_uyeler_goster();

	FILE *dg_uye_sil;
	FILE *dg_taslak;
	dg_taslak = fopen(".taslak.txt","a+");
	dg_uye_sil = fopen(".uyeler.txt","a+");
	if (dg_uye_sil == NULL)
	{
		puts ("\".uyeler.txt\" isimli dosya açılamadı.");
		return 1;
	}
	if (dg_taslak == NULL)
	{
		puts ("\".taslak.txt\" isimli dosya açılamadı.");
		return 1;
	}

	printf("Silmek istediğiniz üyenin SN'sini giriniz(çıkış-0): ");	scanf("%d",&arama_SN);
	if(arama_SN==0)	
	{
		puts("Silme işleminden vazgeçildi.");
		remove(".taslak.txt");
		fclose(dg_taslak);
		fclose(dg_uye_sil);
		return 0;
	}

	while (!feof(dg_uye_sil))
	{
		fscanf(dg_uye_sil, "%d" ,&st_uye_sil.SN);
		fscanf(dg_uye_sil, "%s" ,st_uye_sil.tarih);
		fgets_dosya(st_uye_sil.isim ,50 ,dg_uye_sil);
		if(st_uye_sil.SN!=arama_SN)
		{
			fprintf(dg_taslak, "%d %s %s\n",st_uye_sil.SN ,st_uye_sil.tarih ,st_uye_sil.isim);
		}
		else 
		{
			sayac_uye_sil++;
			printf("Üye bulundu: ");
			fprintf(stdout, "%d %s %s\n",st_uye_sil.SN ,st_uye_sil.tarih ,st_uye_sil.isim);
		}
	}

	if(sayac_uye_sil == 0)
	{
		printf("%d sandık numaralı üye bulunamadı",arama_SN);
		remove(".taslak.txt");
		fclose(dg_taslak);
		fclose(dg_uye_sil);
		return 1;
	}

	remove(".uyeler.txt");
	rename(".taslak.txt",".uyeler.txt");

	fclose(dg_taslak);
	fclose(dg_uye_sil);

	puts("Silme işlemi tamamlandı.");
	return 0;
}

int f_sc_uye_islemleri(void)
{
	int tercih = 1;
	while (tercih!=0)
	{
		//system-clear puts("___________________________________________________\n\n");
		puts("\t   ~ÜYE İŞLEMLERİ~\n");
		puts("\t 1- Yeni üye ekle\n\t 2- Üyeleri göster\n\t 3- Üye sil\n\t 4- Üye bul\n\n\t 0- Çıkış\n\t-1- Üst menüye dön\n");
		printf("Yapmak istediğiniz işlem numarasını giriniz: ");			scanf("%d",&tercih );
		puts("");

		switch (tercih)
		{
			case 1:
			f_uye_ekle();
			break;

			case 2:
			f_uyeler_goster();
			break;

			case 3:
			f_uye_sil();
			break;

			case 4:
			puts("Geçerli işlem oluşturulmadı.");
			break;

			case -1:
			return 0;

			case 0:
			return -1;

			default:
			printf("Lütfen geçerli bir işlem seçiniz.\n");

		}
		puts("\n");
	}
	return 0;
}

int f_uye_bul(int arama_SN)
{
	FILE *dg_uye_bul;
	dg_uye_bul = fopen(".uyeler.txt","a+");
	if (dg_uye_bul == NULL)
	{
		puts ("\".uyeler.txt\" isimli dosya açılamadı.");
		return 1;
	}

	while (!feof(dg_uye_bul))
	{
		fscanf(dg_uye_bul, "%d" ,&st_uye_bul.SN);
		fscanf(dg_uye_bul, "%s" ,st_uye_bul.tarih);
		fgets(st_uye_bul.isim ,2 ,dg_uye_bul);
		fgets(st_uye_bul.isim ,50 ,dg_uye_bul);
		
		if(st_uye_bul.SN==arama_SN)
		{	
			fclose(dg_uye_bul);
			for (int i = 0; i < 50; ++i)																	//fgets en son yeni satır "\n" alır, bunu silip string sonu "\0" ile değiştiriliyor.
			{
				if (st_uye_bul.isim[i] == '\n') 
				{
					st_uye_bul.isim[i] = '\0';
					break;
				}
			}
			return 0;
		}
	}

	fclose(dg_uye_bul);
	return 1;
}

int f_islem_tur_donustur(char is[])
{
	if (strcmp(is, "Aidat") == 0)			return 1;
	else if(strcmp(is, "APB") == 0)			return 2;
	else if(strcmp(is, "APB-O") == 0)		return 3;
	else if(strcmp(is, "APB-Ö") == 0)		return 3;
	else if(strcmp(is, "APB-ö") == 0)		return 3;
	else if(strcmp(is, "PDAY") == 0)		return 4;
	else if(strcmp(is, "PDAY-O") == 0)		return 5;
	else if(strcmp(is, "PDAY-Ö") == 0)		return 5;
	else if(strcmp(is, "PDAY-ö") == 0)		return 5;
	else if(strcmp(is, "ARA TOPLAM") == 0)	return 6;
	else									return -1;
}

void fgets_stdin(char *yazi ,int size ,int yeni_satir)	//1) Klavyeden girilen yazının başında '\n' varsa (yeni_satir = 1) siler, yoksa (yeni_satir = 2) birşey yapmaz. 
														//2) Sonundaki '\n' karakterini siler.
{	
	if(yeni_satir == 1)
	{
		getchar();
		fgets(yazi, size ,stdin);
		for (int i = 0; yazi[i] != '\0'; ++i)																	//fgets en son yeni satır "\n" alır, bunu silip string sonu "\0" ile değiştiriliyor.
		{
			if (yazi[i] == '\n') 
			{
				yazi[i] = '\0';
				break;
			}
		}
	}

	else if (yeni_satir == 0)
	{
		fgets(yazi, size ,stdin);
		for (int i = 0; yazi[i] != '\0'; ++i)																	//fgets en son yeni satır "\n" alır, bunu silip string sonu "\0" ile değiştiriliyor.
		{
			if (yazi[i] == '\n') 
			{
				yazi[i] = '\0';
				break;
			}
		}
	}
}

int f_dosya_kopyala (char dosya_ismi[] ,char hedef_dosya_ismi[])	//dosya_ismi isimli txt dosyasını hedef_dosya_ismi isimli txt dosyasına kopyalar.
{
	FILE *dg_kaynak, *dg_hedef;

	dg_kaynak = fopen(dosya_ismi ,"r");
	if (dg_kaynak == NULL)
	{
		printf("\"%s\" dosyası okunamadı.\n",dosya_ismi );
		return 1;
	}

	dg_hedef = fopen(hedef_dosya_ismi ,"w");
	if (dg_hedef == NULL)
	{
		printf("\"%s\" dosyası oluşturulamadı.\n",hedef_dosya_ismi );
		return 2;
	}

	char ch;
	while (1) 
	{
		ch = fgetc(dg_kaynak);

		if (ch == EOF)	break;
		else			putc(ch, dg_hedef);
	}


	fclose (dg_kaynak);
	fclose (dg_hedef);

	return 0;
}

int f_dosya_yedekle (char dosya_ismi[])
{
	char hedef_dosya_ismi[100];
	sprintf(hedef_dosya_ismi, ".yedek/%s_%s_%s" ,f_simdi_zaman_st('y') ,f_simdi_zaman_st('s') ,dosya_ismi);

	f_dosya_kopyala (dosya_ismi ,hedef_dosya_ismi);
}

void f_tam_yedekleme(void)
{
	f_dosya_yedekle(".islemler.txt");
 //	f_dosya_yedekle(".uyeler.txt");
 //	f_dosya_yedekle("sandik.c");
}

int f_sc_islem_goster(void)
{
	char arama_kelime[50];
	int tercih = 1 ,arama_uye_SN;

	//system-clear puts("___________________________________________________\n\n");
	puts("\t   ~İŞLEM GÖSTER~\n");
	puts("\t 1- Tüm işlemler\n\t 2- Aidatlar\n\t 3- APB\n\t 4- APB-Ö\n\t 5- PDAY\n\t 6- PDAY-Ö\n\t 7- Üye\n\n\t 0- Geri Dön\n");
	printf("Yapmak istediğiniz işlem numarasını giriniz: ");			scanf("%d",&tercih );
	puts("");

	switch (tercih)
	{
		case 1:		//Tüm İşlemler
		f_islemler_bul_yazdir ("00000" ,0 ,"000");
		break;

		case 2:		//Aidatlar
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		printf("Aranacak kelimeyi giriniz (hepsi -> 0): ");		scanf("%s" ,arama_kelime);		if (arama_kelime[0] == '0')	memcpy(arama_kelime, "000" ,sizeof(char) * 3);
		f_islemler_bul_yazdir ("Aidat" ,arama_uye_SN ,arama_kelime);
		break;

		case 3:		//APB
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		printf("Aranacak kelimeyi giriniz (hepsi -> 0): ");		scanf("%s" ,arama_kelime);		if (arama_kelime[0] == '0')	memcpy(arama_kelime, "000" ,sizeof(char) * 3);
		f_islemler_bul_yazdir ("APB" ,arama_uye_SN ,arama_kelime);
		break;

		case 4:		//APB-Ö
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		printf("Aranacak kelimeyi giriniz (hepsi -> 0): ");		scanf("%s" ,arama_kelime);		if (arama_kelime[0] == '0')	memcpy(arama_kelime, "000" ,sizeof(char) * 3);
		f_islemler_bul_yazdir ("APB-O" ,arama_uye_SN ,arama_kelime);
		break;

		case 5:		//PDAY
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		printf("Aranacak kelimeyi giriniz (hepsi -> 0): ");		scanf("%s" ,arama_kelime);		if (arama_kelime[0] == '0')	memcpy(arama_kelime, "000" ,sizeof(char) * 3);
		f_islemler_bul_yazdir ("PDAY" ,arama_uye_SN ,arama_kelime);
		break;

		case 6:		//PDAY-Ö
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		printf("Aranacak kelimeyi giriniz (hepsi -> 0): ");		scanf("%s" ,arama_kelime);		if (arama_kelime[0] == '0')	memcpy(arama_kelime, "000" ,sizeof(char) * 3);
		f_islemler_bul_yazdir ("PDAY-O" ,arama_uye_SN ,arama_kelime);
		break;

		case 7	:		//ÜYE
		printf("Üye SN giriniz (hepsi -> 0): ");				scanf("%d" ,&arama_uye_SN);
		f_islemler_bul_yazdir ("00000" ,arama_uye_SN ,"000");
		break;

		case 0:
		//Geri Dön
		return 0;

		default:
		printf("Lütfen geçerli bir işlem seçiniz.\n");
	}

	puts("\n");
	return 0;
}

int f_islemler_toplam (char *tur ,int SN ,char *arama_kelime)
{
	if(tur[0] == '0' & tur[1] == '\0')						{			 tur = (char*) malloc(sizeof(char)*7);		memcpy(tur ,"00000" ,7 * sizeof(char));				}
	if(arama_kelime[0] == '0' & arama_kelime[1] == '\0')	{	arama_kelime = (char*) malloc(sizeof(char)*5);		memcpy(arama_kelime ,"000" ,5 * sizeof(char));		}

	int islem_toplam = 0;
	f_islemler_bul (tur ,SN ,arama_kelime);
	for (int i = 0; i < sayac_arama; ++i)
	{
		islem_toplam += st_islemler_bul[i].miktar;
	}
	free(tur);
	free(arama_kelime);

	return islem_toplam;
}	

int f_islemler_bul (char tur[] ,int SN ,char arama[])		//00000 ,0 ,000
{
	FILE *dg_islemler_bul;
	dg_islemler_bul = fopen(".islemler.txt","r");
	if (dg_islemler_bul == NULL)
	{
		printf("\".islemler.txt\" dosyası okunamadı.\n");
		return 0;
	}

	sayac_arama = 0;
	//struct tag_islemler *st_islemler_bul;
	free(st_islemler_bul);
	st_islemler_bul = (struct tag_islemler*) malloc(sizeof(struct tag_islemler) * 2);

	/*********************************İlk satır okunur, işleme alınmaz************************************************************/
	fscanf(dg_islemler_bul ,"%d %s %d %s %d" ,&st_islemler_bul[sayac_arama].IN ,st_islemler_bul[sayac_arama].tarih ,&st_islemler_bul[sayac_arama].SN ,st_islemler_bul[sayac_arama].tur ,&st_islemler_bul[sayac_arama].miktar );
	fgets_dosya(st_islemler_bul[sayac_arama].aciklama ,sizeof(st_islemler_bul[sayac_arama].aciklama) ,dg_islemler_bul);
	/*********************************BİTİŞ - İlk satır okunur, işleme alınmaz****************************************************/

	puts("");
	while(!feof(dg_islemler_bul))
	{		
		fscanf(dg_islemler_bul ,"%d %s %d %s %d" ,&st_islemler_bul[sayac_arama].IN ,st_islemler_bul[sayac_arama].tarih ,&st_islemler_bul[sayac_arama].SN ,st_islemler_bul[sayac_arama].tur ,&st_islemler_bul[sayac_arama].miktar );
		fgets_dosya(st_islemler_bul[sayac_arama].aciklama ,sizeof(st_islemler_bul[sayac_arama].aciklama) ,dg_islemler_bul);
		
		if (strcmp (st_islemler_bul[sayac_arama].tur, tur) == 0)
		{
			if (SN == st_islemler_bul[sayac_arama].SN)
			{
				if (strstr(st_islemler_bul[sayac_arama].aciklama ,arama) != NULL)
				{
					sayac_arama++;
				}
				else if(strcmp(arama, "000") == 0)
				{
					sayac_arama++;
				}				
			}
			else if (SN == 0)
			{
				if (strstr(st_islemler_bul[sayac_arama].aciklama ,arama) != NULL)
				{
					sayac_arama++;
				}
				else if(strcmp(arama, "000") == 0)
				{
					sayac_arama++;
				}				
			}
		}
		else if (strcmp (tur, "00000") == 0)
		{
			if (SN == st_islemler_bul[sayac_arama].SN)
			{
				if (strstr(st_islemler_bul[sayac_arama].aciklama ,arama) != NULL)
				{
					sayac_arama++;
				}
				else if(strcmp(arama, "000") == 0)
				{
					sayac_arama++;
				}				
			}
			else if (SN == 0)
			{
				if (strstr(st_islemler_bul[sayac_arama].aciklama ,arama) != NULL)
				{
					sayac_arama++;
				}
				else if(strcmp(arama, "000") == 0)
				{
					sayac_arama++;
				}				
			}
		}

		st_islemler_bul = (struct tag_islemler*) realloc (st_islemler_bul ,sizeof(struct tag_islemler) * (sayac_arama + 2));
	}
	fclose(dg_islemler_bul);

	return sayac_arama;
}

void f_islemler_bul_yazdir (char tur[] ,int SN ,char arama[])
{
	f_islemler_bul (tur ,SN ,arama);

	if (sayac_arama == 0)					printf("Herhangi bir işlem listelenemedi\n\n");
	else if (strcmp (tur, "00000") == 0)	printf("%d işlem listelendi\n\n" ,sayac_arama);
	else 									printf("%d %s listelendi\n\n" ,sayac_arama ,tur );

	printf("IN\tTarih\t\tSN\tTür\tMiktar\tAçıklama\n---\t----------\t-----\t------\t------\t-------------------\n");
	for (int i = 0; i < sayac_arama; ++i)
	{
		fprintf(stdout, "%3.d\t%s\t%d\t%s\t%4.d\t%s\n" ,st_islemler_bul[i].IN ,st_islemler_bul[i].tarih ,st_islemler_bul[i].SN ,st_islemler_bul[i].tur ,st_islemler_bul[i].miktar ,st_islemler_bul[i].aciklama );
	}

	f_devam_bas();
}

void f_devam_bas(void)
{
	puts("\n\nDevam etmek için bir tuşa basınız...");
	getchar();	getchar();
}

void f_aidat_odemeyenler (char ay[])
{
	int kontrol = 0;
	f_uyeler_SN_hepsi();
	f_islemler_bul ("Aidat" ,0 ,ay);

	f_buyuk_harf(ay);
	//system-clear puts("____________________________________________________");
	printf("    %s ayı aidatını ödemeyenler\n\n",ay);
	for (int i = 0; i < sayac_uyeler_SN_hepsi-1; ++i)
	{
		kontrol = 0;
		for (int j = 0; j < sayac_arama; ++j)
		{
			if(int_uyeler_SN_hepsi[i] == st_islemler_bul[j].SN)	kontrol++;
		}
		if(kontrol == 0)
		{
			printf("\t%d\t%s\n" ,int_uyeler_SN_hepsi[i] ,f_uye_isim_bul(int_uyeler_SN_hepsi[i]));
		}
	}
}

char *f_uye_isim_bul (int arama_SN)
{
	char uye_isim[50];
	FILE *dg_uye_isim_bul;
	dg_uye_isim_bul = fopen(".uyeler.txt","a+");
	if (dg_uye_isim_bul == NULL)
	{
		puts ("\".uyeler.txt\" isimli dosya açılamadı.");
		return "Dosya açılamadı";
	}
	struct tag_uyeler *st_uye_isim_bul = (struct tag_uyeler*) malloc (sizeof(struct tag_uyeler));

	while (!feof(dg_uye_isim_bul))
	{
		fscanf(dg_uye_isim_bul, "%d" ,&st_uye_isim_bul->SN);
		fscanf(dg_uye_isim_bul, "%s" ,st_uye_isim_bul->tarih);
		fgets_dosya (st_uye_isim_bul->isim ,50 ,dg_uye_isim_bul);

		if(st_uye_isim_bul->SN==arama_SN)
		{	
			fclose(dg_uye_isim_bul);
			free(st_uye_isim_bul);	
			return st_uye_isim_bul->isim;
		}
	}

	fclose(dg_uye_isim_bul);
	free(st_uye_isim_bul);
	return "Üye bulunamadı!";
}

void fgets_dosya(char *yazi ,int size ,FILE *dosya)
{
	fgets(yazi, 2 ,dosya);
	fgets(yazi, size ,dosya);

	for (int i = 0; yazi[i] != '\0'; ++i)																	//fgets en son yeni satır "\n" alır, bunu silip string sonu "\0" ile değiştiriliyor.
	{
		if (yazi[i] == '\n') 
		{
			yazi[i] = '\0';
			break;
		}
	}
}

void f_uyeler_SN_hepsi(void)
{
	int_uyeler_SN_hepsi = (int*) malloc (sizeof(int));
	char cop[200];
	FILE *dg_uyeler_SN_hepsi;
	dg_uyeler_SN_hepsi = fopen(".uyeler.txt","r");

	for (sayac_uyeler_SN_hepsi = 0; !feof(dg_uyeler_SN_hepsi); ++sayac_uyeler_SN_hepsi)
	{
		fscanf(dg_uyeler_SN_hepsi ,"%d" ,&int_uyeler_SN_hepsi[sayac_uyeler_SN_hepsi]);
		fgets_dosya (cop ,sizeof(char) * 200 ,dg_uyeler_SN_hepsi);
		int_uyeler_SN_hepsi = (int*) realloc (int_uyeler_SN_hepsi ,sizeof(int) * (sayac_uyeler_SN_hepsi+2));
	}
}

char *f_buay (void)			//Bu ayı "Haziran17"-"aaaayy" formatında döner.
{
	char buay[12];
	char buyil[3];
	char *buayyil = (char *) malloc(sizeof(char) * 15);
	time_t simdi = time(0);
	struct tm zaman;
	zaman = *localtime(&simdi);
	strftime(buay ,sizeof(buay) ,"%B" ,&zaman );

			 if (strcmp (buay, "January") == 0)		memcpy(buay ,"Ocak" ,sizeof(buay));
		else if (strcmp (buay, "February") == 0)	memcpy(buay ,"Şubat" ,sizeof(buay));
		else if (strcmp (buay, "March") == 0)		memcpy(buay ,"Mart" ,sizeof(buay));
		else if (strcmp (buay, "April") == 0)		memcpy(buay ,"Nisan" ,sizeof(buay));
		else if (strcmp (buay, "May") == 0)			memcpy(buay ,"Mayıs" ,sizeof(buay));
		else if (strcmp (buay, "June") == 0)		memcpy(buay ,"Haziran" ,sizeof(buay));
		else if (strcmp (buay, "July") == 0)		memcpy(buay ,"Temmuz" ,sizeof(buay));
		else if (strcmp (buay, "August") == 0)		memcpy(buay ,"Ağustos" ,sizeof(buay));
		else if (strcmp (buay, "September") == 0)	memcpy(buay ,"Eylül" ,sizeof(buay));
		else if (strcmp (buay, "October") == 0)		memcpy(buay ,"Ekim" ,sizeof(buay));
		else if (strcmp (buay, "November") == 0)	memcpy(buay ,"Kasım" ,sizeof(buay));
		else if (strcmp (buay, "December") == 0)	memcpy(buay ,"Aralık" ,sizeof(buay));

	strftime(buyil ,sizeof(buyil) ,"%y" ,&zaman );
	sprintf(buayyil ,"%s%s" ,buay ,buyil);

	return buayyil;
}

void f_freele(void)
{
	free(int_uyeler_SN_hepsi);
	free(st_islemler_bul);
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
/*	free();
*/
}