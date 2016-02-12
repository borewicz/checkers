# checkers

### Co to za badziew?
Ten projekt powstał z myślą o zaliczeniu jakże cudownego przedmiotu, jakim są Sieci Komputerowe 2.

### Czym różnią się od zwykłych szachów?
Niczym. Poza tym że paru ludzi ma jeden kolor i się głosuje na ruch. Nic odkrywczego.

### Wymagania
Serwer wymaga boosta, a klient - biblioteki Qt.

### Kompilacja
Ponieważ projekt pisały dwie osoby, każdą część projektu kompiluje siię  zupełnie inny sposób. 

##### Serwer
Ponieważ Pawlok używał ułomnego Eclipse'a, wynikowe Makefiles miały niewiele wspólnego z prawdziwymi i nie kompilowały się nigdzie poza komputerem Pawloka. Na szczęście od czego jest cmake?

``sh
$ cd checkers-server
$ cmake .
$ make
``

##### Klient

Tutaj sprawa jest prostsza - do Qt SDK dostajemy qmake'a:

``sh
$ qmake checkers-client.pro
$ make
``

### Rozwój
Chcesz pomóc? To spadaj, najwyżej zrób forka i elo, nie chcemy cię więcej widzieć.


### Licencja
Tbw na licencję.`
