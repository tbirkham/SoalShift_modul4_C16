# SoalShift_modul4_C16

1. Semua nama file dan folder harus terenkripsi

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






2. Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”

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







3. Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
- Owner Name 	: ‘chipset’ atau ‘ic_controller’
- Group Name	: ‘rusak’
- Tidak dapat dibaca

Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

#### Jawaban :






4. Pada folder **YOUTUBER**, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah **“.iz1”**. File berekstensi **“.iz1”** tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

#### Jawaban :







5. Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama **Backup** kemudian hasil dari save tersebut akan disimpan pada backup dengan nama **namafile_[timestamp].ekstensi**. Dan ketika file asli dihapus, maka akan dibuat folder bernama **RecycleBin**, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama **namafile_deleted_[timestamp].zip** dan ditaruh kedalam folder RecycleBin (file asli dan backup terhapus). Dengan format **[timestamp]** adalah **yyyy-MM-dd_HH:mm:ss**

#### Jawaban :








