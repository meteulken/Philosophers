# Philosophers
Philosophers Problem Solution in C

## Process vs Theread

    Process (İşlem):
        Bir programın çalıştığı ortamı ifade eder.
        Bellekte ayrılmış bir alanı, program kodunu, veri yapılarını ve çalışma durumunu içerir.
        İşletim sistemi tarafından yönetilen bir iş birimidir.
        Kendi adres alanına sahip olduğu için, diğer işlemlerden bağımsız olarak çalışır.
        Bir işlem, tek bir thread veya birden çok thread içerebilir.

    Thread (İş Parçacığı):
        Bir işlem içindeki çalışma birimleridir.
        İşlem içinde kodun belirli bir bölümünü yürüten bir iş parçacığıdır.
        İşlem içinde paylaşılan bellek alanını kullanır.
        Birden çok iş parçacığı, aynı işlem içinde eşzamanlı olarak çalışabilir.
        İş parçacıkları, daha hızlı ve etkili çoklu görev yapısını sağlamak için kullanılır.

    Mutex:
        Mutex, çoklu iş parçacığı programlamasında paralel işlemler arasında senkronizasyon sağlamak için kullanılır.
        Mutex, aynı anda yalnızca bir iş parçacığının belirli bir kaynağı veya kritik bölgeyi kullanmasına izin verir.
        Diğer iş parçacıkları, mutex'in kilidini açana kadar beklemek zorundadır.
        Böylece, veri bütünlüğü korunur ve yarış koşulları önlenir.
        Kilitleme ve kilidi açma işlemlerini destekler ve paylaşılan veri yapılarının güvenli erişilmesini sağlar.


    
![Process](https://github.com/meteulken/Philosophers/blob/main/FRM0YzKUUAAT7SI.jpg)
