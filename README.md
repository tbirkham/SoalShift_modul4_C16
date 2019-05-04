# SoalShift_modul4_C16

## Nomor 1

Semua nama file dan folder harus terenkripsi

Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:
```
qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0
```

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:

“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .

Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

#### Jawaban :

```
static const char *dirpath = "/home/irkham/SISOP/modul4";
```
untuk menyimpan direktori.

```
char cipher[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
```
variable chiper[] untuk menyimpan character list yang dipakai.

```
void encrypt(char change[])
{
	int n;
	for(n = 0; change[n]!= '\0'; ++n)
	{
		int i, ch = change[n];

		if(ch == '/') continue;

		int length = strlen(cipher);
		for(i = 0; i < length; i++)
		{
			if(ch == cipher[i])
			{
				break;
			}
		}
		
		i += 17;
		if(i > 93) 
		i -= length;

		change[n] = cipher[i];
	}
}
```
Pada fungsi **encrypt** ini akan mengecek nilai dari variable **change[]** per karakernya, jika nilainya merupakan karakter '/' maka dilanjutkan saja.

Kemudian, kami melakukan looping sepanjang jumlah karakter variable **cipher[]** dan mengecek apabila variable **ch == cipher[i]** maka akan ter-break. 

Lalu, nilai i akan ditambah dengan 17, dan dicek apabila nilai i menjadi lebih besar dari 93 maka akan dikurangi dengan nilai dari variable **length** atau panjang karakter dari variable **cipher**.
Kemudian, nilai variable **change[n]** akan digantikan dengan nilai variable **cipher[i]**

```
void decrypt(char change[])
{
	int n;
	for(n = 0; change[n] != '\0'; ++n)
	{
		int i, ch = change[n];

		if(ch == '/') continue;

		int length = strlen(cipher);
		for(i = 0; i < length; i++)
		{
			if(ch == cipher[i])
			{
				break;
			}
		}
		
		i -= 17;
		if(i < 0) 
		i += length;

		change[n] = cipher[i];
	}
}
```

Sama halnya dengan fungsi **encrypt** , hanya saja dalam fungsi **decrypt** ini, nilai variable **i** nya akan dikurangi dengan 17 dan jika nilainya menjadi kurang dari 0 maka akan ditambahkan dengan nilai variable **length** atau panjang karakter dari variable **cipher[]** tadi. Kemudian, nilai **change[n]** digantikan dengan nilai dari **cipher[i]**.


## Nomor 2

Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”

Urutan operasi dari kebutuhan ini adalah:

a. Tepat saat sebelum file system di-mount
- Secara otomatis folder “Videos” terbuat di root directory file system
- Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”.
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
- Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
- Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
- Jangan tampilkan file pecahan di direktori manapun

b. Tepat saat file system akan di-unmount
- Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
- Hapus folder “Videos” 

#### Jawaban :







## Nomor 3

Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
- Owner Name 	: ‘chipset’ atau ‘ic_controller’
- Group Name	: ‘rusak’
- Tidak dapat dibaca

Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

#### Jawaban :

- Pada fungsi `xmp_readdir`, tambahkan beberapa sintaks untuk mengecek Owner Name dan Group Name. 
```
	struct passwd *user;
        user = getpwuid(info.st_uid);
        struct group *grup;
        grup = getgrgid(info.st_gid);
        if( (strcmp(user->pw_name,"chipset") == 0 || strcmp(user->pw_name,"ic_controller") == 0) && strcmp(grup->gr_name,"rusak") == 0){
          if((info.st_mode & R_OK)==0){
              char txt[10000] = "/filemiris.txt";
              enkripsi(txt);
              char pathtxt[100000];
              sprintf(pathtxt,"%s%s",dirpath,txt);

              FILE *filetxt;
              filetxt = fopen(pathtxt,"a+");

              char waktu[21];
			  time_t now = time(NULL);
			  strftime(waktu, 20, "%H:%M:%S %Y-%m-%d", localtime(&now));
			  char isi[1000];
              strcpy(isi,de->d_name);
              strcat(isi,"_");
              char iduser[1000];
              sprintf(iduser,"%d_%d",user->pw_uid,grup->gr_gid);
              strcat(isi,iduser);
              strcat(isi,"_");
              strcat(isi,waktu);

              fprintf(filetxt,"%s\n",isi);
              fclose(filetxt);
              remove(cek);
          }
        }
```
- Group Name dan Owner Name disimpan pada struct yaitu 

```
	struct passwd *user;
        user = getpwuid(info.st_uid);
        struct group *grup;
        grup = getgrgid(info.st_gid);
```
- Sedangkan, ``if( (strcmp(user->pw_name,"chipset") == 0 || strcmp(user->pw_name,"ic_controller") == 0) && strcmp(grup->gr_name,"rusak") == 0)`` berfungsi untuk mengecek apakah User dan Group Name sesuai yang diminta pada soal.


## Nomor 4

Pada folder **YOUTUBER**, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah **“.iz1”**. File berekstensi **“.iz1”** tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

#### Jawaban :
- Pada fungsi ``xmp_mkdir`` terdapat sintaks seperti dibawah ini :

```
if (strstr(fpath, youtuber)){
  	res = mkdir(fpath, 0750);
  }
```
Sintaks tersebut berfungsi untuk mendeteksi "/YOUTUBER" pada path directory dari directory yang akan dibuat, maka mode directory akan diubah menjadi 0750.

- Pada fungsi ``xmp_readdir`` terdapat sintaks seperti dibawah ini :

```
else if (strstr(fpath, youtuber) && de->d_type == DT_REG){
  char newPathName[1000];
  sprintf(newPathName, "%s.iz1", temp);
  res = (filler(buf, newPathName, &st, 0));
  eksekusiBahaya(fullpathname, newPathName);
}
```
Sintaks tersebut berfungsi untuk memeriksa jika "/YOUTUBER" yang ada di dalam path dan directory yang dibaca merupakan file biasa, maka file tersebut akan ditampilkan dengan menambahkan ekstensi tambahan **iz1**.

- Pada fungsi ``xmp_create`` terdapat sintaks seperti dibawah ini :

```
if (strstr(fpath, youtuber)){
  	res = creat(fpath, 0640);
  }
```
Sintaks tersebut berfungsi untuk mengubah permission file yang dibentuk pada folder YOUTUBER menjadi 640.

- Pada fungsi ``xmp_chmod`` terdapat sintaks seperti dibawah ini :

```
static int xmp_chmod(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];
	char name[1000];
	sprintf(name,"%s",path);
	enc(name);
	sprintf(fpath, "%s%s",dirpath,name);
	if (strstr(fpath, youtuber)){
		pid_t child = fork();
		int status;
		if (child == 0){
			char *argv[5] = {"zenity", "--error", "--title=Pesan error", "--text=File ekstensi iz1 tidak boleh diubah permissionnya.", NULL};
			execv("/usr/bin/zenity", argv);
		}else{
			while (wait(&status) > 0);
		}
	}else{
		res = chmod(fpath, mode);	
	}
	if (res == -1)
		return -errno;

	return 0;
}
```
Sintaks tersebut berfungsi untuk memunculkan pesan error **File ekstensi iz1 tidak boleh diubah permissionnya.**


## Nomor 5

Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama **Backup** kemudian hasil dari save tersebut akan disimpan pada backup dengan nama **namafile_[timestamp].ekstensi**. Dan ketika file asli dihapus, maka akan dibuat folder bernama **RecycleBin**, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama **namafile_deleted_[timestamp].zip** dan ditaruh kedalam folder RecycleBin (file asli dan backup terhapus). Dengan format **[timestamp]** adalah **yyyy-MM-dd_HH:mm:ss**

#### Jawaban :
- Tambahkan sintaks untuk folder **Backup** pada fungsi ``xmp_write``.

```
static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
    	char fpath[1000];
    	char name[1000];
    	char temp[1000];
	sprintf(name,"%s",path);
    	enc(name);
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,name);
	
	(void) fi;
	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	
	strcpy(temp,path); enc(temp);
	sprintf(name, "%s/%s", dirpath,temp);
	
		if(access(name, R_OK)<0)				
		return res;
	
	char fd_backup[1000]="/home/irkham/SISOP/modul4/XB.Jhu";
	mkdir(fd_backup, 0777);
	
	char namafile[1000], ext[100], waktu[1000], filejadi[1000];
	
	int posisi_ext = posisi(path,'.');
	
	if (posisi_ext==0) {
		posisi_ext = strlen(path);
		ext[0] = '\0';
	}
	else{
		strcpy(ext, path+posisi_ext);
	}
	int p_garing = posisi(path, '/');
	int titik = posisi_ext-(p_garing+1);
	strncpy(namafile, path+1+p_garing, titik);
	namafile[dot] = '\0';
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(waktu, "%04d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	sprintf(filejadi, "%s_%s", namafile, waktu); 
	strcat(filejadi, ext);	
	enc(filejadi);
	sprintf(name, "%s%s", dirpath, temp);
	
	char final[1000];
	sprintf(final, "%s/%s", fd_backup, filejadi);

	int status;
	if (fork()==0)
		execlp("cp","cp", name, final, NULL);

	while((wait(&status))>0);
	
	return res;
}
```
Sintaks tambahan untuk pembuatan folder **Backup** sendiri berada pada sintaks dibawah ini :

```
	char fd_backup[1000]="/home/irkham/SISOP/modul4/XB.Jhu";
	mkdir(fd_backup, 0777);
```

- File yang ingin dimasukkan ke dalam folder **Backup** pun harus memiliki tambahan waktu dan tanggal dibelakangnya (timestamp) sesuai soal.

```
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(waktu, "%04d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
```

- Untuk folder **Recycle Bin**, edit dan tambahkan sintaks pada fungsi ``xmp_unlink`` dengan sintaks dibawah ini :

```
	char fd_recyclebin[100]="/home/irkham/SISOP/modul4/oO.k.EOX[)";
	mkdir(fd_recyclebin, 0777);
```






