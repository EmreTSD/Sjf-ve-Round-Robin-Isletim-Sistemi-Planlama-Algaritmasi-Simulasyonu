#include <iostream>
using namespace std;

// Struct - Her işlemin bilgilerini tutar
struct Process {
    int id;            // işlemi birbirinden ayırt edebilmek için kullandığımız numaramız
    int arrival;       // CPU kuyruğuna giriş yaptığı zamanı
    int burst;         // CPU üzerinde çalıştığı süre
    int remaining;     // Bir kısmının çalıştıktan sonra eğer işlem yapılcak kısmı var olduğu halde başka işlem giriyorsa o ana kadar çalıştığı süre burs time dan çıkarılarak bulunur.
    int finish;        // İşlemin tamamamen tamamlandığı süre 
    int waiting;       // CPU ya alındıktan sonra işlem sırasını beklediği süre
    int turnaround;    // CPU ya girdiği andan itibaren alınarak çıktığı saniyeye kadar geçirdiği süre
    bool isDone;       // İşlem devam edecekmi yoksa tamamen bitirildimi true veya false ile belli eder
};



// Fonksiyon temel: İşlem bilgilerini al
void getBilgiler(Process p[], int n) {
    cout << "\nBilgileri gir:\n";
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;  // P1, P2, P3... dizi 0 dan başlıyor ama id 1 den başlatıyoruz.
        p[i].isDone = false;  // Başlangıçta hiçbiri bitmedi
        
        cout << "\nP" << p[i].id << " icin:\n"; // id üstte atamasını yapmıştık şimdi bu id si atamış olduklarımıza ihtiyacı olan bilgileri gelme zamanı ve işlem süresi gibi bilgileri veriyoruz.
        cout << "  Gelme zamani: ";
        cin >> p[i].arrival;
        cout << "  Islem suresi: ";
        cin >> p[i].burst;
    }
}
//--------------------------------------------------------------------------------------------------------------------------//
// Fonksiyon 1: En kısa işi bul
int enKisaIsiBul(Process p[], int n, int currentTime) {
    int shortest = -1;      // Henüz bulunamadı
    int minBurst = 999994;    // Çok büyük bir sayı
    
    // Tüm işleri kontrol et
    for(int i = 0; i < n; i++) {
        // Bu iş geldi mi? + Bitti mi? + En kısa mı?
        if(p[i].arrival <= currentTime && p[i].isDone == false && p[i].burst < minBurst) {
            
            minBurst = p[i].burst;
            shortest = i;
        }
    }
    
    return shortest;  // En kısa işin indeksini döndürerek ilk önce kısa olan işi çalıştırabilemmizi sağlıcak
}

// Fonksiyon 2: SJF algoritmasını çalıştır
void sjf_Calistir(Process p[], int n) {
    cout << "\n--- ISLEM SIRASI ---\n";
    
    int currentTime = 0;   // Anlık Zamanımız 
    int completed = 0;      // Programa başlarken hiçbir iş bitmemiş tamamlancak olarak kabul ediyoruz
    
    // Tüm işler bitene kadar döngümüz devam edecek
    while(completed < n) {
        
        // En kısa işi bul fonksiyonumuza giderek
        int shortest = enKisaIsiBul(p, n, currentTime);
        
        // Hiç iş yoksa zamanı ilerlet
        if(shortest == -1) {
            cout << "Zaman " << currentTime << ": [Bosta]\n";           // bu kısım o anda işleme alınmış iş yoksa zamanı boşa geçirtir
            currentTime++;
            continue;
        }
        
        // İşi çalıştırır bilgileri vererek
        cout << "\nZaman " << currentTime << ": P" << p[shortest].id 
             << " basladi (sure: " << p[shortest].burst << ")\n";
        
        // İşin çalışma süresi ile o ana gelene kadarki zamanı toplayarak işlemden sonraki zamanımızı buluyoruz
        currentTime = currentTime + p[shortest].burst;
        
        // İş bittiğinde iş bitti diye değişkenimizin değeri true yapıyoruz
        p[shortest].finish = currentTime;
        p[shortest].isDone = true;
        completed++; // her döngü başa gitmeden bu adıma kadar bir işi bitiririz
        
        cout << "Zaman " << currentTime << ": P" << p[shortest].id 
             << " BITTI!\n";
    }
}

// Fonksiyon 3: Süreleri hesapla
void sjf_sureleriHesapla(Process p[], int n) {
    cout << "\n--- HESAPLAMALAR ---\n";
    
    for(int i = 0; i < n; i++) {
        // Turnaround = Bitirme - Gelme
        p[i].turnaround = p[i].finish - p[i].arrival;
        
        // Bekleme = Turnaround - İşlem Süresi
        p[i].waiting = p[i].turnaround - p[i].burst;
        
        cout << "P" << p[i].id << ": ";
        cout << "Turnaround=" << p[i].turnaround;
        cout << ", Bekleme=" << p[i].waiting << endl;
    }
}

// Fonksiyon 4: Sonuçları göster
void sjf_sonuclariGoster(Process p[], int n) {
    cout << "\n=== SONUCLAR ===\n";
    cout << "ID\tGelme\tSure\tBitis\tBekleme\tTurnaround\n";    //tablo şeklinde her prosesimizin bilgilerini tablo şeklinde gösterdiğimiz kısım
    cout << "ID	(AT)  	(BT)   	 (CT)     (WT) 	  (TAT)\n";
    cout << "-----------------------------------------------\n";
    
    float totalWaiting = 0;
    float totalTurnaround = 0;
    
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << " \t ";
        cout << p[i].arrival << "\t ";
        cout << p[i].burst << "\t  ";
        cout << p[i].finish << "\t    ";
        cout << p[i].waiting << " \t     ";
        cout << p[i].turnaround << "\n";
        
        totalWaiting += p[i].waiting;            // ortalama bekleme süresini bulmak için tüm proseslerin bekleme sürelerini topluyoruz
        totalTurnaround += p[i].turnaround;      // ortalama geri dönüş süresini bulmak için tüm proseslerin geri döndükleri sürelerini topluyoruz
    }
    
    cout << "\nOrtalama Bekleme: " << (totalWaiting / n) << endl;
    cout << "Ortalama Turnaround: " << (totalTurnaround / n) << endl;
}
//-----------------------------------------------------------------------------------------------------------------------------//


// // Fonksiyon 1: Round Robin çalıştır
void rRobin_Calistir(Process p[], int n, int timeSlice) {

    cout << "\n--- ROUND ROBIN ---\n";

    int* queue = new int[n * 1000];   // Bir proses birçok kez kuyruğa gelebilir olduğundan büyük bir kuyruk sistemi oluşturuyoruz
    bool* eklendi = new bool[n];     // Kuyruğa eklendi mi? kontrolü için

    int bas = 0;   // Kuyruğun başı
    int son = 0;   // Kuyruğun sonu
    int zaman = 0; // CPU zamanı
    int biten = 0; // Bitmiş proses sayısı

    // Başlangıçta hiçbir proses eklenmemiş
    for(int i = 0; i < n; i++)
        eklendi[i] = false;

    // Zaman 0'da gelen prosesleri kuyruğa ekle
    for(int i = 0; i < n; i++) {
        if(p[i].arrival <= 0) {
            queue[son++] = i;
            eklendi[i] = true;
        }
    }

    // Tüm prosesler bitene kadar devam et
    while(biten < n) {

        // Kuyruk boşsa CPU boşta kalır, zamanı ilerlet
        if(bas == son) {
            zaman++; // zaman ilerler
            // Bu zamana kadar gelenleri ekle
            for(int i = 0; i < n; i++) {
                if(!eklendi[i] && p[i].arrival <= zaman && p[i].remaining > 0) {      // 3 adet koşul var: Kuyruğa eklenmemiş, işlemciye gelmiş ve prosesin bitmemiş olması lazım
                    queue[son++] = i;
                    eklendi[i] = true;
                }
            }
            continue;
        }

        // Kuyruğun başındaki prosesi al
        int pid = queue[bas++];

        // Çalışacağı süre
        int sure = (p[pid].remaining > timeSlice) ? timeSlice : p[pid].remaining;    // kalan süre time slice dan büyükse time slice kadar çalışacak, değilse kalan süre kadar çalışacak

        cout << "Zaman " << zaman << ": P" << p[pid].id << " calisiyor (" << sure << ")\n";

        zaman += sure;
        p[pid].remaining -= sure;

        // Bu sürede gelen yeni prosesleri ekle
        for(int i = 0; i < n; i++) {
            if(!eklendi[i] && p[i].arrival <= zaman && p[i].remaining > 0) {
                queue[son++] = i;
                eklendi[i] = true;
            }
        }

        // Proses bittiyse
        if(p[pid].remaining == 0) {
            p[pid].finish = zaman;
            biten++;
            cout << "Zaman " << zaman << ": P" << p[pid].id << " BITTI\n";
        }
        // Bitmediyse kuyruğun sonuna ekle
        else {
            queue[son++] = pid;
        }
    }

    delete[] queue;
    delete[] eklendi;
}



// Fonksiyon 2: Süreleri hesapla
void rRobin_sureleriHesapla(Process p[], int n) {
    cout << "\n--- HESAPLAMALAR ---\n";
    
    for(int i = 0; i < n; i++) {
        // Turnaround = Bitirme - Gelme
        p[i].turnaround = p[i].finish - p[i].arrival;
        
        // Bekleme = Turnaround - İşlem Süresi
        p[i].waiting = p[i].turnaround - p[i].burst;
        
        cout << "P" << p[i].id << ": ";
        cout << "Turnaround=" << p[i].turnaround;
        cout << ", Bekleme=" << p[i].waiting << endl;
    }
}

// Fonksiyon 3: Sonuçları göster
void rRobin_sonuclariGoster(Process p[], int n) {
    cout << "\n=== SONUCLAR ===\n";
    cout << "ID\tGelme\tSure\tBitis\tBekleme\tTurnaround\n";
    cout << "ID	(AT)  	(BT)   	 (CT)     (WT) 	  (TAT)\n";
    cout << "-----------------------------------------------\n";
    
    float totalWaiting = 0;
    float totalTurnaround = 0;
    
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << " \t ";
        cout << p[i].arrival << "\t ";
        cout << p[i].burst << "\t  ";
        cout << p[i].finish << "\t    ";
        cout << p[i].waiting << " \t     ";
        cout << p[i].turnaround << "\n";
        
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }
    
    cout << "\nOrtalama Bekleme: " << (totalWaiting / n) << endl;
    cout << "Ortalama Turnaround: " << (totalTurnaround / n) << endl;
}

void rRobin_reset(Process* p, int n) {
    for(int i = 0; i < n; i++) {
        p[i].remaining  = p[i].burst;
        p[i].finish     = 0;
        p[i].waiting    = 0;
        p[i].turnaround = 0;
        p[i].isDone     = false;
    }
}


void resetProcesses(Process p[], int n) {
    for(int i = 0; i < n; i++) {
        p[i].remaining  = p[i].burst;
        p[i].finish     = 0;
        p[i].waiting    = 0;
        p[i].turnaround = 0;
        p[i].isDone     = false;
    }
}


//------------------------------------------------------------------------------------------------------------------------------//


int main() {
    cout << "========================================\n";
    cout << "   Shortest Job First (SJF) Scheduling Algoritmasi ve Round Robin Algoritmasi Programimiz \n";
    cout << "========================================\n";
    
    int n;
    cout << "Kac islem var? ";
    cin >> n;
    
    
  // Process dizisi oluştur - DİNAMİK BOYUTLU!
    Process* p = new Process[n];  // Kullanıcının girdiği kadar yer ayır

    getBilgiler(p, n);        // 1. Bilgileri al

    cout << "========================================\n";
    cout << "      Shortest Job First (SJF) Scheduling Algoritmasi\n";
    cout << "========================================\n";
    
    // Fonksiyonları sırayla çağır
    
    sjf_Calistir(p, n);        // 1. SJF çalıştır
    sjf_sureleriHesapla(p, n);    // 2. Süreleri hesapla
    sjf_sonuclariGoster(p, n);    // 3. Sonuçları göster
    
 
    resetProcesses(p,n); // SJF den sonra Round Robin için proses bilgilerini sıfırla
 //--------------------------------------------------------------------------------------------------------------------//
  
cout << "========================================\n";
cout << "      Round Robin Algoritmasi\n";
cout << "========================================\n";

int minBurst = p[0].burst;
int maxBurst = p[0].burst;

// Min ve Max Burst hesapla
for(int i = 1; i < n; i++) {
    if(p[i].burst < minBurst) {
        minBurst = p[i].burst;
    }

    if(p[i].burst > maxBurst) {
        maxBurst = p[i].burst;
    }
}

int userTimeSlice;
cout << "Time Slice (zaman dilimi) kac birim? ";
cin >> userTimeSlice;

// 1) Kullanıcıdan alınan Time Slice ile çalıştır
cout << "========================================\n";
cout << "      Round Robin Algoritmasi (Time Slice = " << userTimeSlice << ")\n";
cout << "========================================\n";

rRobin_reset(p, n);  // Belleği sıfırla
//rRobin_getBilgiler(p, n);  // 1. Bilgileri al
rRobin_Calistir(p, n, userTimeSlice);  // 2. Round Robin çalıştır
rRobin_sureleriHesapla(p, n);  // 3. Süreleri hesapla
rRobin_sonuclariGoster(p, n);  // 4. Sonuçları göster


// 2) Min Burst ile çalıştır
cout << "========================================\n";
cout << "      Round Robin Algoritmasi (Min Burst = " << minBurst << ")\n";
cout << "========================================\n";

rRobin_reset(p, n);  // Belleği sıfırla
rRobin_Calistir(p, n, minBurst);  // 2. Round Robin çalıştır
rRobin_sureleriHesapla(p, n);  // 3. Süreleri hesapla
rRobin_sonuclariGoster(p, n);  // 4. Sonuçları göster


// 3) Max Burst ile çalıştır
cout << "========================================\n";
cout << "      Round Robin Algoritmasi (Max Burst = " << maxBurst << ")\n";
cout << "========================================\n";

rRobin_reset(p, n);  // Belleği sıfırla
rRobin_Calistir(p, n, maxBurst);  // 3. Round Robin çalıştır
rRobin_sureleriHesapla(p, n);  // 3. Süreleri hesapla
rRobin_sonuclariGoster(p, n);  // 4. Sonuçları göster

delete[] p;    // Belleği temizle

cout << "\nBITTI!\n";

    
    return 0;
}



