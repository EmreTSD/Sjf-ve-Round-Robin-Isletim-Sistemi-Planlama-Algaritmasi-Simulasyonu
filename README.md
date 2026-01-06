# CPU Scheduling Algorithms Simulation (SJF & Round Robin)

Bu proje, İşletim Sistemleri dersi kapsamında geliştirilmiş, CPU kaynaklarını işlemlere tahsis etmek için kullanılan iki temel zamanlama algoritmasını (SJF ve Round Robin) modelleyen bir C++ programıdır.


## 📌 Özellikler
Program, kullanıcıdan alınan işlem (process) verilerine dayanarak aşağıdaki metrikleri hesaplar:
* **SJF (Shortest Job First):** En kısa işin öncelikli olduğu kesintisiz (non-preemptive) modelleme.
* **Round Robin (RR):** Belirlenen zaman dilimine (Time Slice) göre adil kaynak paylaşımı.
* **Analiz:** Ortalama Bekleme Süresi (Average Waiting Time) ve Ortalama Geri Dönüş Süresi (Average Turnaround Time) hesaplamaları.

## 🛠 Kullanılan Teknolojiler
* **Dil:** C++
* **Yapı:** Struct tabanlı veri modeli, Dinamik bellek yönetimi.

## 🚀 Nasıl Çalıştırılır?
1. Bir C++ derleyicisine (GCC, Clang, MSVC) sahip olduğunuzdan emin olun.
2. Terminal üzerinden projeyi klonlayın ve derleyin:
   ```bash
   g++ main.cpp -o scheduler
   ./scheduler
